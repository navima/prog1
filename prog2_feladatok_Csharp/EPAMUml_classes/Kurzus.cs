using System;
using System.Text;
using System.Collections;
using System.Collections.Generic;
using System.Linq;


public class Kurzus
{

	#region Attributes

	public int létszám_mintaterv
	{
		get
		{
			return m_létszám_mintaterv;
		}
		private set
		{
			m_létszám_mintaterv = value;
		}
	}
	private int m_létszám_mintaterv;


	public int létszám_nemMintaterv
	{
		get
		{
			return m_létszám_nemMintaterv;
		}
		private set
		{
			m_létszám_nemMintaterv = value;
		}
	}
	private int m_létszám_nemMintaterv;


	public string oktató
	{
		get
		{
			return m_oktató;
		}
		private set
		{
			m_oktató = value;
		}
	}
	private string m_oktató;


	private List<Hallgató> hallgatók_nemMintaterv = new List<Hallgató>();


	private List<Hallgató> hallgatók_mintaterv = new List<Hallgató>();


	private Tárgy parent;

	public EMintaterv mintaterv
	{
		get
		{
			return m_mintaterv;
		}
		private set
		{
			m_mintaterv = value;
		}
	}
	private EMintaterv m_mintaterv;



	#endregion


	public Kurzus(int létszám_mintaterv, int létszám_nemMintaterv, EMintaterv mintaterv)
	{
		this.létszám_mintaterv = létszám_mintaterv;
		this.létszám_nemMintaterv = létszám_nemMintaterv;
		this.mintaterv = mintaterv;
	}

	#region Public methods

	/// <summary>
	/// van hely?
	/// </summary>
	/// <returns>bool</returns>
	public bool felvesz(Hallgató hallgató)
	{
		if (hallgató.mintaterv == mintaterv)
		{
			if (hallgatók_mintaterv.Count < létszám_mintaterv)
			{
				hallgatók_mintaterv.Add(hallgató);
				return true;
			}
		}
		if (hallgatók_nemMintaterv.Count < létszám_nemMintaterv)
		{
			hallgatók_nemMintaterv.Add(hallgató);
			return true;
		}

		return false;
	}

	public override string ToString()
	{
		return hallgatók_mintaterv.Count + "/" + létszám_mintaterv + "  "
			+ hallgatók_nemMintaterv.Count + "/" + létszám_nemMintaterv;
	}

	public List<Hallgató> getHallgatók()
	{
		return hallgatók_mintaterv.Concat(hallgatók_nemMintaterv).ToList();
	}

	#endregion


}

