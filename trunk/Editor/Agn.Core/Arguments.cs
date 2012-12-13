
using log4net;
namespace Agn
{
    /// <summary>
    /// Converts standard input arguments into easily interpretable keys and values.
    /// </summary>
    public class Arguments
    {
        private readonly ILog log = LogManager.GetLogger(typeof(Arguments));

        public Arguments(string[] args)
        {
            this.Args = args;

            if (this.log.IsInfoEnabled)
            {
                foreach (var arg in args)
                {
                    this.log.Info("Parsing Arg: " + arg);
                    // TODO convert args.
                }
            }
        }

        /// <summary>
        /// Gets the original collection of input arguments.
        /// </summary>
        public string[] Args { get; private set; }
    }
}
