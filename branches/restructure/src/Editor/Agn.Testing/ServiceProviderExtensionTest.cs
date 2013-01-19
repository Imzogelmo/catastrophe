using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using System.Collections.Generic;

namespace Agn
{
    [TestClass]
    public class ServiceProviderExtensionTest
    {
        [TestMethod]
        public void GetServiceTest()
        {
            var expected = new GenericParameterHelper();
            var serviceProvider = new MockServiceProvider(new Dictionary<Type, object>
            {
                { typeof(GenericParameterHelper), expected },
                { typeof(string), null }
            });

            var helper = serviceProvider.GetService<GenericParameterHelper>();
            Assert.AreEqual(expected, helper);

            var str = serviceProvider.GetService<string>();
            Assert.IsNull(str);
        }

        public class MockServiceProvider : IServiceProvider
        {
            private readonly Dictionary<Type, object> services;

            public MockServiceProvider(Dictionary<Type, object> services)
            {
                this.services = services;
            }

            public object GetService(Type serviceType)
            {
                object service;
                if (!this.services.TryGetValue(serviceType, out service))
                {
                    service = null;
                }
                return service;
            }
        }
    }
}
