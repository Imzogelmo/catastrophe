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
            // Start the application.
            var starter = new ApplicationStarter(args);
            starter.Start();
        }
    }
}
