using System;
using System.Runtime.InteropServices;

namespace Agn
{
    /// <summary>
    /// Provides access to native methods.
    /// </summary>
    public static class NativeMethods
    {
        public const int SW_HIDE = 0;
        public const int SW_SHOWNORMA = 1;

        /// <summary>
        /// Retrieves the window handle used by the console associated with the calling process.
        /// </summary>
        /// <returns>The retrun value is a handle to the window used by the console
        /// associated with the calling process, or null if there is no such
        /// associated console.</returns>
        [DllImport("kernel32.dll")]
        public static extern IntPtr GetConsoleWindow();

        /// <summary>
        /// Sets the specified window's show state.
        /// </summary>
        /// <param name="hWnd">A handle to the window.</param>
        /// <param name="nCmdShow">Controls how the window is to be shown.</param>
        /// <returns>If the window was previously visible, then true, otherwise false.</returns>
        [DllImport("user32.dll")]
        public static extern bool ShowWindow(IntPtr hWnd, int nCmdShow);
    }
}
