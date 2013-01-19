using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using System.ComponentModel.Composition;

namespace Agn
{
    [TestClass]
    public class ApplicationContextTest
    {
        private static AbstractComposer Create()
        {
            var localPath = typeof(AbstractComposerTest).Assembly
                                                        .GetName()
                                                        .GetLocalPath();
            return new AbstractComposer(localPath);
        }

        [TestMethod]
        public void ComposerSetTest()
        {
            var context = new ApplicationContext();
            context.Composer = Create();
            var actual = context.GetService<MockService>();
            Assert.IsNotNull(actual);
            Assert.AreEqual(MockService.Instance, actual);
        }

        [TestMethod]
        public void CurrentGetTest()
        {
            Assert.IsNotNull(ApplicationContext.Current);
            Assert.IsInstanceOfType(ApplicationContext.Current, typeof(ApplicationContext));
        }

        [TestMethod]
        public void DockContainerGetTest()
        {
            var context = new ApplicationContext();
            Assert.IsNull(context.DockContainer);
        }

        [Export(typeof(IService))]
        public class MockService : IService
        {
            public MockService()
            {
                Instance = this;
            }

            public static MockService Instance { get; private set; }

            public Type ServiceType
            {
                get { return typeof(MockService); }
            }
        }
    }
}
