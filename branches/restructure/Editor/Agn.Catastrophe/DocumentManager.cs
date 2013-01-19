using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel.Composition;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Agn.Catastrophe.Editor
{
    [Export(typeof(IService))]
    public class DocumentManager : IDocumentManager, IService
    {
        public DocumentManager()
        {
            this.Documents = new ObservableCollection<IDocument>();
        }

        public ObservableCollection<IDocument> Documents { get; private set; }

        public Type ServiceType
        {
            get { return typeof(IDocumentManager); }
        }
    }
}
