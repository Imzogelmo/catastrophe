using System;
using System.Linq;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace Agn
{
    [TestClass]
    public class ArgumentsTest
    {
        [TestMethod]
        public void CtorTest()
        {
            var args = new[] { 
                "1",
                "2", 
                "3",
                "-a", 
                "--word", 
                "--wordandvalue=asdf",
                "--wordandvalue=\"zxcv\"" };
            var arguments = new Arguments(args);

            // Make sure that the arrays are est.
            CollectionAssert.AreEqual(args, arguments.Args);

            // Test the flags.
            Assert.IsNotNull(arguments.Flags);
            Assert.AreEqual(3, arguments.Flags.Count());

            // Look up the a flag.
            var flags = arguments.Flags["a"];
            Assert.AreEqual(1, flags.Count());
            Assert.AreEqual(string.Empty, flags.Single());

            // Look up the word flag.
            flags = arguments.Flags["word"];
            Assert.AreEqual(1, flags.Count());
            Assert.AreEqual(string.Empty, flags.Single());

            // Look up the wordandvalue flag.
            flags = arguments.Flags["wordandvalue"];
            Assert.AreEqual(2, flags.Count());
            Assert.AreEqual("asdf", flags.First());
            Assert.AreEqual("zxcv", flags.Last());
        }
    }
}
