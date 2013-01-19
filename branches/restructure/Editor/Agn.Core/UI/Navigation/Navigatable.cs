using System;
using System.ComponentModel;

namespace Agn.UI.Navigation
{
    public class Navigatable : INavigatable
    {
        public const string IsEnabledPropertyName = "IsEnabled";
        public const string IsVisiblePropertyName = "IsVisible";

        protected Navigatable(string category, int categoryOrder, string name, int order, Action<object> command)
            : this(category, categoryOrder, name, order, new DelegateCommand(command))
        {
        }

        protected Navigatable(string category, int categoryOrder, string name, int order, ICommand command)
        {
            this.Category = category;
            this.CategoryOrder = categoryOrder;
            this.Command = command;
            this.Name = name;
            this.Order = order;
        }

        public event PropertyChangedEventHandler PropertyChanged;

        public string Category { get; private set; }
        public int CategoryOrder { get; private set; }
        public ICommand Command { get; private set; }

        private bool isEnabled = true;
        public bool IsEnabled
        {
            get { return this.isEnabled; }
            set
            {
                if (this.isEnabled == value) { return; }
                this.isEnabled = value;
                this.OnPropertyChanged(new PropertyChangedEventArgs(IsEnabledPropertyName));
            }
        }

        private bool isVisible = true;
        public bool IsVisible
        {
            get { return this.isEnabled; }
            set
            {
                if (this.isVisible == value) { return; }
                this.isVisible = value;
                this.OnPropertyChanged(new PropertyChangedEventArgs(IsVisiblePropertyName));
            }
        }

        public string Name { get; private set; }
        public int Order { get; private set; }

        protected virtual void OnPropertyChanged(PropertyChangedEventArgs e)
        {
            var ev = this.PropertyChanged;
            ev.Invoke(this, e);
        }
    }
}
