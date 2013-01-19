using Agn.UI;
using System;

namespace Agn
{
    /// <summary>
    /// Provides information about the application in its running state.
    /// </summary>
    public interface IApplicationContext : IServiceProvider
    {
        /// <summary>
        /// Gets or sets the composer for injecting dependencies.
        /// </summary>
        AbstractComposer Composer { get; set; }

        /// <summary>
        /// Gets or sets the dock container for adding dockable windows to.
        /// </summary>
        IDockContainer DockContainer { get; set; }
    }
}
