class RadNukeMissionsAreaSettings
{
	bool      IsActive;
	int       StartDelayAfterRestart;
	int				Duration;
	int       NumberOfPlayers;
	int       NumberOfLevel;
	bool 			IsLootActive;
	bool      IsWarningMsgActive;
	string    WarningMsg;
	bool      IsGlobalWarningMsgActive;
	string    GlobalWarningMsg;
	ref array<ref RadZoneNukeMissionsLocation> RadNukeMissionsAreaLocation;

	void RadNukeMissionsAreaSettings() {
		RadNukeMissionsAreaLocation = new ref array<ref RadZoneNukeMissionsLocation>;
	}

	void RadNukeMissionsAreaDefaultSettings()	{
		IsActive = true;
		StartDelayAfterRestart = 300000;
		Duration = 3600000;
		NumberOfPlayers = 60;
		NumberOfLevel = 1;
		IsLootActive = true;
		IsWarningMsgActive = true;
		WarningMsg = "Warning ! A Plane that contain a Nuke bomb is heading toward ! Run for your life !";
		IsGlobalWarningMsgActive = true;
		GlobalWarningMsg = "Warning ! A Plane that contain a Nuke bomb is heading to: ";
		RadNukeMissionsAreaLocation.Insert(new ref RadZoneNukeMissionsLocation("Severograd", 7899, 12634, 600,90,1,true, "YOU ARE IN AN IRRADIED AREA", "YOU'RE LEAVING AN IRRADIED AREA","THIS AREA IS NO LONGER IRRRADIED", true));
		RadNukeMissionsAreaLocation.Get(0).AddNukeWastesPosition("NukeCrater",Vector(7899.91,113,12634.8));
		RadNukeMissionsAreaLocation.Get(0).AddNukeWastesPosition("IrradiedDirtPile",Vector(7899.91,113,12634.8));
		RadNukeMissionsAreaLocation.Get(0).AddNukeWastesPosition("IrradiedDirtPile",Vector(7724.71,132,12743.1));
		RadNukeMissionsAreaLocation.Get(0).AddNukeWastesPosition("IrradiedDirtPile",Vector(7646.57,119.824,12626.1));
		RadNukeMissionsAreaLocation.Get(0).AddNukeWastesPosition("IrradiedDirtPile",Vector(7731.96,127.236,12485.5));
		RadNukeMissionsAreaLocation.Get(0).AddNukeWastesPosition("IrradiedDirtPile",Vector(7941.87,118.841,12533.2));
		RadNukeMissionsAreaLocation.Get(0).AddNukeWastesPosition("IrradiedDirtPile",Vector(8013.77,129.448,12598.9));
		RadNukeMissionsAreaLocation.Get(0).AddNukeWastesPosition("IrradiedDirtPile",Vector(8145.17,113.128,12680.1));
		RadNukeMissionsAreaLocation.Get(0).AddNukeWastesPosition("IrradiedDirtPile",Vector(8164.3,113.069,12812.6));
		RadNukeMissionsAreaLocation.Get(0).AddNukeWastesPosition("IrradiedDirtPile",Vector(8017.04,113.979,12781.5));
		RadNukeMissionsAreaLocation.Get(0).AddCratePosition(10,"RadiationCase","NukeCleaningReward",Vector(7940.32,123.772,12709.5),Vector(-25.691,0,0));
		RadNukeMissionsAreaLocation.Get(0).AddCratePosition(10,"RadiationCase","NukeCleaningReward",Vector(7910.47,126.364,12605.5),Vector(-80,0,0));
		RadNukeMissionsAreaLocation.Get(0).AddCratePosition(10,"RadiationCase","NukeCleaningReward",Vector(7788.11,121.391,12627.4),Vector(-20,0,0));
		RadNukeMissionsAreaLocation.Get(0).AddCreaturesToList("Animal_CanisLupus_Grey",7,1);
		RadNukeMissionsAreaLocation.Get(0).AddCreaturesToList("Animal_UrsusArctos",1,1);
		RadNukeMissionsAreaLocation.Insert(new ref RadZoneNukeMissionsLocation("NovayaPetrovka", 3446, 13045 , 500, 90,1, true, "YOU ARE IN AN IRRADIED AREA", "YOU'RE LEAVING AN IRRADIED AREA","THIS AREA IS NO LONGER IRRRADIED", true));
		RadNukeMissionsAreaLocation.Get(1).AddNukeWastesPosition("NukeCrater",Vector(3446.57,192.6,13045.8));
		RadNukeMissionsAreaLocation.Get(1).AddNukeWastesPosition("IrradiedDirtPile",Vector(3446.57,192.6,13045.8));
		RadNukeMissionsAreaLocation.Get(1).AddNukeWastesPosition("IrradiedDirtPile",Vector(3335.47,199.68,13029.2));
		RadNukeMissionsAreaLocation.Get(1).AddNukeWastesPosition("IrradiedDirtPile",Vector(3373.63,198.299,13120.4));
		RadNukeMissionsAreaLocation.Get(1).AddNukeWastesPosition("IrradiedDirtPile",Vector(3427.03,198.147,13163));
		RadNukeMissionsAreaLocation.Get(1).AddNukeWastesPosition("IrradiedDirtPile",Vector(3559.32,193.597,13105));
		RadNukeMissionsAreaLocation.Get(1).AddNukeWastesPosition("IrradiedDirtPile",Vector(3429.44,198.078,12856.4));
		RadNukeMissionsAreaLocation.Get(1).AddNukeWastesPosition("IrradiedDirtPile",Vector(3326.28,198.16,12802.1));
		RadNukeMissionsAreaLocation.Get(1).AddNukeWastesPosition("IrradiedDirtPile",Vector(3272.55,200.786,12894.2));
		RadNukeMissionsAreaLocation.Get(1).AddNukeWastesPosition("IrradiedDirtPile",Vector(3419.01,221.4,12733));
		RadNukeMissionsAreaLocation.Get(1).AddCratePosition(10,"RadiationCase","NukeCleaningReward",Vector(3445.64,200.989,13094.2),Vector(-25.691,0,0));
		RadNukeMissionsAreaLocation.Get(1).AddCratePosition(10,"RadiationCase","NukeCleaningReward",Vector(3509.68,192.617,13070.2),Vector(-80,0,0));
		RadNukeMissionsAreaLocation.Get(1).AddCratePosition(10,"RadiationCase","NukeCleaningReward",Vector(3420.3,203.475,12972.9),Vector(-20,0,0));
		RadNukeMissionsAreaLocation.Get(1).AddCreaturesToList("Animal_CanisLupus_Grey",7,1);
		RadNukeMissionsAreaLocation.Get(1).AddCreaturesToList("Animal_UrsusArctos",1,1);
		RadNukeMissionsAreaLocation.Insert(new ref RadZoneNukeMissionsLocation("ZelenoGorsk", 2724, 5309,400,90,1,true, "YOU ARE IN AN IRRADIED AREA", "YOU'RE LEAVING AN IRRADIED AREA","THIS AREA IS NO LONGER IRRRADIED", true));
		RadNukeMissionsAreaLocation.Get(2).AddNukeWastesPosition("NukeCrater",Vector(2724.81,206.2,5309.81));
		RadNukeMissionsAreaLocation.Get(2).AddNukeWastesPosition("IrradiedDirtPile",Vector(2542.15,190.661,5245.5));
		RadNukeMissionsAreaLocation.Get(2).AddNukeWastesPosition("IrradiedDirtPile",Vector(2518.87,193.888,5047.86));
		RadNukeMissionsAreaLocation.Get(2).AddNukeWastesPosition("IrradiedDirtPile",Vector(2808.07,211.004,5448.21));
		RadNukeMissionsAreaLocation.Get(2).AddNukeWastesPosition("IrradiedDirtPile",Vector(2703.41,207.686,5470.91));
		RadNukeMissionsAreaLocation.Get(2).AddNukeWastesPosition("IrradiedDirtPile",Vector(2696.41,206.35,5400.49));
		RadNukeMissionsAreaLocation.Get(2).AddNukeWastesPosition("IrradiedDirtPile",Vector(2803.14,207.241,5374.03));
		RadNukeMissionsAreaLocation.Get(2).AddNukeWastesPosition("IrradiedDirtPile",Vector(2736.52,194.187,5062.97));
		RadNukeMissionsAreaLocation.Get(2).AddCratePosition(10,"RadiationCase","NukeCleaningReward",Vector(2739.1,215.592,5317.12),Vector(159.691,0,0));
		RadNukeMissionsAreaLocation.Get(2).AddCratePosition(10,"RadiationCase","NukeCleaningReward",Vector(2701.5,205.569,5255.81),Vector(-80,0,0));
		RadNukeMissionsAreaLocation.Get(2).AddCratePosition(10,"RadiationCase","NukeCleaningReward",Vector(2670.38,205.676,5286.79),Vector(10,0,0));
		RadNukeMissionsAreaLocation.Get(2).AddCratePosition(10,"RadiationCase","NukeCleaningReward",Vector(2806.04,208.691,5297.97),Vector(100,0,0));
		RadNukeMissionsAreaLocation.Get(2).AddCreaturesToList("Animal_CanisLupus_Grey",7,1);
		RadNukeMissionsAreaLocation.Get(2).AddCreaturesToList("Animal_UrsusArctos",1,1);
		JsonFileLoader<RadNukeMissionsAreaSettings>.JsonSaveFile(RZ_NUKE_MISSION_CONFIG, this);
	}

	static ref RadNukeMissionsAreaSettings Load()	{
		ref RadNukeMissionsAreaSettings settings = new RadNukeMissionsAreaSettings();

		if (FileExist(RZ_NUKE_MISSION_CONFIG)) {
			JsonFileLoader<RadNukeMissionsAreaSettings>.JsonLoadFile(RZ_NUKE_MISSION_CONFIG, settings);
		}
		else {
			settings.RadNukeMissionsAreaDefaultSettings();
		}

		return settings;
	}
};
