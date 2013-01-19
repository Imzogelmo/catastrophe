using log4net;
using System;
using System.Linq;
using System.Text.RegularExpressions;

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

            this.Flags = args.Select(a => ProcessMatch(a))
                             .Where(t => t != null)
                             .ToLookup(t => t.Item1, t => t.Item2);
        }

        private Tuple<string, string> ProcessMatch(string arg)
        {
            this.log.Info("Parsing Arg: " + arg);
            Match match = flagExpression.Match(arg);
            if (match.Success)
            {
                // Look up the flag always, and sometimes the value.
                string flag = match.Groups["Flag"].Value;
                string value = string.Empty;
                if (match.Groups["Value"].Success)
                {
                    value = match.Groups["Value"].Value;
                }

                this.log.Info("Flag: " + flag);
                this.log.Info("Value: " + value);

                // Return the results.
                return Tuple.Create(flag, value);
            }
            else
            {
                this.log.Info("Failed");
                return null;
            }
        }

        /// <summary>
        /// Gets the original collection of input arguments.
        /// </summary>
        public string[] Args { get; private set; }

        /// <summary>
        /// Gets the collection of flags that were parsed.
        /// </summary>
        public ILookup<string, string> Flags { get; private set; }

        private static Regex flagExpression = new Regex("(-(?<Flag>[\\w\\?])|--(?<Flag>\\w+)=\"(?<Value>\\w+)\"|--(?<Flag>\\w+)=(?<Value>\\w+)|--(?<Flag>\\w+))", RegexOptions.Compiled);
    }
}
