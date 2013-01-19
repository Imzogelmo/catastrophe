using Agn.UI;
using System.ComponentModel.Composition;
using System.Windows.Forms;

namespace Agn.Catastrophe.Views
{
    /// <summary>
    /// Exposes the conversion window.
    /// </summary>
    [Export(typeof(IView))]
    [ViewSettings("/convert")]
    public class ConvertFileView : IView
    {
        public string Text { get { return "Convert File"; } }

        public Control CreateControl(ViewContext context)
        {
            return new ConvertFile();
        }
    }
}
