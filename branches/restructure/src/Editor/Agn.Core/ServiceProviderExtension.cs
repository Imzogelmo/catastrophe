using System;

namespace Agn
{
    /// <summary>
    /// Provides extension methods for all class types that implement the interface <see cref="IServiceProvider"/>.
    /// </summary>
    public static class ServiceProviderExtension
    {
        /// <summary>
        /// Gets the service object of the specified <typeparamref name="T"/>.
        /// </summary>
        /// <typeparam name="T">The type of service to request.</typeparam>
        /// <param name="provider">The provider instance which stores services.</param>
        /// <returns>A service object of type <typeparamref name="T"/>.-or- null 
        /// if there is no service object of type <typeparamref name="T"/>.</returns>
        public static T GetService<T>(this IServiceProvider provider)
            where T : class
        {
            return provider.GetService(typeof(T)) as T;
        }
    }
}
