class RadZoneNukeMissionsLocation
{
  string RadZoneStatut;
  float X, Y, Radius;
  int NbSickGivenForRadiation;
  int Level;
  bool IsMsgActive;
  string MsgEnterZone;
  string MsgExitZone;
  string MsgAreaClean;
  bool IsLootActive;
	ref array<ref NukeWasteListe>NukeWastesPosition;
  ref array<ref RZCrateLocation>RewardsLocations;
  ref array<ref RZCreature>CreaturesLists;

  void RadZoneNukeMissionsLocation(string radzonestatut, float x, float y, float radius,int nbradgiven,int level,bool ismsgactive, string msgenterzone, string msgexitzone, string msgareaclean, bool islootactive)
	{
    RadZoneStatut = radzonestatut;
    X = x;
    Y = y;
    Radius = radius;
    NbSickGivenForRadiation = nbradgiven;
    Level = level;
    IsMsgActive = ismsgactive;
    MsgEnterZone = msgenterzone;
    MsgExitZone = msgexitzone;
    MsgAreaClean = msgareaclean;
    IsLootActive = islootactive;
		NukeWastesPosition = new ref array<ref NukeWasteListe>;
    RewardsLocations = new ref array<ref RZCrateLocation>;
    CreaturesLists = new ref array<ref RZCreature>;
  }

  void AddCreaturesToList(string creaturename, int max, float probtospawn)
  {
    CreaturesLists.Insert(new ref RZCreature(creaturename,max,probtospawn));
  }

	void AddNukeWastesPosition(string name, vector pos)
	{
		NukeWastesPosition.Insert(new ref NukeWasteListe(name,pos));
	}

  void AddCratePosition(int rzmaxloot,string container,string name, vector pos, vector ori)
  {
    RewardsLocations.Insert(new ref RZCrateLocation(rzmaxloot,container,name,pos,ori));
  }
};

class NukeWasteListe
{
	string Name;
	vector Pos;

	void NukeWasteListe(string name, vector pos)
	{
		Name=name;
		Pos=pos;
	}
};
