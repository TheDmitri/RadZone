class RadiationAreaSettings
{
	bool			IsRadiationZoneActive;
	float 		RadChanceVomit;
	float 		RadChanceBleeding;
	float 		RadBloodLossDamage;
	float			RadHealthDamage;
	float 		RadHighMultiplier;
	float     QtyRadReducedPerMin;
	int 			SuitsDamage;
	int       RequiredProtection;
	int      	CriticalProtection;
	float 		ClothesQuantityMultiplier;
	float			AmountGivenAfterCriticalProtection;
	ref array<ref RadiationZoneLocation> RadiationAreaLocation;

	void RadiationAreaSettings() {
		RadiationAreaLocation = new array<ref RadiationZoneLocation>;
	}

	#ifndef DEERISLE
	void RadiationAreaDefaultSettings()	{
		IsRadiationZoneActive = true;
		RadiationAreaLocation.Insert(new RadiationZoneLocation("NEAF", 12153, 12540, 400,false, -1,-1,-1,-1,true,"YOU ARE IN A RADIATION AREA!","YOU LEFT THE RADIATION AREA!",60));
		RadiationAreaLocation.Insert(new RadiationZoneLocation("NWAF", 4584, 10254, 1000,false,-1,-1,-1,-1,true,"YOU ARE IN A RADIATION AREA!","YOU LEFT THE RADIATION AREA!",100));
		RadChanceBleeding = 0.15;
		RadChanceVomit = 0.2;
		RadBloodLossDamage=100;
		RadHealthDamage=2;
		RadHighMultiplier = 2.5;
		QtyRadReducedPerMin = 120;
		SuitsDamage=5;
		RequiredProtection=6;
		CriticalProtection=70;
		ClothesQuantityMultiplier=0.15;
		AmountGivenAfterCriticalProtection = 0.2;
		JsonFileLoader<RadiationAreaSettings>.JsonSaveFile(RZ_RAD_CONFIG, this);
	}
	#else
	void RadiationAreaDefaultSettings()	{
		IsRadiationZoneActive = true;
		RadiationAreaLocation.Insert(new RadiationZoneLocation("PowerPlant", 4749.0, 7098.0, 310,false, -1,-1,-1,-1,true,"YOU ARE IN A RADIATION AREA!","YOU LEFT THE RADIATION AREA!",80));
		RadiationAreaLocation.Insert(new RadiationZoneLocation("Georgestown", 4718.5, 4458.9, 260,false,-1,-1,-1,-1,true,"YOU ARE IN A RADIATION AREA!","YOU LEFT THE RADIATION AREA!",80));
		RadiationAreaLocation.Insert(new RadiationZoneLocation("Greenville", 3292.0, 6313.0, 260,false,-1,-1,-1,-1,true,"YOU ARE IN A RADIATION AREA!","YOU LEFT THE RADIATION AREA!",80));
		RadChanceBleeding = 0.15;
		RadChanceVomit = 0.2;
		RadBloodLossDamage=100;
		RadHealthDamage=2;
		RadHighMultiplier = 2.5;
		QtyRadReducedPerMin = 120;
		SuitsDamage=5;
		RequiredProtection=6;
		CriticalProtection=70;
		ClothesQuantityMultiplier=0.15;
		AmountGivenAfterCriticalProtection = 0.2;
		JsonFileLoader<RadiationAreaSettings>.JsonSaveFile(RZ_RAD_CONFIG, this);
	}
	#endif

	void AddRadZone(string radiationzonestatut, float x, float y, float radius,bool isquarezone,float x1, float y1, float x2, float y2,bool ismsgactive, string msgenterzone, string msgexitzone,int giveradsickness)
	{
		RadiationAreaLocation.Insert(new RadiationZoneLocation(radiationzonestatut,x,y,radius,isquarezone,x1,y1,x2,y2,ismsgactive,msgenterzone, msgexitzone,giveradsickness));
	}


	static ref RadiationAreaSettings Load()	{
		RadiationAreaSettings settings = new RadiationAreaSettings();

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

		if (FileExist(RZ_RAD_CONFIG)) {
			RadZoneJsonLoader<RadiationAreaSettings>.LoadFromFile(RZ_RAD_CONFIG, settings);
			//JsonFileLoader<RadiationAreaSettings>.JsonLoadFile(RZ_RAD_CONFIG, settings);
		}
		else {
			settings.RadiationAreaDefaultSettings();
		}

		return settings;
	}
};
