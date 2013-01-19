using Agn.UI;
using Agn.UI.Navigation;
using System.ComponentModel.Composition;

namespace Agn.Catastrophe.Editor.Navigation
{
    [Export(typeof(INavigatable))]
    internal class NewProject : Navigatable
    {
        public NewProject()
            : base("File", 0, "New &Project", 0, New) { }

        private static void New(object o)
        {
            // TODO
            // Open the Project Navigator view.
            var view = ViewFactory.Default.Build("ffc:///file/test");

            // Show as a docking window.
            var host = ViewHostFactory.Default.Build(ViewHostType.Docking);
            host.Show(view);
        }
    }
}
