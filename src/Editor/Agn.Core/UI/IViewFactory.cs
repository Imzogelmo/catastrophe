
namespace Agn.UI
{
    /// <summary>
    /// Provides an interface for creating views.
    /// </summary>
    public interface IViewFactory
    {
        /// <summary>
        /// Builds the <see cref="IView"/>.
        /// </summary>
        /// <param name="uri">The path to the view including parameters.</param>
        /// <returns>The view that was built.</returns>
        ViewContext Build(string uri);
    }
}
