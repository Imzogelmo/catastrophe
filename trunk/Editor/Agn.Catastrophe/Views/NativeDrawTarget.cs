using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Drawing.Imaging;
using System.Runtime.InteropServices;

namespace Agn.Catastrophe.Views
{
    /// <summary>
    /// Provides a view for handling native drawing.
    /// </summary>
    public partial class NativeDrawTarget : UserControl, IDrawTarget
    {
        #region Fields

        private Bitmap bitmap;
        private Rectangle lockArea;
        private DrawableWrapper drawable;

        #endregion

        public NativeDrawTarget()
        {
            InitializeComponent();

            this.drawable = new DrawableWrapper(this);
        }

        #region Properties

        public byte[] RawData
        {
            get { return this.rawData; }
        }
        private byte[] rawData;

        #endregion

        #region Methods

        /// <summary>
        /// Handles the drawing routine.
        /// </summary>
        protected override void OnPaint(PaintEventArgs e)
        {
            base.OnPaint(e);

            // Do nothing for design mode.
            if (this.DesignMode) { return; }
            
            // If the raw data array has not been set yet, then assign it.
            if (this.rawData == null) { this.OnSizeChanged(e); }

            BitmapData bitmapData = null;

            try
            {
                // Lock the bits.
                bitmapData = this.bitmap.LockBits(
                    this.lockArea,
                    ImageLockMode.WriteOnly,
                    this.bitmap.PixelFormat);

                // Copy the raw data to the bitmap.
                Marshal.Copy(
                    this.rawData, 
                    0, 
                    bitmapData.Scan0, 
                    this.rawData.Length);
            }
            finally
            {
                // Free the bits.
                if (bitmapData != null)
                {
                    this.bitmap.UnlockBits(bitmapData);
                }
            }

            // Draw the bitmap.
            var g = e.Graphics;
            // TODO Allow larger regions, and use scroll bars.
            g.DrawImage(this.bitmap, 0, 0);
            g.Flush();
        }

        protected override void OnResize(EventArgs e)
        {
            base.OnResize(e);

            // Do nothing in design mode.
            if (this.DesignMode) { return; }

            // If the bitmap is already present, then dispose of it.
            if (this.bitmap != null)
            {
                this.bitmap.Dispose();
                this.bitmap = null;
            }

            // Create the new data-set for the image.
            this.rawData = new byte[this.Width * this.Height * 3];
            this.bitmap = new Bitmap(this.Width, this.Height, PixelFormat.Format24bppRgb);
            this.lockArea = new Rectangle(0, 0, this.Width, this.Height);

            // TODO Provide a timer for drawing.
            this.drawable.Draw();

            // Redraw the region.
            this.Invalidate();
        }

        #endregion
    }
}
