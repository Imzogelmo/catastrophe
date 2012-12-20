using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using log4net;

namespace Agn
{
    [TestClass]
    public class LogExtensionTest
    {
        private void DelayTestHelper(Action<MockLog, Func<object>> work, Action<MockLog, bool> setWritten, Func<MockLog, bool> getWritten)
        {
            var log = new MockLog();
            var flag = false;
            Func<object> thunk = () => (flag = true).ToString();

            // Expect that upon invoking the delegate, that the flag
            // (above) and the written property are both not set
            // because the level is not enabled.
            work.Invoke(log, thunk);
            Assert.IsFalse(flag);
            Assert.IsFalse(getWritten.Invoke(log));

            // Set the level to be enabled, and then re-run the test.
            // Both the flag and the property should become set after
            // invoking the delegate.
            setWritten.Invoke(log, true);
            work.Invoke(log, thunk);
            Assert.IsTrue(flag);
            Assert.IsTrue(getWritten.Invoke(log));
        }

        [TestMethod]
        public void DebugDelayTest()
        {
            DelayTestHelper(
                (l, t) => l.DebugDelay(t),
                (l, f) => l.IsDebugEnabled = f,
                l => l.IsDebugEnabled);
        }

        [TestMethod]
        public void ErrorDelayTest()
        {
            DelayTestHelper(
                (l, t) => l.ErrorDelay(t),
                (l, f) => l.IsErrorEnabled = f,
                l => l.IsErrorEnabled);
        }

        [TestMethod]
        public void FatalDelayTest()
        {
            DelayTestHelper(
                (l, t) => l.FatalDelay(t),
                (l, f) => l.IsFatalEnabled = f,
                l => l.IsFatalEnabled);
        }

        [TestMethod]
        public void InfoDelayTest()
        {
            DelayTestHelper(
                (l, t) => l.InfoDelay(t),
                (l, f) => l.IsInfoEnabled = f,
                l => l.IsInfoEnabled);
        }

        [TestMethod]
        public void WarnDelayTest()
        {
            DelayTestHelper(
                (l, t) => l.WarnDelay(t),
                (l, f) => l.IsWarnEnabled = f,
                l => l.IsWarnEnabled);
        }

        public class MockLog : ILog
        {
            public void Debug(object message)
            {
                this.IsDebugWritten = true;
            }

            public void Error(object message)
            {
                this.IsErrorWritten = true;
            }

            public void Fatal(object message)
            {
                this.IsFatalWritten = true;
            }

            public void Info(object message)
            {
                this.IsInfoWritten = true;
            }

            public void Warn(object message)
            {
                this.IsWarnWritten = true;
            }

            public bool IsDebugEnabled { get; set; }

            public bool IsDebugWritten { get; set; }

            public bool IsErrorEnabled { get; set; }

            public bool IsErrorWritten { get; set; }

            public bool IsFatalEnabled { get; set; }

            public bool IsFatalWritten { get; set; }

            public bool IsInfoEnabled { get; set; }

            public bool IsInfoWritten { get; set; }

            public bool IsWarnEnabled { get; set; }

            public bool IsWarnWritten { get; set; }

            #region Not Implemented

            public void Debug(object message, Exception exception)
            {
                throw new NotImplementedException();
            }

            public void DebugFormat(IFormatProvider provider, string format, params object[] args)
            {
                throw new NotImplementedException();
            }

            public void DebugFormat(string format, object arg0, object arg1, object arg2)
            {
                throw new NotImplementedException();
            }

            public void DebugFormat(string format, object arg0, object arg1)
            {
                throw new NotImplementedException();
            }

            public void DebugFormat(string format, object arg0)
            {
                throw new NotImplementedException();
            }

            public void DebugFormat(string format, params object[] args)
            {
                throw new NotImplementedException();
            }

            public void Error(object message, Exception exception)
            {
                throw new NotImplementedException();
            }

            public void ErrorFormat(IFormatProvider provider, string format, params object[] args)
            {
                throw new NotImplementedException();
            }

            public void ErrorFormat(string format, object arg0, object arg1, object arg2)
            {
                throw new NotImplementedException();
            }

            public void ErrorFormat(string format, object arg0, object arg1)
            {
                throw new NotImplementedException();
            }

            public void ErrorFormat(string format, object arg0)
            {
                throw new NotImplementedException();
            }

            public void ErrorFormat(string format, params object[] args)
            {
                throw new NotImplementedException();
            }

            public void Fatal(object message, Exception exception)
            {
                throw new NotImplementedException();
            }

            public void FatalFormat(IFormatProvider provider, string format, params object[] args)
            {
                throw new NotImplementedException();
            }

            public void FatalFormat(string format, object arg0, object arg1, object arg2)
            {
                throw new NotImplementedException();
            }

            public void FatalFormat(string format, object arg0, object arg1)
            {
                throw new NotImplementedException();
            }

            public void FatalFormat(string format, object arg0)
            {
                throw new NotImplementedException();
            }

            public void FatalFormat(string format, params object[] args)
            {
                throw new NotImplementedException();
            }

            public void Info(object message, Exception exception)
            {
                throw new NotImplementedException();
            }

            public void InfoFormat(IFormatProvider provider, string format, params object[] args)
            {
                throw new NotImplementedException();
            }

            public void InfoFormat(string format, object arg0, object arg1, object arg2)
            {
                throw new NotImplementedException();
            }

            public void InfoFormat(string format, object arg0, object arg1)
            {
                throw new NotImplementedException();
            }

            public void InfoFormat(string format, object arg0)
            {
                throw new NotImplementedException();
            }

            public void InfoFormat(string format, params object[] args)
            {
                throw new NotImplementedException();
            }

            public void WarnFormat(IFormatProvider provider, string format, params object[] args)
            {
                throw new NotImplementedException();
            }

            public void WarnFormat(string format, object arg0, object arg1, object arg2)
            {
                throw new NotImplementedException();
            }

            public void WarnFormat(string format, object arg0, object arg1)
            {
                throw new NotImplementedException();
            }

            public void WarnFormat(string format, object arg0)
            {
                throw new NotImplementedException();
            }

            public void WarnFormat(string format, params object[] args)
            {
                throw new NotImplementedException();
            }

            public void Warn(object message, Exception exception)
            {
                throw new NotImplementedException();
            }

            public log4net.Core.ILogger Logger
            {
                get { throw new NotImplementedException(); }
            }

            #endregion
        }
    }
}
