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

		private ushort maxiter_ = 20;
		ushort maxiter
		{
			get { return maxiter_; }
			set
			{
				if (value < 1)
					maxiter_ = 1;
				else
					maxiter_ = value;
			}
		}

		(float,float) zoomingScale = (0.001f,0.001f);

		Bitmap MyBitmap;

		bool isSelected = false;
		Complex selection;


		public Form1()
		{
			InitializeComponent();

			myPic.MouseWheel += new MouseEventHandler(zoomHandler);
			myPic.MouseDown += new MouseEventHandler(delegate (object sender, MouseEventArgs e) 
			{
				switch (e.Button)
				{
					case MouseButtons.Left:
						panningStart = e.Location;
						panningLimitsR = limitsR;
						panningLimitsI = limitsI;
						isPanning = true;
						break;
					case MouseButtons.None:
						break;
					case MouseButtons.Right:
						if(isSelected)
						{
							isSelected = false;
						}
						else
						{
							isSelected = true;
							selection = clientToComplex(flip(e.Location), flip(myPic.Size));
							redraw();
						}
						break;
					case MouseButtons.Middle:
						break;
					case MouseButtons.XButton1:
						break;
					case MouseButtons.XButton2:
						break;
					default:
						break;
				}
			});
			myPic.MouseUp += new MouseEventHandler(delegate (object sender, MouseEventArgs e) 
			{
				switch (e.Button)
				{
					case MouseButtons.Left:
						isPanning = false; redraw();
						break;
					case MouseButtons.None:
						break;
					case MouseButtons.Right:
						break;
					case MouseButtons.Middle:
						break;
					case MouseButtons.XButton1:
						break;
					case MouseButtons.XButton2:
						break;
					default:
						break;
				}
			});
			myPic.MouseMove += new MouseEventHandler(panHandler);
			this.KeyDown += new KeyEventHandler(keydownHandler);
		}

		void drawSelected(Complex Z)
		{
			using (var g = Graphics.FromImage(myPic.Image))
			{
				g.FillRectangle(Brushes.AliceBlue, 0, 0, 250, 120);
			}
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
			if(isSelected)
			{
				selection = clientToComplex(flip(e.Location), flip(myPic.Size));
				redraw();
			}
		}

		private void Form1_Load(object sender, EventArgs e)
		{
			redraw();
		}

		void redraw()
		{
			int width = 1024;
			int height = 1024;

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
					  //uint myMandel = biom(new Complex(
					  //	  (float)i / width * (limitsR.Item2 - limitsR.Item1) + limitsR.Item1,
					  //	  (float)j / height * (limitsI.Item2 - limitsI.Item1) + limitsI.Item1));

					  uint myMandel = mandel(clientToComplex(new Point(i, j), new Size(width, height)));

					  rgbValues[i * 3 * width + j * 3+2] = (byte)(255-(((float)myMandel / maxiter) * 255));
				  }
			  });

			System.Runtime.InteropServices.Marshal.Copy(rgbValues, 0, ptr, bytes);
			MyBitmap.UnlockBits(bmpData);

			using (var g = Graphics.FromImage(MyBitmap))
			{
				if(limitsR.Item1 < selection.Real && selection.Real < limitsR.Item2)
				{
					g.DrawLine(Pens.AliceBlue, new Point(0,0), flip(complexToClient(selection, MyBitmap.Size)));
					g.DrawLines(Pens.AliceBlue, flip(complexToClient(GetChainMandel(selection),MyBitmap.Size)));
				}
			}


			myPic.Image = MyBitmap;
		}

		uint mandel(Complex D)
		{
			Complex Z = D;
			uint i = 0;
			for(i=0; i<maxiter; i++)
			{
				Z = Z * Z + D;
				if (Z.Magnitude > 2)
					break;
			}
			return i;
		}

		Complex[] GetChainMandel(Complex D)
		{
			List<Complex> chain = new List<Complex>();
			chain.Add(new Complex(0, 0));
			Complex Z = D;
			uint i = 0;
			for (i = 0; i < maxiter; i++)
			{
				chain.Add(Z);
				Z = Z * Z + D;
				if (Z.Magnitude > 2)
					break;
			}
			return chain.ToArray();
		}

		Point[] complexToClient(Complex[] complices, Size clientSize)
		{
			Point[] points = new Point[complices.Length];
			for(int i = 0;i<complices.Length; i++)
			{
				points[i] = complexToClient(complices[i], clientSize);
			}
			return points;
		}

		uint biom(Complex Z_)
		{
			Complex Z = Z_;
			Complex D = new Complex(-0.8, 0.156);
			Complex V = new Complex(0, 0);
			float R = 2;

			uint i = 0;
			for (i = 0; i < maxiter; i++)
			{
				V = Z*Z+D;
				Z = V*V+D;
				i++;

				if (Z.Magnitude > R)
					break;
			}
			return i;
		}

		Point complexToClient(Complex Z, Size clientSize)
		{
			return new Point(
				(int)((Z.Real - limitsR.Item1) / (limitsR.Item2 - limitsR.Item1) * clientSize.Width),
				(int)((Z.Imaginary - limitsI.Item1) / (limitsI.Item2 - limitsI.Item1) * clientSize.Height));
		}

		Point flip(Point A)
		{
			return new Point(A.Y, A.X);
		}

		Point[] flip(Point[] A)
		{
			Point[] points = new Point[A.Length];
			for (int i = 0; i < A.Length; i++)
				points[i] = flip(A[i]);
			return points;
		}

		Complex flip (Complex A)
		{
			return new Complex(A.Imaginary, A.Real);
		}

		Size flip(Size A)
		{
			return new Size(A.Height, A.Width);
		}

		Complex clientToComplex(Point client, Size clientSize)
		{
			return new Complex(
				client.X / (float)clientSize.Width * (limitsR.Item2 - limitsR.Item1) + limitsR.Item1,
				client.Y / (float)clientSize.Height * (limitsI.Item2 - limitsI.Item1) + limitsI.Item1);
		}
	}
}