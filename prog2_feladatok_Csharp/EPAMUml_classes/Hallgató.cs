using System;
using System.Text;
using System.Collections;
using System.Collections.Generic;


public class Hallgat�
{

	#region Attributes

	public List<Tartoz�s> tartoz�sok
	{
		get
		{
			return m_tartoz�sok;
		}
		private set
		{
			m_tartoz�sok = value;
		}
	}
	private List<Tartoz�s> m_tartoz�sok = new List<Tartoz�s>();


	public string n�v
	{
		get
		{
			return m_n�v;
		}
		private set
		{
			m_n�v = value;
		}
	}
	private string m_n�v;


	public string k�d
	{
		get
		{
			return m_k�d;
		}
		private set
		{
			m_k�d = value;
		}
	}
	private string m_k�d;


	public List<T�rgy> teljes�tett_t�rgyak
	{
		get
		{
			return m_teljes�tett_t�rgyak;
		}
		private set
		{
			m_teljes�tett_t�rgyak = value;
		}
	}
	private List<T�rgy> m_teljes�tett_t�rgyak = new List<T�rgy>();


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

	public Hallgat�(string k�d, EMintaterv mintaterv, string n�v)
	{
		this.k�d = k�d;
		this.mintaterv = mintaterv;
		this.n�v = n�v;
	}

	#region Public methods

	public void addTeljT�rgy(T�rgy t�rgy)
	{
		teljes�tett_t�rgyak.Add(t�rgy);
	}

	/// <summary>
	/// Nincs tartoz�sa
	/// Nem teljes�tette m�g
	/// </summary>
	/// <returns>bool</returns>
	public bool felvehet(T�rgy t�rgy)
	{
		return tartoz�sok.Count == 0 && !teljes�tett_t�rgyak.Contains(t�rgy);
	}

	public override string ToString()
	{
		return k�d + " " + n�v;
	}

	#endregion
}

