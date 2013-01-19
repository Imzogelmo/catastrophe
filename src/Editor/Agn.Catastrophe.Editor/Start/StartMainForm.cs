using System.ComponentModel.Composition;
using System.Windows.Forms;

namespace Agn.Catastrophe.Editor.Start
{
    /// <summary>
    /// Starts the main form.
    /// </summary>
    [Export(typeof(IApplicationStart))]
    public class StartMainForm : IApplicationStart
    {
        /// <summary>
        /// Gets the order in which the start should be invoked.
        /// </summary>
        public int Order
        {
            get { return 1; }
        }

        /// <summary>
        /// Starts the application.
        /// </summary>
        /// <param name="args">The collection of input arguments.</param>
        public void Start(Arguments args)
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new MainMenu());
        }
    }
}
