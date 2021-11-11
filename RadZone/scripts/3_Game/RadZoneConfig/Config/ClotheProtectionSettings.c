class ClotheProtectionSettings
{
	ref array<ref RZSlotProtection> RZListSlotProtection;

	void ClotheProtectionSettings() {
		RZListSlotProtection = new array<ref RZSlotProtection>;
	}

	void ClotheProtectionDefaultSettings()
	{
		RZListSlotProtection.Insert(new RZSlotProtection("Mask"));
		RZListSlotProtection.Get(0).AddProtectiveClothe("GP5GasMask",0);
		RZListSlotProtection.Insert(new RZSlotProtection("Headgear"));
		RZListSlotProtection.Get(1).AddProtectiveClothe("NBCHoodBase",1);
		RZListSlotProtection.Insert(new RZSlotProtection("Body"));
		RZListSlotProtection.Get(2).AddProtectiveClothe("NBCJacketBase",1);
		RZListSlotProtection.Insert(new RZSlotProtection("Gloves"));
		RZListSlotProtection.Get(3).AddProtectiveClothe("NBCGloves_ColorBase",1);
		RZListSlotProtection.Insert(new RZSlotProtection("Legs"));
		RZListSlotProtection.Get(4).AddProtectiveClothe("NBCPantsBase",1);
		RZListSlotProtection.Insert(new RZSlotProtection("Feet"));
		RZListSlotProtection.Get(5).AddProtectiveClothe("NBCBootsBase",1);
		JsonFileLoader<ClotheProtectionSettings>.JsonSaveFile(RZ_CP_CONFIG, this);
	}

	void AddRZListSlotProtection(string slotname)
	{
		RZListSlotProtection.Insert(new ref RZSlotProtection(slotname));
	}

	void AddProtectiveClothes(ref array<string> clothes,ref array<int>protections)
	{
		for(int i = 0;i<clothes.Count();i++)
		{
			int k = -1 + RZListSlotProtection.Count();
			RZListSlotProtection.Get(k).AddProtectiveClothe(clothes.Get(i),protections.Get(i));
		}
	}

	static ref ClotheProtectionSettings Load()	{
		ClotheProtectionSettings settings = new ClotheProtectionSettings();

		if ( !FileExist( RZ_CONFIG_ROOT_SERVER ) )
		{
			MakeDirectory( RZ_CONFIG_ROOT_SERVER );
			if ( !FileExist( RZ_CONFIG_DIR_SERVER ) )
			{
				MakeDirectory( RZ_CONFIG_DIR_SERVER );
			}
			if ( !FileExist( RZ_LOGGER_DIR_SERVER ) )
			{
				MakeDirectory( RZ_LOGGER_DIR_SERVER );
			}
		}

		if (FileExist(RZ_CP_CONFIG)) {
		  RadZoneJsonLoader<ClotheProtectionSettings>.LoadFromFile(RZ_CP_CONFIG, settings);
			//JsonFileLoader<ClotheProtectionSettings>.JsonLoadFile(RZ_CP_CONFIG, settings);
		}
		else {
			settings.ClotheProtectionDefaultSettings();
		}

		return settings;
	}
};
