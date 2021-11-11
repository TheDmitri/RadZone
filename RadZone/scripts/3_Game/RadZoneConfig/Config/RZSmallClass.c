class RZCreature
{
	string CreatureName;
	int Max;
  float ProbToSpawn;

	void RZCreature(string creaturename, int max, float probtospawn)
	{
		CreatureName = creaturename;
		Max = max;
    ProbToSpawn = probtospawn;
	}
};

class RZSlotProtection
{
	string SlotName;
	ref array<ref ProtectiveClothe>ListProtections;

	void RZSlotProtection(string slotname)
	{
		SlotName = slotname;
		ListProtections = new array<ref ProtectiveClothe>;
	}

	void AddProtectiveClothe(string item_name, int protect_value)
	{
		ListProtections.Insert(new ProtectiveClothe(item_name,protect_value));
	}
};

class ProtectiveClothe
{
	string ClotheName;
	int    Protection;

	void ProtectiveClothe(string clothename, int value)
	{
		ClotheName = clothename;
		Protection = value;
	}
};
