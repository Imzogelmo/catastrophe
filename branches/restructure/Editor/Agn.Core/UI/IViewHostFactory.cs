
namespace Agn.UI
{
    /// <summary>
    /// Provides an interface for building <see cref="IViewHost"/>.
    /// </summary>
    public interface IViewHostFactory
    {
        /// <summary>
        /// Builds a <see cref="IViewHost"/> based upon <see cref="ViewHostType"/>.
        /// </summary>
        IViewHost Build(ViewHostType type);
    }
}
