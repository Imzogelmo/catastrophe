using System.ComponentModel.Composition;
using System.Reflection;
using System.Linq;

namespace Agn.Catastrophe.Editor.Start
{
    /// <summary>
    /// Initializes the application context.
    /// </summary>
    [Export(typeof(IApplicationStart))]
    public class InitializeContext : IApplicationStart
    {
        /// <summary>
        /// Gets the order in which the start should be invoked.
        /// </summary>
        public int Order
        {
            get { return 0; }
        }

        /// <summary>
        /// Starts the application.
        /// </summary>
        /// <param name="args">The collection of input arguments.</param>
        public void Start(Arguments args)
        {
            var asm = Assembly.GetEntryAssembly();
            var names = asm.GetReferencedAssemblies()
                           .Where(n => n.Name.StartsWith("Agn."))
                           .Select(n => Assembly.Load(n).GetName().GetLocalPath())
                           .Concat(new [] {
                               asm.GetName().GetLocalPath(),
                               @".\Agn.Catastrophe.dll" })
                           .ToArray();
            
            ApplicationContext.Current.Composer = new AbstractComposer(names);
        }
    }
}
