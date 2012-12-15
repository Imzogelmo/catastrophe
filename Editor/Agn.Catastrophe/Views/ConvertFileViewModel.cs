using System.IO;

namespace Agn.Catastrophe.Views
{
    /// <summary>
    /// Provides a wrapper for values exposed to the UI, and a bridge into the native FileConverter.
    /// </summary>
    public class ConvertFileViewModel
    {
        /// <summary>
        /// Gets any error messages that may have occurred due 
        /// to validation, or through the file conversion process.
        /// </summary>
        public string Error { get; private set; }

        /// <summary>
        /// Gets or sets the source file to convert.
        /// </summary>
        public string SourceFile { get; set; }

        /// <summary>
        /// Gets or sets the target directory to convert into.
        /// </summary>
        public string TargetDirectory { get; set; }

        /// <summary>
        /// Validates the local propreties prior to calling the native converter.
        /// </summary>
        private bool Validate()
        {
            // Make sure that all of the file operations are valid.
            if (string.IsNullOrEmpty(this.SourceFile))
            {
                this.Error = "Missing Source File";
            }
            else if (!File.Exists(this.SourceFile))
            {
                this.Error = "Source File does not exist.";
            }
            else if (string.IsNullOrEmpty(this.TargetDirectory))
            {
                this.Error = "Missing Target Directory";
            }
            else if (!Directory.Exists(this.TargetDirectory))
            {
                this.Error = "Target Directory does not exist.";
            }

            // Only continue if there is no error.
            return string.IsNullOrEmpty(this.Error);
        }

        /// <summary>
        /// Calls the native converter.
        /// </summary>
        public void Convert()
        {
            // Reset the error flag.
            this.Error = null;

            // Validate that the local propeties are OK to pass to the native call.
            if (this.Validate())
            {
                // Create a new converter.
                FileConverter converter = new FileConverter();

                // Try to convert the source file into the target directory,
                // if it fails assign the resultant error into the local property.
                string error = null;
                if (!converter.Convert(this.SourceFile, this.TargetDirectory, ref error))
                {
                    this.Error = error ?? "Failed to convert file.";
                }
            }
        }
    }
}
