using System.Collections.Generic;

namespace Agn.UI.Navigation
{
    public interface INavigationFactory
    {
        IEnumerable<INavigatable> Build();
        INavigatable Get(string category, string name);
    }
}
