using System;
using System.Text;
using System.Collections;
using System.Collections.Generic;


public class Hallgató
{

	#region Attributes

	public List<Tartozás> tartozások
	{
		get
		{
			return m_tartozások;
		}
		private set
		{
			m_tartozások = value;
		}
	}
	private List<Tartozás> m_tartozások = new List<Tartozás>();


	public string név
	{
		get
		{
			return m_név;
		}
		private set
		{
			m_név = value;
		}
	}
	private string m_név;


	public string kód
	{
		get
		{
			return m_kód;
		}
		private set
		{
			m_kód = value;
		}
	}
	private string m_kód;


	public List<Tárgy> teljesített_tárgyak
	{
		get
		{
			return m_teljesített_tárgyak;
		}
		private set
		{
			m_teljesített_tárgyak = value;
		}
	}
	private List<Tárgy> m_teljesített_tárgyak = new List<Tárgy>();


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

	public Hallgató(string kód, EMintaterv mintaterv, string név)
	{
		this.kód = kód;
		this.mintaterv = mintaterv;
		this.név = név;
	}

	#region Public methods

	public void addTeljTárgy(Tárgy tárgy)
	{
		teljesített_tárgyak.Add(tárgy);
	}

	/// <summary>
	/// Nincs tartozása
	/// Nem teljesítette még
	/// </summary>
	/// <returns>bool</returns>
	public bool felvehet(Tárgy tárgy)
	{
		return tartozások.Count == 0 && !teljesített_tárgyak.Contains(tárgy);
	}

	public override string ToString()
	{
		return kód + " " + név;
	}

	#endregion
}

