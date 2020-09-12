using System;
using System.Text;
using System.Collections;
using System.Collections.Generic;

public class Tartozás
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


	public string összeg
	{
		get
		{
			return m_összeg;
		}
		private set
		{
			m_összeg = value;
		}
	}
	private string m_összeg;

	#endregion
}
