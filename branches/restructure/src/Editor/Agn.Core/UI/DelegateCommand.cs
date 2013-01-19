using System;

namespace Agn.UI
{
    /// <summary>
    /// Provides a basic implementation of the command using a delegate.
    /// </summary>
    public class DelegateCommand : ICommand
    {
        internal readonly Action<object> command;

        public DelegateCommand(Action<object> command)
        {
            this.command = command;
        }

        public void Execute(object sender)
        {
            this.command.Invoke(sender);
        }
    }
}
