using System;
using System.Windows.Forms;

namespace Agn.Catastrophe.Views
{
    /// <summary>
    /// Provides a view for converting files.
    /// </summary>
    public partial class ConvertFile : UserControl
    {
        private BindingSource binding;
        private ConvertFileViewModel model;

        public ConvertFile()
        {
            InitializeComponent();
        }

        protected override void OnLoad(EventArgs e)
        {
            base.OnLoad(e);

            if (this.DesignMode) { return; }

            this.ParentForm.AcceptButton = this.buttonConvert;
            this.ParentForm.CancelButton = this.buttonCancel;

            // Bind the data source.
            this.model = new ConvertFileViewModel();
            this.binding = new BindingSource(this.model, null);

            this.textBoxSourceFile.DataBindings.Add("Text", this.binding, "SourceFile");
            this.textBoxTargetFile.DataBindings.Add("Text", this.binding, "TargetDirectory");
        }

        private void buttonCancel_Click(object sender, EventArgs e)
        {
            this.ParentForm.Close();
        }

        private void buttonConvert_Click(object sender, EventArgs e)
        {
            this.binding.EndEdit();

            // Apply the conversion.
            this.model.Convert();

            // Show the error.
            if (!string.IsNullOrEmpty(this.model.Error))
            {
                MessageBox.Show(
                    this.model.Error,
                    "Error",
                    MessageBoxButtons.OK,
                    MessageBoxIcon.Error);
            }
        }
    }
}
