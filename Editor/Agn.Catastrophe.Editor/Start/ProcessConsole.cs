using System.ComponentModel.Composition;
using System.Linq;

namespace Agn.Catastrophe.Editor.Start
{
    /// <summary>
    /// Processes the display of the console window.
    /// </summary>
    [Export(typeof(IApplicationStart))]
    public class ProcessConsole : IApplicationStart
    {
        /// <summary>
        /// Gets the order in which the start is executed.
        /// </summary>
        public int Order
        {
            get { return -1; }
        }

        /// <summary>
        /// Turns on the console based upon the -c or --console flag.
        /// </summary>
        public void Start(Arguments args)
        {
            if (args.Flags["c"].Concat(args.Flags["console"]).Any())
            {
                var console = NativeMethods.GetConsoleWindow();
                NativeMethods.ShowWindow(console, NativeMethods.SW_SHOWNORMA);
            }
        }
    }
}
