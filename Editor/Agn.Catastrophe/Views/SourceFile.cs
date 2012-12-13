using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;

namespace Agn.Catastrophe.Editor.Views
{
    public partial class SourceFile : UserControl
    {
        public SourceFile()
        {
            InitializeComponent();
        }

        public string FileName { get; set; }

        protected override void OnLoad(EventArgs e)
        {
            base.OnLoad(e);

            if (this.DesignMode) { return; }
            this.textBox1.Text = File.ReadAllText(this.FileName);
        }
    }
}
