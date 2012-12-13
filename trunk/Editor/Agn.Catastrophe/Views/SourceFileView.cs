using Agn.UI;
using System;
using System.Collections.Generic;
using System.ComponentModel.Composition;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Agn.Catastrophe.Editor.Views
{
    [Export(typeof(IView))]
    [ViewSettings("/file/{fileName}")]
    public class SourceFileView : IView
    {
        public string Text { get; private set; }

        public Control CreateControl(ViewContext context)
        {
            var fileName = context.Parameters["fileName"];

            // TODO Translate file name.

            fileName = @"C:\temp\20121205_1111_19.txt";
            this.Text = Path.GetFileName(fileName);

            return new SourceFile() { FileName = fileName };
        }
    }
}
