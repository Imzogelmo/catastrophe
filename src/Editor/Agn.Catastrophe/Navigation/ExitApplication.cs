using Agn.UI.Navigation;
using System.ComponentModel.Composition;
using System.Windows.Forms;

namespace Agn.Catastrophe.Editor.Navigation
{
    /// <summary>
    /// Allows navigating to close the application.
    /// </summary>
    [Export(typeof(INavigatable))]
    internal class ExitApplication : Navigatable
    {
        public ExitApplication()
            : base("File", 0, "E&xit", 2, Exit) { }

        private static void Exit(object o)
        {
            // Close all forms in the application.
            foreach (Form form in Application.OpenForms)
            {
                form.Close();
            }
        }
    }
}
