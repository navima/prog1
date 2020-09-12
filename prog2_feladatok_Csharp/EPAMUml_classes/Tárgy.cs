using System;
using System.Text;
using System.Collections;
using System.Collections.Generic;


public class Tárgy
{

	#region Attributes

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


	public List<Tárgy> követelmények
	{
		get
		{
			return m_követelmények;
		}
		private set
		{
			m_követelmények = value;
		}
	}
	private List<Tárgy> m_követelmények = new List<Tárgy>();


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

	public Tárgy(string kód, string név)
	{
		this.kód = kód;
		this.név = név;
	}

	#region Public methods

	public void addKövetelmény(Tárgy tárgy)
	{
		követelmények.Add(tárgy);
	}
	public void addKurzus(Kurzus kurzus)
	{
		kurzusok.Add(kurzus);
	}

	/// <summary>
	/// hallgató: felvehet?
	/// kurzus: felvesz?
	/// </summary>
	public bool felvesz(Hallgató hallgató, Kurzus kurzus)
	{
		return hallgató.felvehet(this) 
			&& követelmények.TrueForAll(x => hallgató.teljesített_tárgyak.Contains(x))
			&& kurzus.felvesz(hallgató);
	}

	public override string ToString()
	{
		return kód+": "+ név;
	}

	#endregion

	public static void test()
	{
		//itt hasznos lenne egy wrapper Tárgyak class (static? singleton?) ami eltárolná az összes classt
		var logika = new Tárgy("101", "Logika");
		var prog0 = new Tárgy("104", "Bevprog");
		var adatb = new Tárgy("209", "Adatb");
		adatb.addKövetelmény(logika);
		var prog1 = new Tárgy("212", "Magas Prog");
		prog1.addKövetelmény(prog0);
		var kalkulus = new Tárgy("207", "Kalkulus");
		var prog2 = new Tárgy("315", "Magas Prog 2");
		prog2.addKövetelmény(prog1);
		var stat = new Tárgy("313", "Statisztika");
		stat.addKövetelmény(kalkulus);
		var gépi_tan = new Tárgy("934", "Gépi Tanulás");
		gépi_tan.addKövetelmény(stat);
		gépi_tan.addKövetelmény(prog2);
		gépi_tan.addKurzus(new Kurzus(1, 14, EMintaterv.Tan_Infó));
		gépi_tan.addKurzus(new Kurzus(0, 15, EMintaterv.Tan_Infó));

		var hallg = new Hallgató("AGT45K", EMintaterv.PTI, "Kovács Kovács");

		for (int i = 0; i < 14; i++)
		{
			var temp_hallg = new Hallgató("RANDOM", EMintaterv.PTI, "Randy Random");
			temp_hallg.addTeljTárgy(stat);
			temp_hallg.addTeljTárgy(prog2);
			gépi_tan.felvesz(temp_hallg, gépi_tan.kurzusok[0]);
		}

		gépi_tan.felvesz(hallg, gépi_tan.kurzusok[0]);
		hallg.addTeljTárgy(stat);
		hallg.addTeljTárgy(prog2);
		gépi_tan.felvesz(hallg, gépi_tan.kurzusok[1]);

	}
}

