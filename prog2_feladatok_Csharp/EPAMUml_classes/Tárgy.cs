using System;
using System.Text;
using System.Collections;
using System.Collections.Generic;


public class T�rgy
{

	#region Attributes

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


	public List<T�rgy> k�vetelm�nyek
	{
		get
		{
			return m_k�vetelm�nyek;
		}
		private set
		{
			m_k�vetelm�nyek = value;
		}
	}
	private List<T�rgy> m_k�vetelm�nyek = new List<T�rgy>();


	public List<Kurzus> kurzusok
	{
		get
		{
			return m_kurzusok;
		}
		private set
		{
			m_kurzusok = value;
		}
	}
	private List<Kurzus> m_kurzusok = new List<Kurzus>();


	   
	#endregion

	public T�rgy(string k�d, string n�v)
	{
		this.k�d = k�d;
		this.n�v = n�v;
	}

	#region Public methods

	public void addK�vetelm�ny(T�rgy t�rgy)
	{
		k�vetelm�nyek.Add(t�rgy);
	}
	public void addKurzus(Kurzus kurzus)
	{
		kurzusok.Add(kurzus);
	}

	/// <summary>
	/// hallgat�: felvehet?
	/// kurzus: felvesz?
	/// </summary>
	public bool felvesz(Hallgat� hallgat�, Kurzus kurzus)
	{
		return hallgat�.felvehet(this) 
			&& k�vetelm�nyek.TrueForAll(x => hallgat�.teljes�tett_t�rgyak.Contains(x))
			&& kurzus.felvesz(hallgat�);
	}

	public override string ToString()
	{
		return k�d+": "+ n�v;
	}

	#endregion

	public static void test()
	{
		//itt hasznos lenne egy wrapper T�rgyak class (static? singleton?) ami elt�roln� az �sszes classt
		var logika = new T�rgy("101", "Logika");
		var prog0 = new T�rgy("104", "Bevprog");
		var adatb = new T�rgy("209", "Adatb");
		adatb.addK�vetelm�ny(logika);
		var prog1 = new T�rgy("212", "Magas Prog");
		prog1.addK�vetelm�ny(prog0);
		var kalkulus = new T�rgy("207", "Kalkulus");
		var prog2 = new T�rgy("315", "Magas Prog 2");
		prog2.addK�vetelm�ny(prog1);
		var stat = new T�rgy("313", "Statisztika");
		stat.addK�vetelm�ny(kalkulus);
		var g�pi_tan = new T�rgy("934", "G�pi Tanul�s");
		g�pi_tan.addK�vetelm�ny(stat);
		g�pi_tan.addK�vetelm�ny(prog2);
		g�pi_tan.addKurzus(new Kurzus(1, 14, EMintaterv.Tan_Inf�));
		g�pi_tan.addKurzus(new Kurzus(0, 15, EMintaterv.Tan_Inf�));

		var hallg = new Hallgat�("AGT45K", EMintaterv.PTI, "Kov�cs Kov�cs");

		for (int i = 0; i < 14; i++)
		{
			var temp_hallg = new Hallgat�("RANDOM", EMintaterv.PTI, "Randy Random");
			temp_hallg.addTeljT�rgy(stat);
			temp_hallg.addTeljT�rgy(prog2);
			g�pi_tan.felvesz(temp_hallg, g�pi_tan.kurzusok[0]);
		}

		g�pi_tan.felvesz(hallg, g�pi_tan.kurzusok[0]);
		hallg.addTeljT�rgy(stat);
		hallg.addTeljT�rgy(prog2);
		g�pi_tan.felvesz(hallg, g�pi_tan.kurzusok[1]);

	}
}

