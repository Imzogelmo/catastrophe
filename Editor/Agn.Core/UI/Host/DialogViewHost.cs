using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Agn.UI.Host
{
    public class DialogViewHost : FormViewHost
    {
        protected override void ShowForm(Form form)
        {
            using (form)
            {
                form.ShowDialog();
            }
        }
    }
}
