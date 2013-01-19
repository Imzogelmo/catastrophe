
namespace Agn.UI
{
    /// <summary>
    /// Provides an interface for showing <see cref="IView"/>.
    /// </summary>
    public interface IViewHost
    {
        /// <summary>
        /// Shows a view.
        /// </summary>
        /// <param name="view">The view to show.</param>
        void Show(ViewContext view);
    }
}
