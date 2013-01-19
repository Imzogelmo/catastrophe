using log4net;
using System;
using System.Collections.Generic;
using System.Windows.Forms;

namespace Agn.UI
{
    /// <summary>
    /// Wraps a call to a view.
    /// </summary>
    public sealed class ViewContext
    {
        private readonly ILog log = LogManager.GetLogger(typeof(ViewContext));

        /// <summary>
        /// New instance of a view with its original access call.
        /// </summary>
        public ViewContext(IView view, Uri uri, IDictionary<string, string> parameters)
        {
            this.AccessUri = uri;
            this.Parameters = parameters;
            this.View = view;
        }

        /// <summary>
        /// Gets the original access URI for the view.
        /// </summary>
        public Uri AccessUri { get; private set; }

        /// <summary>
        /// Gets the collection of named parameters.
        /// </summary>
        public IDictionary<string, string> Parameters { get; private set; }

        /// <summary>
        /// Gets the view.
        /// </summary>
        public IView View { get; private set; }

        /// <summary>
        /// Creates the control which will represent the view.
        /// </summary>
        public Control CreateControl()
        {
            try
            {
                var control = this.View.CreateControl(this);

                this.log.Info("Created " + control.GetType() + " with " + this.AccessUri);

                return control;
            }
            catch (Exception ex)
            {
                this.log.Fatal("Unable to Create View: " + this.AccessUri, ex);
                throw ex;
            }
        }
    }
}
