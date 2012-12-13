using Microsoft.VisualStudio.TestTools.UnitTesting;
using System;
using System.Collections.Generic;
using System.ComponentModel.Composition;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Agn
{
    [TestClass]
    public class AbstractComposerTest
    {
        private static AbstractComposer Create()
        {
            var codeBase = typeof(AbstractComposerTest).Assembly.GetName()
                                                                .CodeBase;
            var localPath = new Uri(codeBase).LocalPath;
            return new AbstractComposer(localPath);
        }

        [TestMethod]
        public void ComposeTest()
        {
            var composer = Create();
            var importer = new TestImporter();
            composer.Compose(importer);

            Assert.IsNotNull(importer.Export);
            Assert.IsInstanceOfType(importer.Export, typeof(TestExport));
        }

        [ExpectedException(typeof(ObjectDisposedException))]
        [TestMethod]
        public void DisposeTest()
        {
            var composer = new AbstractComposer();
            composer.Dispose();
            composer.Compose(this);
        }

        public class TestImporter
        {
            [Import(typeof(ITestExport))]
            public ITestExport Export { get; set; }
        }

        public interface ITestExport { }
        [Export(typeof(ITestExport))]
        public class TestExport : ITestExport { }
    }
}
