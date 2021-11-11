class RZCrateSystemAreaSettings
{
	ref array<ref RZListLootConfig>ListLoots;
	ref array<ref RZ_CSArea>AreaLocation;
	int 			TimerLoot;
	bool 			IsCrateSystemActive;

	void CrateSystemAreaSettings() {
		AreaLocation = new array<ref RZ_CSArea>;
		ListLoots = new array<ref RZListLootConfig>;
	}

	void RZCrateSystemDefaultSettings()	{
		IsCrateSystemActive = 1;
		TimerLoot=2700000;
		AreaLocation = new array<ref RZ_CSArea>;
		AreaLocation.Insert(new RZ_CSArea("NWAF",1));
		AreaLocation.Get(0).AddCratePosition(10,"RadiationCase","Army2",Vector(4623.64,343.319,9557.33),Vector(0,0,0));
		AreaLocation.Get(0).AddCratePosition(10,"RadiationCase","Army2",Vector(4552.65,343.319,9553.44),Vector(0,0,0));
		AreaLocation.Get(0).AddCratePosition(10,"RadiationCase","Army2",Vector(4556.09,339.572,9528.47),Vector(-177.000000, 0.000000, -0.000000));
		AreaLocation.Get(0).AddCratePosition(10,"RadiationCase","Army2",Vector(4622.56,346.5,9549.5),Vector(65.000000, 0.000000, -0.000000));
		AreaLocation.Get(0).AddCratePosition(10,"RadiationCase","Army2",Vector(4446.36,343.694,9619.97),Vector(35.000000, 0.000000, -0.000000));
		AreaLocation.Get(0).AddCratePosition(10,"RadiationCase","Army2",Vector(4485.57,342.459,9674.85),Vector(-90.000000, 0.000000, -0.000000));
		AreaLocation.Get(0).AddCratePosition(10,"RadiationCase","Army2",Vector(4545.88,339.075,9690.74),Vector(0.000000, 0.000000, -0.000000));
		AreaLocation.Get(0).AddCreaturesToList("Animal_CanisLupus_Grey",7,1);
		AreaLocation.Get(0).AddCreaturesToList("Animal_UrsusArctos",1,1);
		AreaLocation.Insert(new RZ_CSArea("NEAF",1));
		AreaLocation.Get(1).AddCratePosition(10,"RadiationCase","Army2",Vector(11860.2,141.061,12423.5),Vector(-65,0,0));
		AreaLocation.Get(1).AddCratePosition(10,"RadiationCase","Army2",Vector(11856.7,140.581,12461.4),Vector(-165,2.99368e-06,-2.74181e-06));
		AreaLocation.Get(1).AddCratePosition(10,"RadiationCase","Army2",Vector(11830.7,140.706,12462.1),Vector(20.000000, 0.000000, -0.000000));
		AreaLocation.Get(1).AddCratePosition(10,"RadiationCase","Army2",Vector(11839,141.344,12472.7),Vector(115.000000, 0.000000, -0.000000));
		AreaLocation.Get(1).AddCratePosition(10,"RadiationCase","Army2",Vector(11817,147.111,12542.6),Vector(-53.000000, 0.000000, -0.000000));
		AreaLocation.Get(1).AddCratePosition(10,"RadiationCase","Army2",Vector(11801.1,140.244,12576.3),Vector(58.000000, 0.000000, -0.000000));
		AreaLocation.Get(1).AddCratePosition(10,"RadiationCase","Army2",Vector(12439.1,141.42,12514.5),Vector(171.000000, 0.000000, -0.000000));
		AreaLocation.Get(1).AddCreaturesToList("Animal_CanisLupus_Grey",7,1);
		AreaLocation.Get(1).AddCreaturesToList("Animal_UrsusArctos",1,1);
		ListLoots = new array<ref RZListLootConfig>;
		ListLoots.Insert(new RZListLootConfig("NukeCleaningReward"));
		ListLoots.Get(0).AddLootConfig("AKM",true,"Mag_AKM_Drum75Rnd",0.6);
		ListLoots.Get(0).Loots.Get(0).AddAttachmentsToItem("PSO1Optic",0.5);
		ListLoots.Get(0).Loots.Get(0).AddAttachmentsToItem("AK_Suppressor",0.3);
		ListLoots.Get(0).Loots.Get(0).AddAttachmentsToItem("AK_PlasticHndgrd",0.85);
		ListLoots.Get(0).Loots.Get(0).AddAttachmentsToItem("AK_RailHndgrd_Black",0.85);
		ListLoots.Get(0).Loots.Get(0).AddAttachmentsToItem("AK_Bayonet",0.4);
		ListLoots.Get(0).Loots.Get(0).AddAttachmentsToItem("AK_FoldingBttstck_Black",0.6);
		ListLoots.Get(0).AddLootConfig("M4A1",true,"Mag_STANAGCoupled_30Rnd",0.6);
		ListLoots.Get(0).Loots.Get(1).AddAttachmentsToItem("ACOGOptic",0.4);
		ListLoots.Get(0).Loots.Get(1).AddAttachmentsToItem("M4_CarryHandleOptic",0.6);
		ListLoots.Get(0).Loots.Get(1).AddAttachmentsToItem("M4_CQBBttstck",0.7);
		ListLoots.Get(0).Loots.Get(1).AddAttachmentsToItem("M4_MPBttstck",0.4);
		ListLoots.Get(0).Loots.Get(1).AddAttachmentsToItem("M4_MPHndgrd",0.7);
		ListLoots.Get(0).Loots.Get(1).AddAttachmentsToItem("M4_RISHndgrd",0.5);
		ListLoots.Get(0).Loots.Get(1).AddAttachmentsToItem("M4_Suppressor",0.4);
		ListLoots.Get(0).AddLootConfig("SVD",true,"Mag_SVD_10Rnd",0.4);
		ListLoots.Get(0).Loots.Get(2).AddAttachmentsToItem("PSO1Optic",0.35);
		ListLoots.Get(0).AddLootConfig("AK74",true,"Mag_AK74_30Rnd",0.6);
		ListLoots.Get(0).Loots.Get(3).AddAttachmentsToItem("AK_RailHndgrd_Black",0.7);
		ListLoots.Get(0).Loots.Get(3).AddAttachmentsToItem("AK74_WoodBttstck",0.7);
		ListLoots.Get(0).Loots.Get(3).AddAttachmentsToItem("AK_Bayonet",0.6);
		ListLoots.Get(0).Loots.Get(3).AddAttachmentsToItem("AK_FoldingBttstck_Black",0.7);
		ListLoots.Get(0).Loots.Get(3).AddAttachmentsToItem("AK_Suppressor",0.45);
		ListLoots.Insert(new RZListLootConfig("Army2"));
		ListLoots.Get(1).AddLootConfig("FAL",true,"Mag_FAL_20Rnd",0.3);
		ListLoots.Get(1).Loots.Get(0).AddAttachmentsToItem("Fal_FoldingBttstck",0.85);
		ListLoots.Get(1).Loots.Get(0).AddAttachmentsToItem("Fal_OeBttstck",0.75);
		ListLoots.Get(1).Loots.Get(0).AddAttachmentsToItem("ACOGOptic",0.45);
		ListLoots.Get(1).AddLootConfig("AmmoBox_545x39_20Rnd",false,"",0.8);
		ListLoots.Get(1).AddLootConfig("AmmoBox_556x45_20Rnd",false,"",0.8);
		ListLoots.Get(1).AddLootConfig("SVD",true,"Mag_SVD_10Rnd",0.4);
		ListLoots.Get(1).Loots.Get(2).AddAttachmentsToItem("PSO1Optic",0.35);
		ListLoots.Get(1).AddLootConfig("AK74",true,"Mag_AK74_30Rnd",0.6);
		ListLoots.Get(1).Loots.Get(3).AddAttachmentsToItem("AK_RailHndgrd_Black",0.7);
		ListLoots.Get(1).Loots.Get(3).AddAttachmentsToItem("AK74_WoodBttstck",0.7);
		ListLoots.Get(1).Loots.Get(3).AddAttachmentsToItem("AK_Bayonet",0.6);
		ListLoots.Get(1).Loots.Get(3).AddAttachmentsToItem("AK_FoldingBttstck_Black",0.7);
		ListLoots.Get(1).Loots.Get(3).AddAttachmentsToItem("AK_Suppressor",0.45);
		JsonFileLoader<RZCrateSystemAreaSettings>.JsonSaveFile(RZ_CS_CONFIG, this);
	}

	static ref RZCrateSystemAreaSettings Load()	{
		RZCrateSystemAreaSettings settings = new RZCrateSystemAreaSettings();

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

		if (FileExist(RZ_CS_CONFIG)) {
			//JsonFileLoader<RZCrateSystemAreaSettings>.JsonLoadFile(RZ_CS_CONFIG, settings);
			RadZoneJsonLoader<RZCrateSystemAreaSettings>.LoadFromFile(RZ_CS_CONFIG, settings);
			JsonFileLoader<RZCrateSystemAreaSettings>.JsonSaveFile(RZ_CS_CONFIG, settings);
		}
		else {
			settings.RZCrateSystemDefaultSettings();
		}

		return settings;
	}
};
