using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using WeifenLuo.WinFormsUI.Docking;

namespace Agn.UI.Host
{
    public class DockingHost : IViewHost
    {
        public void Show(ViewContext context)
        {
            ApplicationContext.Current.DockContainer.Add(context);
        }
    }
}
