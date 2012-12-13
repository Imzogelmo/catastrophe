using Agn.UI;
using System;
using System.ComponentModel.Composition;
using System.Windows.Forms;

namespace Agn.Catastrophe.Editor.Views
{
    /// <summary>
    /// Views the currently open project.
    /// </summary>
    [Export(typeof(IView))]
    [ViewSettings("/project")]
    public class ProjectNavigatorView : IView
    {
        public string Text
        {
            get { return "Project Navigator"; }
        }

        public Control CreateControl(ViewContext context)
        {
            return new ProjectNavigator();
        }
    }
}
