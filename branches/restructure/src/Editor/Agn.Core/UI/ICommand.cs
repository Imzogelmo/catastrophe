
namespace Agn.UI
{
    /// <summary>
    /// Provides an interface for executing an action.
    /// </summary>
    public interface ICommand
    {
        void Execute(object sender);
    }
}
