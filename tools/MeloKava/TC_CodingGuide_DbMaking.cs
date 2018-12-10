using System;
using System.Collections.Generic;
using System.Diagnostics;

namespace ConsoleApp
{
	public struct SampleElement
	{
		public string name;

		public int pa;
		public int pd;
		public int ma;
		public int md;
		public int max;
		public int ix_img;
		public int ix_comment;

		static public SampleElement create(string name, int[] attrib)
		{
			Debug.Assert(attrib.Length == 7);

			SampleElement inst = new SampleElement();

			inst.name = name;

			int ix = 0;
			inst.pa = attrib[ix++];
			inst.pd = attrib[ix++];
			inst.ma = attrib[ix++];
			inst.md = attrib[ix++];
			inst.max = attrib[ix++];
			inst.ix_img = attrib[ix++];
			inst.ix_comment = attrib[ix++];

			return inst;
		}
	};

	public class SampleElementPair : List<KeyValuePair<string, SampleElement>>
	{
		public void Add(string id, string name, int[] attrib)
		{
			Add(new KeyValuePair<string, SampleElement>(id, SampleElement.create(name, attrib)));
		}
	}

	class DaBase
	{
		public static readonly KeyValuePair<string, SampleElement>[] sample_element_list = new SampleElementPair
		{
			{ "WS-001", "Name 001", new int[] { 0, 0, 1, 1, 1, 1, 0 }},
			{ "WS-002", "Name 002", new int[] { 0, 0, 1, 1, 1, 1, 0 }}
		}.ToArray();
	}

	class TC_CodingGuide_DbMaking
	{
		static void Main(string[] args)
		{
			var found = Array.Find(DaBase.sample_element_list, p => p.Key == "WS-002");
			Console.WriteLine("OK - FOUND: " + found.Value.name);

			var not_found = Array.Find(DaBase.sample_element_list, p => p.Key == "NOT_EXIST");
			if (not_found.Key == null)
				Console.WriteLine("OK - NOT FOUND");
		}
	}
}

/*
	class Inst
	{
		public int ix_meti;
		public int plus;
		public int[] slots;
		public bool curd;
		public bool unid;

		public bool merge(Inst ref_inst)
		{
			if (this.ix_meti != ref_inst.ix_meti)
				return false;

			int add = (ref_inst.plus > 0) ? ref_inst.plus : 1;
			this.plus += add;

			// TODO: slots

			return true;
		}

		static public Inst create(int ix, int plus, int[] slots)
		{
			Inst inst = new Inst();
			inst.ix_meti = ix;
			inst.plus = plus;
			inst.slots = null;
			inst.curd = false;
			inst.unid = false;

			if (slots != null && slots.Length > 0)
				inst.slots = slots;
			else
				inst.slots = new int[0];

			return inst;
		}
	};

	Inst i1 = Inst.create(0, 2, null);
	Inst i2 = Inst.create(0, 1, new int[] { 3, 0 } );

	i1.merge(i2);

 */
