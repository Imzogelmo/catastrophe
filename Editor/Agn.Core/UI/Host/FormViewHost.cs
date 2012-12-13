using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Agn.UI.Host
{
    public class FormViewHost : IViewHost
    {
        public void Show(ViewContext context)
        {
            var control = context.CreateControl();
            var form = new Form
            {
                Text = context.View.Text
            };
            form.Controls.Add(control);
            control.Dock = DockStyle.Fill;
            this.ShowForm(form);
        }

        protected virtual void ShowForm(Form form)
        {
            form.Show();
        }
    }
}
