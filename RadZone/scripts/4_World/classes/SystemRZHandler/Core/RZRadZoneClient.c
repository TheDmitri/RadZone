class RZRadZoneClient
{
  int             NbSickGivenForRadiation=0;
  bool						RZStatut = false;
  int             ClothesProtection = 0;
  int             RadQtyOnClothes = 0;
  int             InnerRad = 0;
	string          RZName="";
  bool            HasStarted = false;

  private ref array<string>m_Suits = {"GP5GasMask","NBCHoodBase","NBCJacketBase","NBCGloves_ColorBase","NBCPantsBase","NBCBootsBase"};
  private ref array<string>m_SLOTS = {"Mask","Headgear","Body","Gloves","Legs","Feet"};

  ref RadiationLocations m_RadiationLocations;

  #ifdef RZNM
  ref RadZoneNukeMissionsLocation m_RadZoneNukeMissionsLocation;
  #endif

  private PluginRadStatus m_RZModuleRadStatus;

	void RZRadZoneClient()
  {
      m_RZModuleRadStatus = PluginRadStatus.Cast(GetPlugin(PluginRadStatus));
  }

  void ~RZRadZoneClient(){
  }


  void StartRadCheck()
  {
      HasStarted = true;
      //GetGame().GetMission().MissionScript.Call( this, "RadZoneCheck", null );
      //GetGame().GetMission().MissionScript.Call( this, "IsInsideRadZone", null );
      GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(IsInsideRadZone, 60000, true);
      GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(RadZoneCheck, 2000, true);
  }

  private void IsInsideRadZone()
  {
      if (RZStatut == true) //Already in zone
      {
        RadCheckClient();
        RadQtyOnClothesHandler();
      }
  }

  private void RadZoneCheck()
	{
            PlayerBase m_player = PlayerBase.Cast(GetGame().GetPlayer());
            if(m_player)
            {
              if( m_RadiationLocations )
              {
          			for(int i = 0 ; i<= -1 + m_RadiationLocations.X1.Count() ; i++)
          			{
                  if(RZStatut  && RZName != m_RadiationLocations.Statut.Get(i))continue;
          				if( m_RadiationLocations.IsSquareZone.Get(i) == 1)
          				{
          					RadiationZoneSquare(m_player,m_player.GetPosition(),m_RadiationLocations.Xc.Get(i),m_RadiationLocations.Yc.Get(i),m_RadiationLocations.X1.Get(i),m_RadiationLocations.Y1.Get(i),m_RadiationLocations.X2.Get(i),m_RadiationLocations.Y2.Get(i),m_RadiationLocations.Statut.Get(i),m_RadiationLocations.NbRadGiven.Get(i),m_RadiationLocations.IsMsgActive.Get(i),m_RadiationLocations.MsgEnterZone.Get(i),m_RadiationLocations.MsgExitZone.Get(i));
          				}
          				else
          				{
          					RadiationZoneRound(m_player,m_player.GetPosition(),m_RadiationLocations.X.Get(i),m_RadiationLocations.Y.Get(i),m_RadiationLocations.Radius.Get(i),m_RadiationLocations.Statut.Get(i),m_RadiationLocations.NbRadGiven.Get(i),m_RadiationLocations.IsMsgActive.Get(i),m_RadiationLocations.MsgEnterZone.Get(i),m_RadiationLocations.MsgExitZone.Get(i));
          				}
          			}
              }
              #ifdef RZNM
              if(m_RadZoneNukeMissionsLocation)
              {
                if((!RZStatut && RZName=="") || (RZStatut && RZName==m_RadZoneNukeMissionsLocation.RadZoneStatut)
                {
                  RadiationZoneRound(m_player,m_player.GetPosition(),m_RadZoneNukeMissionsLocation.X,m_RadZoneNukeMissionsLocation.Y,m_RadZoneNukeMissionsLocation.Radius,m_RadZoneNukeMissionsLocation.RadZoneStatut,m_RadZoneNukeMissionsLocation.NbSickGivenForRadiation,m_RadZoneNukeMissionsLocation.IsMsgActive,m_RadZoneNukeMissionsLocation.MsgEnterZone,m_RadZoneNukeMissionsLocation.MsgExitZone);
                }
              }
              #endif
            }
            else
            {
              RZStatut = false;
              RZName = "";
              NbSickGivenForRadiation = 0;
              RadQtyOnClothes = 0;
              ClothesProtection = 0;
              m_RadiationLocations = NULL;
              #ifdef RZNM
              m_RadZoneNukeMissionsLocation = NULL;
              #endif
            }
	}

  void RadiationZoneRound(PlayerBase m_player , vector pos,float m_X, float m_Y, float Zone_Radius,string Status,int m_NbSickGivenForRadiation,bool ismsgactive, string msgenterzone, string msgexitzone)
  {
    pos[1]=0;
    vector center = Vector(m_X,0,m_Y);
    float dist = vector.Distance(center, pos);
    if(m_NbSickGivenForRadiation > 0)
    {
      float coeff = m_NbSickGivenForRadiation / Zone_Radius;
      NbSickGivenForRadiation = (Zone_Radius-dist)*coeff;
    }else NbSickGivenForRadiation = -1 * m_NbSickGivenForRadiation;
    if(NbSickGivenForRadiation < 0)NbSickGivenForRadiation=0;
    if ( dist <= Zone_Radius )
		{
      if (RZName!=Status && !RZStatut) //Already in zone
			{
        RZName=Status;
        RZStatut=true;
        SetRadLogoHasToBeVisible(true);
        DisplayRadUI(true);
        SendRadZoneStatut(RZName, RZStatut);
        if(!ismsgactive)return;
        NotificationSystem.AddNotificationExtended( 4, Status, msgenterzone, "RadZone_Data/images/radiation.paa" );
      }
    }
    else
			{
        if (RZName==Status && RZStatut)
				{
          RZName="";
          RZStatut=false;
          NbSickGivenForRadiation = 0;
          SetRadLogoHasToBeVisible(false);
          DisplayRadUI(false);
          SendRadQtyToClothesRequest(RadQtyOnClothes);
          RadQtyOnClothes = 0;
          SendRadZoneStatut(RZName, RZStatut);
          if(!ismsgactive)return;
          NotificationSystem.AddNotificationExtended( 4, Status, msgexitzone, "RadZone_Data/images/radiation.paa" );
				}
			}
  }

  void 	RadiationZoneSquare(PlayerBase m_player ,vector pos,float m_Xc, float m_Yc, float m_X1, float m_Y1, float m_X2, float m_Y2,string Status,int m_NbSickGivenForRadiation,bool ismsgactive, string msgenterzone, string msgexitzone)
	{
    float dist = vector.Distance(Vector(pos[0],0,pos[2]),Vector(m_Xc,0,m_Yc));
    float dist_max = vector.Distance(Vector(m_X1,0,m_Y1),Vector(m_Xc,0,m_Yc));
    float coeff = m_NbSickGivenForRadiation / dist;
    NbSickGivenForRadiation = (dist_max-dist)*coeff;
    if(m_NbSickGivenForRadiation < 0) NbSickGivenForRadiation = -1 * m_NbSickGivenForRadiation;
    if(NbSickGivenForRadiation < 0)NbSickGivenForRadiation=0;

    if ( pos[0]>m_X1 && pos[0]<m_X2 && pos[2]>m_Y1 && pos[2]< m_Y2 )
		{
      if (RZName!=Status && !RZStatut) //Already in zone
			{
        RZName=Status;
        RZStatut=true;
        SetRadLogoHasToBeVisible(true);
        DisplayRadUI(true);
        SendRadZoneStatut( Status, true);
        if(!ismsgactive)return;
        NotificationSystem.AddNotificationExtended( 4, Status, msgenterzone, "RadZone_Data/images/radiation.paa" );
      }
    }
    else
			{
        if (RZName==Status && RZStatut)
				{
          RZName="";
          RZStatut=false;
          NbSickGivenForRadiation = 0;
          SendRadQtyToClothesRequest(RadQtyOnClothes);
          RadQtyOnClothes = 0;
          SetRadLogoHasToBeVisible(false);
          DisplayRadUI(false);
          SendRadZoneStatut( Status, false);
          if(!ismsgactive)return;
          NotificationSystem.AddNotificationExtended( 4, Status, msgexitzone, "RadZone_Data/images/radiation.paa" );
				}
			}
	}

  private void RadQtyOnClothesHandler()
  {
    int amount = NbSickGivenForRadiation*m_RadiationLocations.ClothesQuantityMultiplier;
    if( amount > RadQtyOnClothes)
    {
      RadQtyOnClothes = amount;
    }
    //Print("RadQtyOnClothes: "+RadQtyOnClothes.ToString());
  }


  void RadCheckClient()
  {
    PlayerBase m_player = PlayerBase.Cast(GetGame().GetPlayer());
    if(!m_player)return;
    if(m_player.InnerRadQty!=0)InnerRad=m_player.InnerRadQty;
    ClothesCheckClient(m_player);

    #ifdef RZDEBUG
    GetRZLogger().LogInfo("ClothesProtection:" + ClothesProtection.ToString());
    #endif

    if( m_RadiationLocations.RequiredProtection <= ClothesProtection && NbSickGivenForRadiation < m_RadiationLocations.CriticalProtection)
    {
      return;
    }
    else
    {
      float radtogive = 0;
      if(NbSickGivenForRadiation >= m_RadiationLocations.CriticalProtection)
      {
        radtogive = NbSickGivenForRadiation*m_RadiationLocations.AmountGivenAfterCriticalProtection;
        SendRadDamageOnClothes();
      }
      if(m_RadiationLocations.RequiredProtection > ClothesProtection)
      {
        radtogive += NbSickGivenForRadiation*(1.0-ClothesProtection/m_RadiationLocations.RequiredProtection*1.0);
      }

      #ifdef RZDEBUG
      GetRZLogger().LogInfo("radtogive:" + radtogive.ToString());
      #endif

      SendGiveSicknessAmount(radtogive);
    }
  }

  void ClothesCheckClient(PlayerBase player)
  {
      ClothesProtection=0;
      for (int i = 0; i <= -1 + GetClothesConfigClient().RZListSlotProtection.Count() ;i++)
      {
        EntityAI SuitsPart;
        string slotname = GetClothesConfigClient().RZListSlotProtection.Get(i).SlotName;
        SuitsPart = player.FindAttachmentBySlotName(slotname);
        ClothesProtection +=GetProtectionLevel(SuitsPart, i, slotname);
      }
  }

  float GetProtectionLevel(EntityAI attch, int i, string slotname)
  {
    int protection = 0;
    if(!attch || attch.IsRuined())return 0;
    if(slotname == "Mask" && attch.GetCompEM().IsWorking())return 1;
    for(int j=0;j<= -1 + GetClothesConfigClient().RZListSlotProtection.Get(i).ListProtections.Count();j++)
    {
      if(attch.IsKindOf(GetClothesConfigClient().RZListSlotProtection.Get(i).ListProtections.Get(j).ClotheName))
      {
          protection = GetClothesConfigClient().RZListSlotProtection.Get(i).ListProtections.Get(j).Protection;
          return protection;
      }
    }
    return protection;
  }

    void GetRadConfigResponse(CallType type,  ParamsReadContext ctx,  PlayerIdentity sender,  Object target)
    {
        if (!GetGame().IsClient())
            return;
        Param1<ref RadiationLocations> data;
        if (!ctx.Read(data))
            return;
        m_RadiationLocations = data.param1;

        //JsonFileLoader<RadiationLocations>.JsonSaveFile(RZ_RAD_CONFIG, m_RadiationLocations);
        if(!HasStarted)
        StartRadCheck();
    }

    void SendRadZoneStatut( string name, bool rep)
    {
      #ifdef RZDEBUG
      GetRZLogger().LogInfo("SendRadZoneStatut");
      #endif
      GetRPCManager().SendRPC("RZRadZone", "GetRadStatut",  new Param2<string,bool>(name,rep), true, NULL);
    }

    void SendRadQtyToClothesRequest(int nbrad)
    {
      if(nbrad < 1)return;
      InnerRad += nbrad;

      #ifdef RZDEBUG
      GetRZLogger().LogInfo("SendRadQtyToClothesRequest");
      #endif

      GetRPCManager().SendRPC("RZRadZone", "GetRadQtyToClothesRequest", new Param1<int>(nbrad), true, NULL);
    }

    void SendRadDamageOnClothes()
    {
      #ifdef RZDEBUG
      GetRZLogger().LogInfo("SendRadDamageOnClothes");
      #endif

      GetRPCManager().SendRPC("RZRadZone", "GetDamageClotheRequest", NULL, true, NULL);
    }

    void SendGiveSicknessAmount(float radtogive)
    {
      #ifdef RZDEBUG
      GetRZLogger().LogInfo("SendGiveSicknessAmount:"+radtogive.ToString());
      #endif

      PlayerBase m_player = PlayerBase.Cast(GetGame().GetPlayer());
      if(m_player.InnerRadQty>=600 || radtogive == 0)return;
      GetRPCManager().SendRPC("RZRadZone", "GetSickQtyToGive", new Param1<float>(radtogive), true);
    }

    //-----------------Helpers function to deal with the rad icon in the ingamehug-----------------------//
    void DisplayRadOutText(bool rep)
    {
      if(m_RZModuleRadStatus)
      {
        m_RZModuleRadStatus.DisplayRadOutText(rep);
      }
    }

    void SetRadLogoHasToBeVisible(bool rep)
    {
      if(m_RZModuleRadStatus)
      {
        m_RZModuleRadStatus.SetRadLogoHasToBeVisible(rep);
      }
    }

    void DisplayRadUI(bool rep)
    {
      if(m_RZModuleRadStatus)
      {
        m_RZModuleRadStatus.DisplayRadUI(rep);
      }
    }

    void DisplayRadInText(bool rep)
    {
      if(m_RZModuleRadStatus && ( !GetGame().IsServer()  ||  !GetGame().IsMultiplayer() ))
      {
        m_RZModuleRadStatus.DisplayRadInText(rep);
      }
    }

    void SetRadInText(int nrad )
    {
      if(m_RZModuleRadStatus)
      {
        m_RZModuleRadStatus.SetRadInText(nrad);
      }
    }

    void SetRadOutText(int nrad)
    {
      if(m_RZModuleRadStatus )
      {
        m_RZModuleRadStatus.SetRadOutText(nrad);
      }
    }
    //-------------------------------------------------------------------------------------------------//
    #ifdef RZNM
    //------------------------------RPC regarding the Nuke Addon---------------------------------------//
    void GetRadNukeMissionsConfigResponse(CallType type,  ParamsReadContext ctx,  PlayerIdentity sender,  Object target)
    {
        if (!GetGame().IsClient())
            return;
        Param1<ref RadZoneNukeMissionsLocation> data;
        if (!ctx.Read(data))
            return;
        m_RadZoneNukeMissionsLocation = NULL;
        m_RadZoneNukeMissionsLocation = data.param1;

        if(!HasStarted)
        StartRadCheck();

        #ifdef RZDEBUG
        GetRZLogger().LogInfo("GetRadNukeMissionsConfigResponse");
        #endif
    }

    void StopRadZone(CallType type,  ParamsReadContext ctx,  PlayerIdentity sender,  Object target)
    {
        if (!GetGame().IsClient())
            return;
        NotificationSystem.AddNotificationExtended(3.5, RZName, m_RadZoneNukeMissionsLocation.MsgAreaClean, "RadZone_Data/images/radiation.paa" );
        PlayerBase m_player = PlayerBase.Cast(GetGame().GetPlayer());
        if(m_player && RZName == m_RadZoneNukeMissionsLocation.RadZoneStatut)
        {
          RZName = "";
          RZStatut=false;
          NbSickGivenForRadiation = 0;
          SendRadZoneStatut(RZName, RZStatut);
          SetRadLogoHasToBeVisible(false);
          DisplayRadUI(false);
        }
        m_RadZoneNukeMissionsLocation = NULL;

        #ifdef RZDEBUG
        GetRZLogger().LogInfo("StopRadZone");
        #endif
    }

    void GetPlayerPosFromNukeFromServer(CallType type,  ParamsReadContext ctx,  PlayerIdentity sender,  Object target)
    {
        if (!GetGame().IsClient())
            return;
        Param2<float, float> data;
        if (!ctx.Read(data))
            return;
        float m_X = data.param1;
        float m_Y = data.param2;

        PlayerBase pl = PlayerBase.Cast(GetGame().GetPlayer());
        vector pos = pl.GetPosition();
        pos[1]=0;
        vector center = Vector(m_X,0,m_Y);
        float dist = vector.Distance(center, pos);
        int rep = 3;

        if(dist < 300)
        {
          rep = 0;
        }else if(dist < 500){
          rep = 1;
        }
        GetRPCManager().SendRPC("RZRadZoneNM", "GetPlayerPosFromNukeToServer",  new Param1<int>(rep), true, NULL);
        #ifdef RZDEBUG
        GetRZLogger().LogInfo("GetPlayerPosFromNukeFromServer");
        #endif
    }
    //-------------------------------------------------------------------------------------------------//
    #endif
};
