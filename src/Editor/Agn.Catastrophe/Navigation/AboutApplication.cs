using Agn.UI.Navigation;
using System.ComponentModel.Composition;
using System.Windows.Forms;

namespace Agn.Catastrophe.Editor.Navigation
{
    /// <summary>
    /// Navigates to the about page.
    /// </summary>
    [Export(typeof(INavigatable))]
    internal class AboutApplication : Navigatable
    {
        public AboutApplication()
            : base("Help", 2, "&About", 0, About) { }

        private static void About(object o)
        {
            MessageBox.Show("http://www.armageddongames.net/");
        }
    }
}
