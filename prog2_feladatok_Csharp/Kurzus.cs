using System;
using System.Text;
using System.Collections;
using System.Collections.Generic;
using System.Linq;


public class Kurzus
{

	#region Attributes

	public int l�tsz�m_mintaterv
	{
		get
		{
			return m_l�tsz�m_mintaterv;
		}
		private set
		{
			m_l�tsz�m_mintaterv = value;
		}
	}
	private int m_l�tsz�m_mintaterv;


	public int l�tsz�m_nemMintaterv
	{
		get
		{
			return m_l�tsz�m_nemMintaterv;
		}
		private set
		{
			m_l�tsz�m_nemMintaterv = value;
		}
	}
	private int m_l�tsz�m_nemMintaterv;


	public string oktat�
	{
		get
		{
			return m_oktat�;
		}
		private set
		{
			m_oktat� = value;
		}
	}
	private string m_oktat�;


	private List<Hallgat�> hallgat�k_nemMintaterv = new List<Hallgat�>();


	private List<Hallgat�> hallgat�k_mintaterv = new List<Hallgat�>();


	private T�rgy parent;

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


	public Kurzus(int l�tsz�m_mintaterv, int l�tsz�m_nemMintaterv, EMintaterv mintaterv)
	{
		this.l�tsz�m_mintaterv = l�tsz�m_mintaterv;
		this.l�tsz�m_nemMintaterv = l�tsz�m_nemMintaterv;
		this.mintaterv = mintaterv;
	}

	#region Public methods

	/// <summary>
	/// van hely?
	/// </summary>
	/// <returns>bool</returns>
	public bool felvesz(Hallgat� hallgat�)
	{
		if (hallgat�.mintaterv == mintaterv)
		{
			if (hallgat�k_mintaterv.Count < l�tsz�m_mintaterv)
			{
				hallgat�k_mintaterv.Add(hallgat�);
				return true;
			}
		}
		if (hallgat�k_nemMintaterv.Count < l�tsz�m_nemMintaterv)
		{
			hallgat�k_nemMintaterv.Add(hallgat�);
			return true;
		}

		return false;
	}

	public override string ToString()
	{
		return hallgat�k_mintaterv.Count + "/" + l�tsz�m_mintaterv + "  "
			+ hallgat�k_nemMintaterv.Count + "/" + l�tsz�m_nemMintaterv;
	}

	public List<Hallgat�> getHallgat�k()
	{
		return hallgat�k_mintaterv.Concat(hallgat�k_nemMintaterv).ToList();
	}

	#endregion


}

