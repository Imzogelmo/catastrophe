using System;

namespace Agn.Catastrophe.Editor
{
    /// <summary>
    /// Main entry point for the application.
    /// </summary>
    static class Program
    {
        /// <summary>
        /// Main entry point.
        /// </summary>
        [STAThread]
        static void Main(string[] args)
        {
            // Always turn off the console.
            var console = NativeMethods.GetConsoleWindow();
            NativeMethods.ShowWindow(console, NativeMethods.SW_HIDE);

            // Start the application.
            var starter = new ApplicationStarter(args);
            starter.Start();
        }
    }
}
