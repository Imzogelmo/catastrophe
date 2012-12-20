using log4net;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Agn
{
    public static class LogExtension
    {
        public static void DebugDelay(this ILog log, Func<object> thunk)
        {
            if (log.IsDebugEnabled)
            {
                log.Debug(thunk.Invoke());
            }
        }

        public static void ErrorDelay(this ILog log, Func<object> thunk)
        {
            if (log.IsErrorEnabled)
            {
                log.Error(thunk.Invoke());
            }
        }

        public static void FatalDelay(this ILog log, Func<object> thunk)
        {
            if (log.IsFatalEnabled)
            {
                log.Fatal(thunk.Invoke());
            }
        }

        public static void InfoDelay(this ILog log, Func<object> thunk)
        {
            if (log.IsInfoEnabled)
            {
                log.Info(thunk.Invoke());
            }
        }

        public static void WarnDelay(this ILog log, Func<object> thunk)
        {
            if (log.IsWarnEnabled)
            {
                log.Warn(thunk.Invoke());
            }
        }
    }
}
