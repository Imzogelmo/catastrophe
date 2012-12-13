using System.Collections.Generic;
using System.ComponentModel.Composition;
using System.Linq;

namespace Agn.UI.Navigation
{
    /// <summary>
    /// Provides the default implementation for creating navigation elements.
    /// </summary>
    public class NavigationFactory : INavigationFactory
    {
        internal NavigationFactory()
        {
            ApplicationContext.Current.Composer.Compose(this);
        }

        static NavigationFactory()
        {
            Default = new NavigationFactory();
        }

        /// <summary>
        /// Gets or sets the default navigation factory.
        /// </summary>
        public static INavigationFactory Default { get; set; }

        [ImportMany(typeof(INavigatable))]
        internal IEnumerable<INavigatable> Navigatables { get; set; }

        /// <summary>
        /// Builds all navigatables.
        /// </summary>
        /// <returns></returns>
        public IEnumerable<INavigatable> Build()
        {
            return this.Navigatables;
        }

        /// <summary>
        /// Gets a navigatable by category/name.
        /// </summary>
        public INavigatable Get(string category, string name)
        {
            return this.Navigatables.SingleOrDefault(n => n.Category == category 
                                                     && n.Name == name);
        }
    }
}
