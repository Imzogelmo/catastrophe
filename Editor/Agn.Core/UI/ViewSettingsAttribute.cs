using System;
using System.ComponentModel.Composition;

namespace Agn.UI
{
    /// <summary>
    /// Describes the view, and how it is launched.
    /// </summary>
    [AttributeUsage(AttributeTargets.Class)]
    [MetadataAttribute]
    public class ViewSettingsAttribute : Attribute, IViewMetadata
    {
        public ViewSettingsAttribute(string uriTemplate)
        {
            this.UriTemplate = uriTemplate;
        }

        /// <summary>
        /// Gets the template to match against when inputting a URL.
        /// </summary>
        public string UriTemplate { get; private set; }
    }
}
