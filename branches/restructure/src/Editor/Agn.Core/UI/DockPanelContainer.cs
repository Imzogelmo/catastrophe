using System.Windows.Forms;
using WeifenLuo.WinFormsUI.Docking;

namespace Agn.UI
{
    /// <summary>
    /// Default implementation for wrapping around <see cref="DockPanel"/>.
    /// </summary>
    public class DockPanelContainer : IDockContainer
    {
        private readonly DockPanel panel;

        /// <summary>
        /// New instance of the container.
        /// </summary>
        /// <param name="panel">The panel to use as a root.</param>
        public DockPanelContainer(DockPanel panel)
        {
            this.panel = panel;
        }

        /// <summary>
        /// Adds a view to the dock panel.
        /// </summary>
        public void Add(ViewContext dockableContext)
        {
            var control = dockableContext.CreateControl();
            var content = new DockContent
            {
                Text = dockableContext.View.Text
            };
            content.Controls.Add(control);
            control.Dock = DockStyle.Fill;
            content.Show(this.panel);
        }
    }
}
