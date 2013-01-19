using Agn.UI;
using log4net;
using System;
using System.Collections.Generic;
using System.ComponentModel.Composition;
using System.Linq;

namespace Agn
{
    /// <summary>
    /// Default implementation of the application context.
    /// </summary>
    public class ApplicationContext : IApplicationContext
    {
        private static readonly ILog log = LogManager.GetLogger(typeof(ApplicationContext));

        // TODO Change to internal, add signing and allow Agn.Testing access to internals.
        public ApplicationContext() { }

        static ApplicationContext()
        {
            current = new ApplicationContext();
        }

        private AbstractComposer composer;
        /// <summary>
        /// Gets or sets the composer for injecting dependencies.
        /// </summary>
        public AbstractComposer Composer
        {
            get { return this.composer; }
            set
            {
                if (this.composer == value) { return; }
                this.composer = value;
                if (this.composer != null)
                {
                    this.composer.Compose(this);
                }
            }
        }

        private static IApplicationContext current;
        /// <summary>
        /// Gets or sets the current run-time application context.
        /// </summary>
        public static IApplicationContext Current
        {
            get { return current; }
            set
            {
                if (current == value) { return; }
                current = value;
                log.Info("Override IApplicationContext: " + current.GetType());
            }
        }

        /// <summary>
        /// Gets or sets the dock container for adding dockable windows to.
        /// </summary>
        public IDockContainer DockContainer { get; set; }

        /// <summary>
        /// Sets the internal services exposed by <see cref="IServiceProvider"/>.
        /// </summary>
        [ImportMany(typeof(IService))]
        internal IService[] Services
        {
            set
            {
                if (value == null)
                {
                    this.ServicesByType = new Dictionary<Type, IService>();
                }
                else
                {
                    // TODO Add Service Metadata so that external assemblies
                    // can inject functionality by overwriting existing services
                    // when implementing the same interface.
                    this.ServicesByType = value.ToDictionary(s => s.ServiceType, s => s);
                }
            }
        }

        internal Dictionary<Type, IService> ServicesByType { get; private set; }

        /// <summary>
        /// Gets a service by its type.
        /// </summary>
        /// <param name="serviceType">The type of service requested.</param>
        /// <returns>The service requested if available, otherwise null.</returns>
        public object GetService(Type serviceType)
        {
            IService service;
            if (!this.ServicesByType.TryGetValue(serviceType, out service))
            {
                return null;
            }
            return service;
        }
    }
}
