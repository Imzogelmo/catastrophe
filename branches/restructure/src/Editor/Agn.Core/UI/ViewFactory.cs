using log4net;
using System;
using System.Collections.Generic;
using System.ComponentModel.Composition;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;

namespace Agn.UI
{
    /// <summary>
    /// Creates the <see cref="IView"/> based upon a URI.
    /// </summary>
    public class ViewFactory : IViewFactory
    {
        private static readonly Regex TemplateParser = new Regex("(/{(?<Param>\\w+)})", RegexOptions.Compiled);

        private readonly ILog log = LogManager.GetLogger(typeof(ViewFactory));

        internal ViewFactory()
        {
            ApplicationContext.Current.Composer.Compose(this);
        }

        static ViewFactory()
        {
            Default = new ViewFactory();
        }

        /// <summary>
        /// Gets or sets the default factory.
        /// </summary>
        public static IViewFactory Default { get; set; }
        
        /// <summary>
        /// Sets the set of views injected from external assemblies.
        /// </summary>
        [ImportMany(typeof(IView))]
        internal Lazy<IView, IViewMetadata>[] Views
        {
            set
            {
                if (value == null)
                {
                    this.ViewsByUri = new Dictionary<MatchCriteria, ViewCriteria>();
                }
                else
                {
                    this.ViewsByUri = value.ToDictionary(
                        v => CreateTemplateUri(v.Metadata.UriTemplate), 
                        v => new ViewCriteria(v));
                }
            }
        }

        /// <summary>
        /// Gets the collection of views by uri.
        /// </summary>
        internal Dictionary<MatchCriteria, ViewCriteria> ViewsByUri { get; private set; }

        /// <summary>
        /// Builds the <see cref="IView"/>.
        /// </summary>
        /// <param name="uri">The path to the view including parameters.</param>
        /// <returns>The view that was built.</returns>
        public ViewContext Build(string uri)
        {
            return this.Build(new Uri(uri));
        }

        /// <summary>
        /// Builds the <see cref="IView"/>.
        /// </summary>
        /// <param name="uri">The path to the view including parameters.</param>
        /// <returns>The view that was built.</returns>
        public ViewContext Build(Uri uri)
        {
            this.log.Info("Parsing URI: " + uri);
            foreach (var key in this.ViewsByUri.Keys)
            {
                var match = key.Expression.Match(uri.AbsoluteUri);
                if (match.Success)
                {
                    var view = this.ViewsByUri[key].View.Value;
                    this.log.Info("Found " + view.GetType());
                    var parameters = GetParameters(key.ParamNames, match);
                    return new ViewContext(view, uri, parameters);
                }
            }
            return null;
        }

        /// <summary>
        /// Creates a match criteria based upon a template URI.
        /// </summary>
        /// <param name="templateUri">The base template URI.</param>
        private static MatchCriteria CreateTemplateUri(string templateUri)
        {
            // If there are any matches against parameter names embedded into the URI,
            // then create a new regular expression.
            var matches = TemplateParser.Matches(templateUri).Cast<Match>();
            if (matches.Any(m => m.Success))
            {
                StringBuilder builder = new StringBuilder();
                List<string> paramNames = new List<string>();
                int position = 0;
                foreach (var match in matches)
                {
                    var group = match.Groups["Param"];
                    paramNames.Add(group.Value);

                    if (position != match.Index)
                    {
                        builder.Append(templateUri.Substring(position, match.Index));
                    }
                    builder.Append("/(\\w*)");
                    position = match.Index + match.Length;
                }

                return new MatchCriteria(new Regex(builder.ToString()), paramNames.ToArray());
            }
            return new MatchCriteria(new Regex(templateUri));
        }

        /// <summary>
        /// Get the parameters from a match.
        /// </summary>
        /// <param name="paramNames">Collection of parameter names.</param>
        /// <param name="match">The match that resulted in a success against a URI.</param>
        /// <returns>A collection of key/value pair.</returns>
        private static IDictionary<string, string> GetParameters(string[] paramNames, Match match)
        {
            if (paramNames.Length == 0) { return null; }

            return paramNames.Select((n, i) => new
                                        {
                                            Key = n,
                                            Value = match.Groups[(i + 1)].Value
                                        })
                             .ToDictionary(p => p.Key, p => p.Value);
        }

        /// <summary>
        /// Internal class for storing match criteria.
        /// </summary>
        internal class MatchCriteria
        {
            public MatchCriteria(Regex expression)
                : this(expression, new string[0])
            {
            }

            public MatchCriteria(Regex expression, string[] paramNames)
            {
                this.Expression = expression;
                this.ParamNames = paramNames;
            }

            public Regex Expression { get; private set; }
            public string[] ParamNames { get; private set; }
        }

        /// <summary>
        /// Internal class for tracking metadata.
        /// </summary>
        internal class ViewCriteria
        {
            public ViewCriteria(Lazy<IView, IViewMetadata> view)
            {
                this.Metadata = view.Metadata;
                this.View = view;
            }

            public IViewMetadata Metadata { get; private set; }
            public Lazy<IView> View { get; private set; }
        }
    }
}
