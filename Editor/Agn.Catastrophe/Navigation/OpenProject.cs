using Agn.UI.Navigation;
using System.ComponentModel.Composition;

namespace Agn.Catastrophe.Editor.Navigation
{
    [Export(typeof(INavigatable))]
    internal class OpenProject : Navigatable
    {
        public OpenProject()
            : base("File", 0, "Open Project", 1, Open) { }

        private static void Open(object o)
        {
            // TODO Remove.
            var n = NavigationFactory.Default.Get("File", "New &Project");
            n.IsEnabled = !n.IsEnabled;
        }
    }
}
