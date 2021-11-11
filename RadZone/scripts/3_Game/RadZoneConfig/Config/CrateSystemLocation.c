class RZCrateLocation
{
		string RZContainer;
		int RZMaxLoot;
    string Name;
    vector POS, ORI;

    void RZCrateLocation(int rzmaxloot,string container,string name, vector pos, vector ori)
		{
				RZMaxLoot = rzmaxloot;
				RZContainer = container;
        Name = name;
        POS = pos;
        ORI = ori;
    }
};

class RZ_CSArea
{
	string RZName;
	int RZNbCrate;
	ref array <ref RZCreature>CreaturesLists;
	ref array<ref RZCrateLocation>RZCrateLocations;

	void RZ_CSArea(string name, int nbcrate)
	{
		RZName=name;
		RZNbCrate=nbcrate;
		CreaturesLists = new array<ref RZCreature>;
		RZCrateLocations = new array<ref RZCrateLocation>;
	}

	void AddCratePosition(int rzmaxloot,string container,string name, vector pos, vector ori)
	{
		RZCrateLocations.Insert(new RZCrateLocation(rzmaxloot,container,name,pos,ori));
	}

	void AddCreaturesToList(string creaturename, int max, float probtospawn)
	{
		CreaturesLists.Insert(new RZCreature(creaturename,max,probtospawn));
	}
};
