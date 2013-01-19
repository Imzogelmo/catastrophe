using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Agn.Catastrophe.Editor
{
    public interface IDocumentManager
    {
        ObservableCollection<IDocument> Documents { get; }
    }
}
