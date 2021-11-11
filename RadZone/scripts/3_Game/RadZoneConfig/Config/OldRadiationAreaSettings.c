class OldRadiationAreaSettings
{
	bool			IsRadiationZoneActive;
	int 			RadCheck;
	float 		RadChanceVomit;
	float 		RadChanceBleeding;
	float 		RadBloodLossDamage;
	float			RadHealthDamage;
	float 		RadHighMultiplier;
	float     QtyRadReducedPerMin;
	int 			SuitsDamage;
	int      	CriticalProtection;
	float 		ClothesQuantityMultiplier;
	float			AmountGivenAfterCriticalProtection;
	ref array<ref OldRadiationZoneLocation> RadiationAreaLocation;

	void OldRadiationAreaSettings() {
		RadiationAreaLocation = new array<ref OldRadiationZoneLocation>;
	}

	void TransformToNewConfig()
	{
		ref RadiationAreaSettings m_RadConfig = new RadiationAreaSettings;
		for(int i = 0; i< RadiationAreaLocation.Count();i++ )
		{
			m_RadConfig.AddRadZone(RadiationAreaLocation.Get(i).RadiationZoneStatut,RadiationAreaLocation.Get(i).X,RadiationAreaLocation.Get(i).Y,RadiationAreaLocation.Get(i).Radius,RadiationAreaLocation.Get(i).IsSquareZone,RadiationAreaLocation.Get(i).X1,RadiationAreaLocation.Get(i).Y1,RadiationAreaLocation.Get(i).X2,RadiationAreaLocation.Get(i).Y2,RadiationAreaLocation.Get(i).IsMsgActive,RadiationAreaLocation.Get(i).MsgEnterZone,RadiationAreaLocation.Get(i).MsgExitZone,RadiationAreaLocation.Get(i).NbSickGivenForRadiation);
		}

		m_RadConfig.IsRadiationZoneActive = IsRadiationZoneActive;
		m_RadConfig.RadChanceBleeding = RadChanceBleeding;
		m_RadConfig.RadChanceVomit = RadChanceVomit;
		m_RadConfig.RadBloodLossDamage=RadBloodLossDamage;
		m_RadConfig.RadHealthDamage=RadHealthDamage;
		m_RadConfig.RadHighMultiplier = RadHighMultiplier;
		m_RadConfig.QtyRadReducedPerMin = QtyRadReducedPerMin;
		m_RadConfig.SuitsDamage=SuitsDamage;
		m_RadConfig.RequiredProtection=6;
		m_RadConfig.CriticalProtection=CriticalProtection;
		m_RadConfig.ClothesQuantityMultiplier=ClothesQuantityMultiplier;
		m_RadConfig.AmountGivenAfterCriticalProtection = AmountGivenAfterCriticalProtection;
		JsonFileLoader<RadiationAreaSettings>.JsonSaveFile(RZ_RAD_CONFIG, m_RadConfig);
	}

	static ref OldRadiationAreaSettings Load()	{
		OldRadiationAreaSettings settings = new OldRadiationAreaSettings();

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

		if (FileExist(RZ_OLDRAD_CONFIG) && !FileExist(RZ_RAD_CONFIG)) {
			JsonFileLoader<OldRadiationAreaSettings>.JsonLoadFile(RZ_OLDRAD_CONFIG, settings);
			settings.TransformToNewConfig();
		}
		else {
			Print("no old config found");
		}

		return settings;
	}
}
