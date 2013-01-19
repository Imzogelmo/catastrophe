using log4net;
using System;
using System.ComponentModel.Composition;
using System.ComponentModel.Composition.Hosting;
using System.Linq;

namespace Agn
{
    /// <summary>
    /// Provides the ability to compose exported contracts onto parts that are importing contracts.
    /// </summary>
    public class AbstractComposer : IDisposable
    {
        private readonly ILog log = LogManager.GetLogger(typeof(AbstractComposer));

        /// <summary>
        /// Initializes the composer with a array of assembly names to inspect for exported contracts.
        /// </summary>
        /// <param name="assemblyNames">The array of assembly names to </param>
        public AbstractComposer(params string[] assemblyNames)
        {
            if (this.log.IsInfoEnabled)
            {
                int i = 0;
                foreach (var name in assemblyNames)
                {
                    this.log.Info("Composing With [" + (i++) + "]: " + name);
                }
            }

            var assemblyCatalogs = assemblyNames.Select(n => new AssemblyCatalog(n)).ToArray();
            var catalog = new AggregateCatalog(assemblyCatalogs);
            this.Container = new CompositionContainer(catalog);
        }

        /// <summary>
        /// Disposes of the composer instance.
        /// </summary>
        ~AbstractComposer()
        {
            this.Dispose(false);
        }

        /// <summary>
        /// Gets the container responsible for inspecting for exported contracts, and importing them onto parts.
        /// </summary>
        internal CompositionContainer Container { get; private set; }

        /// <summary>
        /// Imports contracts onto attributed parts.
        /// </summary>
        /// <param name="parts">Any number of parts that have importing attributes.</param>
        public virtual void Compose(params object[] parts)
        {
            // If the container is null, then this instance has already
            // been disposed and should no longer function.
            if (this.Container == null)
            {
                throw new ObjectDisposedException(typeof(AbstractComposer).Name);
            }

            if (this.log.IsInfoEnabled)
            {
                foreach (var part in parts)
                {
                    this.log.Info("Composing: [" + part.GetType() + "]: " + part);
                }
            }

            // Compose the parts.
            this.Container.ComposeParts(parts);
        }

        /// <summary>
        /// Cleans up local resources.
        /// </summary>
        public void Dispose()
        {
            this.Dispose(true);
            GC.SuppressFinalize(this);
        }

        /// <summary>
        /// Cleans up local resources.
        /// </summary>
        /// <param name="disposing">True when called from <see cref="Dispose()"/>,
        /// otherwise called from the finalizer.</param>
        protected virtual void Dispose(bool disposing)
        {
            if (this.Container == null)
            {
                return;
            }

            this.Container.Dispose();
            this.Container = null;
        }
    }
}
