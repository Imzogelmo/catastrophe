
namespace Agn
{
    /// <summary>
    /// Provides an interface for starting up an application.
    /// </summary>
    public interface IApplicationStart
    {
        /// <summary>
        /// Gets the order in which the start should be invoked.
        /// </summary>
        int Order { get; }

        /// <summary>
        /// Starts the application.
        /// </summary>
        /// <param name="args">The collection of input arguments.</param>
        void Start(Arguments args);
    }
}
