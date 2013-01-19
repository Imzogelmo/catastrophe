using System;
using System.Reflection;

namespace Agn
{
    /// <summary>
    /// Provides extension methods to the <see cref="AssemblyName"/> class.
    /// </summary>
    public static class AssemblyNameExtension
    {
        /// <summary>
        /// Gets the local path for the assembly.
        /// </summary>
        /// <param name="name">The assembly name to get the local path for.</param>
        /// <returns>The absolute local path to the assembly.</returns>
        public static string GetLocalPath(this AssemblyName name)
        {
            return new Uri(name.CodeBase).LocalPath;
        }
    }
}
