class RZLootConfig
{
	string LootName;
	bool   IsWeapon;
	string Magazine;
	float  ProbToSpawn;
	ref array<ref RZAttachmentConfig> AttachmentsToLoot;
	//AttachmentsToItem = NULL;

	void RZLootConfig(string lootname,bool iswpn, string mag, float probtospawn)
	{
		LootName = lootname;
		IsWeapon = iswpn;
		Magazine = mag;
		ProbToSpawn = probtospawn;
		AttachmentsToLoot = new array< ref RZAttachmentConfig>;
	}

	void AddAttachmentsToItem(string name, float prob)
	{
		AttachmentsToLoot.Insert(new RZAttachmentConfig(name,prob));
	}
};

class RZAttachmentConfig
{
	string AttachName;
	float  ProbAttachToSpawn;

	void  RZAttachmentConfig(string attachname, float probattachtospawn)
	{
		AttachName = attachname;
		ProbAttachToSpawn = probattachtospawn;
	}
};

class RZListLootConfig{
	string Name;
	ref array<ref RZLootConfig> Loots;

	void RZListLootConfig(string name)
	{
		Loots= new array<ref RZLootConfig>;
		Name=name;
	}

	void AddLootConfig(string lootname,bool iswpn, string mag, float probtospawn)
	{
		Loots.Insert(new RZLootConfig(lootname,iswpn, mag,probtospawn));
	}
};
