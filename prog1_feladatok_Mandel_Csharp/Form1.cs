using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Numerics;

namespace prog1_feladatok_Mandel_Csharp
{
	public partial class Form1 : Form
	{
		(float, float) limitsR = (-2, 2);
		(float, float) limitsI = (-2, 2);


		bool isPanning = false;
		(float, float) panningScale = (0.001f, 0.001f);
		Point panningStart;
		(float, float) panningLimitsR;
		(float, float) panningLimitsI;

		private short maxiter_ = 20;
		short maxiter
		{
			get { return maxiter_; }
			set
			{
				if (value<1)
					maxiter_ = 1;
				else
					maxiter_ = value;
			}
		}

		(float,float) zoomingScale = (0.001f,0.001f);

		Bitmap MyBitmap;


		public Form1()
		{
			InitializeComponent();

			myPic.MouseWheel += new MouseEventHandler(zoomHandler);
			myPic.MouseDown += new MouseEventHandler(delegate (object sender, MouseEventArgs e) { panningStart = e.Location; panningLimitsR = limitsR; panningLimitsI = limitsI; isPanning = true; });
			myPic.MouseUp += new MouseEventHandler(delegate (object sender, MouseEventArgs e) { isPanning = false; redraw(); });
			myPic.MouseMove += new MouseEventHandler(panHandler);
			//myPic.PreviewKeyDown += new PreviewKeyDownEventHandler(keydownHandler);
			this.KeyDown += new KeyEventHandler(keydownHandler);
		}

		void keydownHandler(object sender, KeyEventArgs e)
		{
			switch(e.KeyData)
			{
				case Keys.Add:
					maxiter+= 1;
					redraw();
					break;
				case Keys.Subtract:
					maxiter -= 1;
					redraw();
					break;
				case Keys.Escape:
					Close();
					break;
				case Keys.R:
					limitsR = (-2, 2);
					limitsI = (-2, 2);
					redraw();
					break;
			}
		}

		void zoomHandler(object sender, MouseEventArgs e)
		{
			float zoomAmountR = (limitsR.Item2 - limitsR.Item1) * e.Delta * zoomingScale.Item1;
			float zoomAmountI = (limitsI.Item2 - limitsI.Item1) * e.Delta * zoomingScale.Item2;

			limitsR = (limitsR.Item1 + zoomAmountR/2, limitsR.Item2-zoomAmountR/2);
			limitsI = (limitsI.Item1 + zoomAmountI/2, limitsI.Item2-zoomAmountI/2);
			redraw();
		}

		void panHandler(object sender, MouseEventArgs e)
		{
			if(isPanning)
			{
				limitsR = (
					(panningStart.Y - e.Y) * panningScale.Item1 * (panningLimitsR.Item2 - panningLimitsR.Item1) + panningLimitsR.Item1,
					(panningStart.Y - e.Y) * panningScale.Item1 * (panningLimitsR.Item2 - panningLimitsR.Item1) + panningLimitsR.Item2);
																   						 						 
				limitsI = (										   						 						 
					(panningStart.X - e.X) * panningScale.Item2 * (panningLimitsI.Item2 - panningLimitsI.Item1) + panningLimitsI.Item1,
					(panningStart.X - e.X) * panningScale.Item2 * (panningLimitsI.Item2 - panningLimitsI.Item1) + panningLimitsI.Item2);

				redraw();
			}
		}

		private void Form1_Load(object sender, EventArgs e)
		{
			redraw();
		}

		void redraw()
		{
			int width = 1024;//(int) (myPic.Width * scale);
			int height = 1024;//(int) (myPic.Height * scale);

			MyBitmap = new Bitmap(width, height, System.Drawing.Imaging.PixelFormat.Format24bppRgb);

			//https://docs.microsoft.com/en-us/dotnet/api/system.drawing.bitmap.lockbits?view=netframework-4.8
			System.Drawing.Imaging.BitmapData bmpData = MyBitmap.LockBits(
				new Rectangle(0, 0, width, height),
				System.Drawing.Imaging.ImageLockMode.ReadWrite,
				MyBitmap.PixelFormat);

			IntPtr ptr = bmpData.Scan0;

			int bytes = Math.Abs(bmpData.Stride) * bmpData.Height;
			byte[] rgbValues = new byte[bytes];

			System.Runtime.InteropServices.Marshal.Copy(ptr, rgbValues, 0, bytes);

			Parallel.For(0, width, (i, state) =>
			  {
				  for (int j = 0; j < height; j++)
				  {
					  int myMandel = mandel(new Complex(
								  (float)i / width * (limitsR.Item2 - limitsR.Item1) + limitsR.Item1,
								  (float)j / height * (limitsI.Item2 - limitsI.Item1) + limitsI.Item1));

					  rgbValues[i * 3 * width + j * 3+2] = (byte)(255-(((float)myMandel / maxiter) * 255));
				  }
			  });

			System.Runtime.InteropServices.Marshal.Copy(rgbValues, 0, ptr, bytes);
			MyBitmap.UnlockBits(bmpData);

			myPic.Image = MyBitmap;
		}

		int mandel(Complex D)
		{
			Complex Z = D;
			int i = 0;
			for(i=0;i<maxiter;i++)
			{
				Z = Z * Z + D;
				if (Z.Magnitude > 2)
					break;
			}
			return i;
		}
	}
}