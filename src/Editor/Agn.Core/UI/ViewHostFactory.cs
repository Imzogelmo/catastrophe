using System.Collections.Generic;

namespace Agn.UI
{
    /// <summary>
    /// Creates all avaliable <see cref="IViewHost"/> based upon <see cref="ViewHostType"/>.
    /// </summary>
    public class ViewHostFactory : IViewHostFactory
    {
        internal ViewHostFactory()
        {
            this.HostsByType = new Dictionary<ViewHostType, IViewHost>
            {
                { ViewHostType.Form, new Host.FormViewHost() },
                { ViewHostType.Dialog, new Host.DialogViewHost() },
                { ViewHostType.Docking, new Host.DockingHost() }
            };
        }

        static ViewHostFactory()
        {
            Default = new ViewHostFactory();
        }

        /// <summary>
        /// Gets or sets the default factory.
        /// </summary>
        public static IViewHostFactory Default { get; set; }

        /// <summary>
        /// Gets the internal view hosts by type.
        /// </summary>
        internal Dictionary<ViewHostType, IViewHost> HostsByType { get; private set; }
        
        /// <summary>
        /// Builds a <see cref="IViewHost"/> based upon <see cref="ViewHostType"/>.
        /// </summary>
        public IViewHost Build(ViewHostType type)
        {
            IViewHost host;
            if (!this.HostsByType.TryGetValue(type, out host))
            {
                return null;
            }
            return host;
        }
    }
}
