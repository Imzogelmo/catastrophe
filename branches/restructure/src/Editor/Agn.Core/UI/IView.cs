using System;
using System.Windows.Forms;

namespace Agn.UI
{
    /// <summary>
    /// Provides an interface for creating a view.
    /// </summary>
    public interface IView
    {
        string Text { get; }
        Control CreateControl(ViewContext context);
    }
}
