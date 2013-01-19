using log4net;
using log4net.Config;
using System;
using System.ComponentModel.Composition;
using System.Linq;
using System.Reflection;

namespace Agn
{
    /// <summary>
    /// Simple class for starting up the application from the main entry point.
    /// </summary>
    public class ApplicationStarter
    {
        private readonly Arguments args;
        private readonly ILog log = LogManager.GetLogger(typeof(ApplicationStarter));

        /// <summary>
        /// Creates the starter instance based upon the standard input arguments.
        /// </summary>
        /// <param name="args">The standard input arguments.</param>
        public ApplicationStarter(string[] args)
            : this(GetEntryPath, args)
        {
        }

        /// <summary>
        /// Creates the starter instance with the composer path specified.
        /// </summary>
        /// <param name="getExecutingPath">Delegate for providing the exectuion path.</param>
        /// <param name="args">The standard input arguments.</param>
        internal ApplicationStarter(Func<string> getExecutingPath, string[] args)
        {
            // Configure using the standard App.config.
            XmlConfigurator.Configure();

            // Convert the arguments.
            this.args = new Arguments(args);

            // TODO parse out an argument for injecting start behavior.

            // Execute the delegate for getting the path.
            var executingPath = getExecutingPath.Invoke();

            // Log out the path.
            this.log.Info("Composing IApplicationStart from: " + executingPath);

            // Compose this instance.
            using (var composer = new AbstractComposer(executingPath))
            {
                composer.Compose(this);
            }
        }

        /// <summary>
        /// Gets or sets the collection of starts that will create the application.
        /// </summary>
        [ImportMany(typeof(IApplicationStart))]
        internal IApplicationStart[] Starts { get; set; }

        /// <summary>
        /// Gets the entry assembly's local path.
        /// </summary>
        private static string GetEntryPath()
        {
            return Assembly.GetEntryAssembly()
                           .GetName()
                           .GetLocalPath();
        }

        /// <summary>
        /// Starts the application.
        /// </summary>
        public void Start()
        {
            try
            {
                // Sort the starts, and invoke them one by one.
                foreach (var start in this.Starts.OrderBy(s => s.Order))
                {
                    this.log.Info("Starting [" + start.Order + "]: " + start.GetType());
                    start.Start(this.args);
                }
            }
            catch (Exception ex)
            {
                this.log.Fatal(ex);
                throw ex;
            }
        }
    }
}
