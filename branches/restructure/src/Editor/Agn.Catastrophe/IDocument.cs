using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Agn.Catastrophe.Editor
{
    public interface IDocument
    {
        string FileName { get; set; }
        bool HasChanges { get; }

        bool Refresh();
        bool Reject();
        bool Save();
    }
}
