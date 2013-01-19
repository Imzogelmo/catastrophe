
namespace Agn.UI
{
    /// <summary>
    /// Describes the avaliable view hosts.
    /// </summary>
    public enum ViewHostType
    {
        /// <summary>
        /// Displays as a normal form.
        /// </summary>
        Form,

        /// <summary>
        /// Displays as a modal dialog.
        /// </summary>
        Dialog,

        /// <summary>
        /// Displays as a dockable form against the <see cref="IApplicationContext.DockContainer"/>.
        /// </summary>
        Docking
    }
}
