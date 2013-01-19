using System.ComponentModel;

namespace Agn.UI.Navigation
{
    public interface INavigatable : INotifyPropertyChanged
    {
        string Category { get; }
        int CategoryOrder { get; }
        ICommand Command { get; }
        bool IsEnabled { get; set; }
        bool IsVisible { get; set; }
        string Name { get; }
        int Order { get; }
    }
}
