using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace Agn
{
    [TestClass]
    public class ArgumentsTest
    {
        [TestMethod]
        public void CtorTest()
        {
            var args = new[] { "1", "2", "3" };
            var arguments = new Arguments(args);

            // Simple test for now.
            CollectionAssert.AreEqual(args, arguments.Args);
        }
    }
}
