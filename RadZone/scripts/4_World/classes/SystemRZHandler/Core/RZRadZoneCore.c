class RZRadZoneCore
{
	ref OldRadiationAreaSettings m_OldRadiationAreaSettings;

	ref RadiationAreaSettings m_ActiveRadiationAreaSettings;
	ref RZCrateSystemAreaSettings m_ActiveRZCrateSystemSettings;
	ref ClotheProtectionSettings m_ClotheProtectionSettings;
	ref ClotheProtectionSettings m_ClotheProtectionSettingsClient;
	ref RadiationLocations m_RadiationLocations;

	#ifdef RZNM
	ref RadNukeMissionsAreaSettings m_ActiveRadNukeMissionsAreaSettings;
	ref RZRadNukeMissionsZoneServer m_RZRadNukeMissionsZoneServer;
	#endif

  ref RZRadZoneClient m_RZRadZoneClient;
  ref RZRadZoneServer m_RZRadZoneServer;
	ref RZCrateSystem m_RZCrateSystem;

	void RZRadZoneCore()
  {
		GetRZLogger().LogInfo("RZRadZoneCore - Started ! => Loading config...");
		#ifdef RZDEBUG
		GetRZLogger().LogInfo("DEBUG MODE ENABLED");
		#endif
		if (GetGame().IsServer() || !GetGame().IsMultiplayer())
		{
			//LOADING CONFIG FILES...
			GetRZLogger().LogInfo("Checking if old config...");
			m_OldRadiationAreaSettings = OldRadiationAreaSettings.Load();
			GetRZLogger().LogInfo("Current config loading...");
			m_ClotheProtectionSettings = ClotheProtectionSettings.Load();
			m_ActiveRZCrateSystemSettings = RZCrateSystemAreaSettings.Load();
			m_ActiveRadiationAreaSettings = RadiationAreaSettings.Load();

			//Creating server side part of the cratesystem
			if(m_ActiveRZCrateSystemSettings.IsCrateSystemActive)
			{
				m_RZCrateSystem = new RZCrateSystem;
			}

			//Creating server side part of radzone
			if(m_ActiveRadiationAreaSettings.IsRadiationZoneActive)
			{
				m_RZRadZoneServer = new RZRadZoneServer;
			}

			#ifdef RZNM
			m_ActiveRadNukeMissionsAreaSettings = RadNukeMissionsAreaSettings.Load();
			GetRZLogger().LogInfo("[RZNUKEMISSIONS]:Loading nuke mission done.");
			//Creating server side part of radzonemission
			if(m_ActiveRadNukeMissionsAreaSettings.IsActive)
			{
				m_RZRadNukeMissionsZoneServer = new RZRadNukeMissionsZoneServer;
			}
			#endif
		}
		else
		{
			//Creation of an other protection config on client side
			m_ClotheProtectionSettingsClient = new ClotheProtectionSettings;

			m_RZRadZoneClient = new RZRadZoneClient;
		}
		InitRPC();
  }

	void ~RZRadZoneCore(){
  }

	void InitRPC()
		{
			if (GetGame().IsServer())	{
				//Server calls
				GetRPCManager().AddRPC("RZRadZone", "GetRadStatut", m_RZRadZoneServer, SingeplayerExecutionType.Client);
				GetRPCManager().AddRPC("RZRadZone", "GetRadQtyToClothesRequest", m_RZRadZoneServer, SingeplayerExecutionType.Client);
				GetRPCManager().AddRPC("RZRadZone", "GetSickQtyToGive", m_RZRadZoneServer, SingeplayerExecutionType.Client);
				GetRPCManager().AddRPC("RZRadZone", "GetDamageClotheRequest", m_RZRadZoneServer, SingeplayerExecutionType.Client);
				#ifdef RZNM
				GetRPCManager().AddRPC("RZRadZoneNM", "GetPlayerPosFromNukeToServer", m_RZRadNukeMissionsZoneServer, SingeplayerExecutionType.Client);
				#endif
			}
			else	{
				//Client calls
				GetRPCManager().AddRPC("RZRadZone", "GetRadConfigResponse", m_RZRadZoneClient, SingeplayerExecutionType.Server);
				GetRPCManager().AddRPC("RZRadZone", "GetRadZoneClotheConfigRequest", this, SingeplayerExecutionType.Server);
				#ifdef RZNM
				GetRPCManager().AddRPC("RZRadZoneNM", "GetRadNukeMissionsConfigResponse", m_RZRadZoneClient, SingeplayerExecutionType.Server);
				GetRPCManager().AddRPC("RZRadZoneNM", "GetPlayerPosFromNukeFromServer", m_RZRadZoneClient, SingeplayerExecutionType.Server);
				GetRPCManager().AddRPC("RZRadZoneNM", "StopRadZone", m_RZRadZoneClient, SingeplayerExecutionType.Server);
				#endif
			}
		}

		//----------------------------------RPC PART---------------------------------------------------//
		void TransfertClotheProtectionConfigToClient(PlayerIdentity idy = NULL)
		{
			bool rep = false;
			for(int i = 0;i<m_ClotheProtectionSettings.RZListSlotProtection.Count();i++)
			{
				ClotheConfigTemp m_ClotheConfigTemp;
			  m_ClotheConfigTemp = new ClotheConfigTemp(i,m_ClotheProtectionSettings);
				if(i == -1 + m_ClotheProtectionSettings.RZListSlotProtection.Count())rep = true;
				GetRPCManager().SendRPC("RZRadZone", "GetRadZoneClotheConfigRequest", new Param2<ref ClotheConfigTemp,bool>(m_ClotheConfigTemp,rep), true, idy);
	      m_ClotheConfigTemp=NULL;
			}
		}

		void GetRadZoneClotheConfigRequest(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
		{
				if (!GetGame().IsClient())
						return;
				Param2<ref ClotheConfigTemp,bool> data;
				if (!ctx.Read(data))
						return;
				ClotheConfigTemp m_ClotheConfigTemp = data.param1;
				m_ClotheProtectionSettingsClient.AddRZListSlotProtection(m_ClotheConfigTemp.SlotName);
				m_ClotheProtectionSettingsClient.AddProtectiveClothes(m_ClotheConfigTemp.ClothesNames,m_ClotheConfigTemp.Protection);
				m_ClotheConfigTemp = NULL;
				if(data.param2)
				{
					JsonFileLoader<ClotheProtectionSettings>.JsonSaveFile(RZ_CP_CONFIG, m_ClotheProtectionSettingsClient);
				}
		}
		//------------------------------------------------------------------------------------------------//
};
