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
        public static void Debug(this ILog log, Func<object> thunk)
        {
            if (log.IsDebugEnabled)
            {
                log.Debug(thunk.Invoke());
            }
        }

        public static void Error(this ILog log, Func<object> thunk)
        {
            if (log.IsErrorEnabled)
            {
                log.Error(thunk.Invoke());
            }
        }

        public static void Fatal(this ILog log, Func<object> thunk)
        {
            if (log.IsFatalEnabled)
            {
                log.Fatal(thunk.Invoke());
            }
        }

        public static void Info(this ILog log, Func<object> thunk)
        {
            if (log.IsInfoEnabled)
            {
                log.Info(thunk.Invoke());
            }
        }

        public static void Warn(this ILog log, Func<object> thunk)
        {
            if (log.IsWarnEnabled)
            {
                log.Warn(thunk.Invoke());
            }
        }
    }
}
