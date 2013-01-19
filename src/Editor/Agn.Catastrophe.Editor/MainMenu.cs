using Agn.UI;
using Agn.UI.Navigation;
using System;
using System.Linq;
using System.Windows.Forms;

namespace Agn.Catastrophe.Editor
{
    /// <summary>
    /// Provides access to all operations within the application.
    /// </summary>
    public partial class MainMenu : Form
    {
        public MainMenu()
        {
            InitializeComponent();
        }

        /// <summary>
        /// Adds navigation to the user interface.
        /// </summary>
        private void AddNavigation()
        {
            // Query for all of the navigatables exported in the current context.
            var groups = NavigationFactory.Default.Build()
                                                  .OrderBy(n => n.CategoryOrder)
                                                  .ThenBy(n => n.Category)
                                                  .GroupBy(n => n.Category);


            // Add the groups and items to the main bar.
            foreach (var group in groups)
            {
                var menuGroup = new ToolStripMenuItem(group.Key);
                this.menuStrip.Items.Add(menuGroup);

                menuGroup.DropDownItems.AddRange(
                    group.OrderBy(n => n.Order)
                         .Select(CreateMenuItem)
                         .ToArray());
            }
        }

        /// <summary>
        /// Creates a menu item from a navigatable.
        /// </summary>
        /// <param name="navigatable">The navigatable to convert.</param>
        private static ToolStripMenuItem CreateMenuItem(INavigatable navigatable)
        {
            // Create a new menu item.
            var menuItem = new ToolStripMenuItem(navigatable.Name)
            {
                Enabled = navigatable.IsEnabled,
                Visible = navigatable.IsVisible
            };

            // Listen for enabled/visibility change.
            navigatable.PropertyChanged += (sender, e) =>
            {
                switch (e.PropertyName)
                {
                    case Navigatable.IsEnabledPropertyName:
                        menuItem.Enabled = navigatable.IsEnabled;
                        break;
                    case Navigatable.IsVisiblePropertyName:
                        menuItem.Visible = navigatable.IsVisible;
                        break;
                }
            };

            // Handle the execution of the command.
            menuItem.Click += (sender, e) =>
                navigatable.Command.Execute(menuItem);

            return menuItem;
        }

        /// <summary>
        /// Handles the loading of the form.
        /// </summary>
        protected override void OnLoad(EventArgs e)
        {
            base.OnLoad(e);

            // Do nothing in design mode, i.e., the visual studio designer is currently running.
            if (this.DesignMode) { return; }

            // Set the dock container to be the current dock panel.
            ApplicationContext.Current.DockContainer = new DockPanelContainer(this.dockPanel);

            // Add the navigation elements to the form.
            this.AddNavigation();
        }
    }
}
