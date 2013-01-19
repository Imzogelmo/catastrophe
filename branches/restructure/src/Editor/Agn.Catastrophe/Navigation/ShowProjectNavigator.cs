using Agn.UI;
using Agn.UI.Navigation;
using System.ComponentModel.Composition;

namespace Agn.Catastrophe.Editor.Navigation
{
    /// <summary>
    /// Allows navigating to the project navigator.
    /// </summary>
    [Export(typeof(INavigatable))]
    internal class ShowProjectNavigator : Navigatable
    {
        public ShowProjectNavigator()
            : base("View", 1, "Project Navigator", 1, Open) { }

        private static void Open(object o)
        {
            // Open the Project Navigator view.
            var view = ViewFactory.Default.Build("ffc:///project");
            
            // Show as a docking window.
            var host = ViewHostFactory.Default.Build(ViewHostType.Docking);
            host.Show(view);
        }
    }
}
