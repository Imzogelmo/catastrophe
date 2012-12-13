
namespace Agn.UI
{
    /// <summary>
    /// Provides metadata about a <see cref="IView"/>.
    /// </summary>
    public interface IViewMetadata
    {
        /// <summary>
        /// Gets the URI Template for matching.
        /// </summary>
        string UriTemplate { get; }
    }
}
