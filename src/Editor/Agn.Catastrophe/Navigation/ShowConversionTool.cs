using Agn.UI;
using Agn.UI.Navigation;
using System;
using System.Collections.Generic;
using System.ComponentModel.Composition;
using System.Linq;
using System.Text;

namespace Agn.Catastrophe.Navigation
{
    /// <summary>
    /// Allows navigating to the conversion tool.
    /// </summary>
    [Export(typeof(INavigatable))]
    public class ShowConversionTool : Navigatable
    {
        public ShowConversionTool()
            : base("Tools", 1, "Convert Files", 1, Open) { }

        private static void Open(object o)
        {
            // Open the Project Navigator view.
            var view = ViewFactory.Default.Build("ffc:///convert");

            // Show as a dialog window.
            var host = ViewHostFactory.Default.Build(ViewHostType.Dialog);
            host.Show(view);
        }
    }
}
