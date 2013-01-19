
namespace Agn.UI
{
    /// <summary>
    /// Provides an interface for adding a view to a docking container.
    /// </summary>
    public interface IDockContainer
    {
        /// <summary>
        /// Adds a view to the container.
        /// </summary>
        void Add(ViewContext dockableContext);
    }
}
