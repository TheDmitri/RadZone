class RZRadNukeMissionsZoneServer
{
  EntityAI m_Loot=NULL;
  House m_RZSiren;
  ref array<ref IrradiedDirtPile> m_NukeWastes = new array<ref IrradiedDirtPile>;
  ref array<EntityAI> m_LootList = new array<EntityAI>;
  ref array<Object> DeadWolfObjs = new array<Object>;
  int m_CheckScheduler;

  ref array<ref RadZoneNukeMissionsLocation> RZRadLists;
  ref RadZoneNukeMissionsLocation RZRadZonePicked;

  void RZRadNukeMissionsZoneServer()
  {
    RZRadLists = new array<ref RadZoneNukeMissionsLocation>;
    GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(this.InitStartRZNM, 1000);
  }

  void InitStartRZNM()
  {
      int m_min = (GetRZNMConfig().StartDelayAfterRestart/1000)/60;
      GetRZLogger().LogInfo("[RZNUKEMISSIONS] - Started ! Launch in "+m_min.ToString()+" min");
      int delay = GetRZNMConfig().StartDelayAfterRestart + GetRZNMConfig().Duration;
      GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(this.StartRZNM, GetRZNMConfig().StartDelayAfterRestart);
      GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(CleanAndTempoNextDrop, delay, true);
  }

  void CleanAndTempoNextDrop()
  {
    RZRadLists.Clear();
    RZRadZonePicked=NULL;
    CheckParticlesStatus();
    CheckCreaturesStatus();
    GetRZLogger().LogInfo("[RZNUKEMISSIONS] - Mission got cleaned - waiting before new drop...");
    GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(this.StartRZNM, GetRZNMConfig().StartDelayAfterRestart);
  }


  void StartRZNM()
  {
    GetRZLogger().LogInfo("[RZNUKEMISSIONS] - Start RadZone Nuke Mission - StartRZNM()");
    array<Man> m_Players = new array<Man>;
    GetGame().GetPlayers(m_Players);
    int Nb_Players = m_Players.Count();
    int step = GetRZNMConfig().NumberOfPlayers / GetRZNMConfig().NumberOfLevel;
    for(int i = 0; i < GetRZNMConfig().NumberOfLevel;i++ )
    {
      if(Nb_Players <= step*(i+1))
      {
        //We add in an array the RZ that got the desired level
        for(int j=0; j<GetRZNMConfig().RadNukeMissionsAreaLocation.Count();j++)
        {
          if(GetRZNMConfig().RadNukeMissionsAreaLocation.Get(i).Level == (i+1))
          {
            RZRadLists.Insert(GetRZNMConfig().RadNukeMissionsAreaLocation.Get(j));
            //GetRZLogger().LogInfo("[RZNUKEMISSIONS] - Zone added to RZRadLists");
          }
        }
        //GetTempArrayList(RZRadLists);
        //we picked randomly the RZ that wll spawn
        int rand_result = Math.RandomIntInclusive(0,-1 + RZRadLists.Count());
        RZRadZonePicked = RZRadLists.Get(rand_result);
        GetPickedZoneInfo(); //Get Log about which zone has been picked
        SendNotifIfInRZ(); //Send a notification to every player that are currently into the bombing area
        SendGlobalNotif();
        StartSiren(); //pretty obvious I guess
        StartPlane();
        //GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(this.StartAfterDelay, 95000);
        return;
      }
    }
  }

  void StartPlane()
  {
    vector destination;
    vector startinglocation;
    destination[0]=RZRadZonePicked.X;
    destination[2]=RZRadZonePicked.Y;

    float angle = Math.RandomIntInclusive(-1,1)*Math.RandomFloatInclusive(0,3.14);
    startinglocation[0] = destination[0] + 3000 * Math.Cos(angle);
    startinglocation[2] = destination[2] + 3000 * Math.Sin(angle);

    GetRZLogger().LogInfo("starting location: X:" +startinglocation[0].ToString() + " Y:" + startinglocation[2].ToString());
    startinglocation=snapToGround(startinglocation);
    startinglocation[1]=startinglocation[1]+400;
    NukeBomber m_NukeBomber = NukeBomber.Cast(GetGame().CreateObject( "NukeBomber", startinglocation, false, true, true));
    m_NukeBomber.SetPosition(startinglocation);
    m_NukeBomber.SetOrientation(Vector(180,0,0));
    m_NukeBomber.SetDirection(startinglocation - destination);
    m_NukeBomber.SetupBomber(destination);
  }

  void GetTempArrayList(ref array<ref RadZoneNukeMissionsLocation> m_array)
  {
      int cpt = m_array.Count() - 1;
      GetRZLogger().LogInfo("------------------------------------------------------");
      for(int i = 0;i<=cpt;i++)
      {
          string msg = "[RZNUKEMISSIONS] Debug Print Array :Name :"+m_array.Get(i).RadZoneStatut;
          GetRZLogger().LogInfo(msg);
      }
      GetRZLogger().LogInfo("------------------------------------------------------");
  }

  void StopSiren()
  {
      GetGame().ObjectDelete(m_RZSiren);
  }

  //Just to get some log about what's going on
  void GetPickedZoneInfo()
  {
      string msg = "[RZNUKEMISSIONS] - Name:"+RZRadZonePicked.RadZoneStatut + " pos: X:" + RZRadZonePicked.X.ToString() + " Z:" + RZRadZonePicked.Y.ToString();
      GetRZLogger().LogInfo(msg);
  }

  void StartSiren()
  {
      GetRZLogger().LogInfo("[RZNUKEMISSIONS] - Siren is played - StartSiren");
      vector pos;
      pos[0] = RZRadZonePicked.X;
      pos[2] = RZRadZonePicked.Y;
      pos = snapToGround(pos);
      m_RZSiren = House.Cast(GetGame().CreateObject( "RZSiren", pos, false, true, true));
  }

  void StartAfterExplosion()
  {
    StopSiren();
    GetRPCManager().SendRPC("RZRadZoneNM", "GetPlayerPosFromNukeFromServer", new Param2<float, float>(RZRadZonePicked.X,RZRadZonePicked.Y), true, NULL);
    GetRPCManager().SendRPC("RZRadZoneNM", "GetRadNukeMissionsConfigResponse", new Param1<ref RadZoneNukeMissionsLocation>(RZRadZonePicked), true, NULL);
    GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(this.StartNukeWastesEffect, 85000);
  }

  void SendRZNMConfigToClient(PlayerIdentity sender)
  {
      if(RZRadZonePicked)
      {
          GetRPCManager().SendRPC("RZRadZoneNM", "GetRadNukeMissionsConfigResponse", new Param1<ref RadZoneNukeMissionsLocation>(RZRadZonePicked), true, sender);
      }
  }

  void StartNukeWastesEffect()
  {
    GetRZLogger().LogInfo("[RZNUKEMISSIONS] - StartParticles");
    int cpt = RZRadZonePicked.NukeWastesPosition.Count() - 1;
    for (int k=0;k<=cpt;k++)
    {
      GetRZLogger().LogInfo("[RZNUKEMISSIONS] - Spawned nukewastes");
      vector pos = RZRadZonePicked.NukeWastesPosition.Get(k).Pos;
      pos = snapToGround(pos);
      IrradiedDirtPile m_tempWastes = IrradiedDirtPile.Cast(GetGame().CreateObject(RZRadZonePicked.NukeWastesPosition.Get(k).Name,pos));
      m_NukeWastes.Insert(m_tempWastes);
    }
    for(int i = 0;i<RZRadZonePicked.CreaturesLists.Count();i++)
    {
      for(int j = 0;j<RZRadZonePicked.CreaturesLists.Get(i).Max;j++)
      {
        if(RZRadZonePicked.CreaturesLists.Get(i).ProbToSpawn > Math.RandomFloatInclusive(0,1))
        {
          vector offset;
          offset[0] = RZRadZonePicked.X + Math.RandomIntInclusive(-RZRadZonePicked.Radius,RZRadZonePicked.Radius);
          offset[2] = RZRadZonePicked.Y + Math.RandomIntInclusive(-RZRadZonePicked.Radius,RZRadZonePicked.Radius);
          string creature = RZRadZonePicked.CreaturesLists.Get(i).CreatureName;
          Object m_creature=GetGame().CreateObject(creature, snapToGround(offset), false, true, true);
          DeadWolfObjs.Insert(m_creature);
        }
      }
    }
  }

  void CheckNukeWaste(vector pos)
  {
    GetRZLogger().LogInfo("[RZNUKEMISSIONS] - CheckNukeWaste");
    GetRZLogger().LogInfo("[RZNUKEMISSIONS] - CheckNukeWaste : Remaining"+m_NukeWastes.Count().ToString());
    for(int i = 0; i < m_NukeWastes.Count(); i++){
      if(m_NukeWastes.Get(i).GetPosition()==pos){
        m_NukeWastes.Get(i).RZDelete();
        m_NukeWastes.Remove(i);
      }
    }
    if(m_NukeWastes == NULL || m_NukeWastes.Count() == 0)
    {
      GetRZLogger().LogInfo("[RZNUKEMISSIONS] - m_NukeWastes == NULL");
      GetRPCManager().SendRPC("RZRadZoneNM", "StopRadZone", NULL, true, NULL);
      GiveRewardCase();
      RZRadZonePicked = NULL;
      m_NukeWastes.Clear();
    }
  }

  void GiveRewardCase()
  {
    GetRZLogger().LogInfo("[RZNUKEMISSIONS] - GiveRewardCase");
    CheckCreaturesStatus();
    CheckRadCaseListStatus();
    if(RZRadZonePicked.IsLootActive != 1)return;
    int cpt = -1 + RZRadZonePicked.RewardsLocations.Count();
    int pickedcrate = Math.RandomIntInclusive(0,cpt);
    vector pos = RZRadZonePicked.RewardsLocations.Get(pickedcrate).POS;
    vector ori = RZRadZonePicked.RewardsLocations.Get(pickedcrate).ORI;
    pos = snapToGround(pos);
    CreateEzDrop(RZRadZonePicked.RewardsLocations.Get(pickedcrate).RZMaxLoot,RZRadZonePicked.RewardsLocations.Get(pickedcrate).RZContainer,pos, ori,RZRadZonePicked.RewardsLocations.Get(pickedcrate).Name);
  }

  void CreateEzDrop(int maxloot, string container_name,vector v, vector o, string name)
  {
    int SpawnSeed = RZGetTimeStamp();
		Math.Randomize(SpawnSeed);
    int k,temp;
    if(v[1]==0)v[1]=GetGame().SurfaceY(v[0], v[2]);
    m_Loot = EntityAI.Cast(GetGame().CreateObject( container_name, v, false, true, true));
    m_Loot.SetOrientation(o);
    m_LootList.Insert(m_Loot);
    GetRZLogger().LogInfo("[RZNM - LOOTREWARD]: RadiationCaseSpawned:"+" CrateName: "+ name + "- Position: X:"+v[0].ToString()+" Y:"+v[1].ToString()+" Z:"+v[2].ToString());
    int count=-1+GetCrateSystemConfig().ListLoots.Count();
    for(int i=0; i<=count;i++)
    {
      if(GetCrateSystemConfig().ListLoots.Get(i).Name==name){
        k=i;
      }
    }
    for(int l=0;l<GetCrateSystemConfig().ListLoots.Get(k).Loots.Count();l++)
    {
      if(temp>=maxloot && maxloot!=-1)continue;
      if ( GetCrateSystemConfig().ListLoots.Get(k).Loots.Get(l).ProbToSpawn > Math.RandomFloatInclusive(0,1) )
      {
        if (GetCrateSystemConfig().ListLoots.Get(k).Loots.Get(l).AttachmentsToLoot.Count() == 0)
        {
          m_Loot.GetInventory().CreateInInventory(GetCrateSystemConfig().ListLoots.Get(k).Loots.Get(l).LootName);
          temp+=1;
          GetRZLogger().LogInfo(GetCrateSystemConfig().ListLoots.Get(k).Loots.Get(l).LootName);
          continue;
        }
        else
        {
          m_Loot.GetInventory().CreateInInventory(GetCrateSystemConfig().ListLoots.Get(k).Loots.Get(l).LootName);
          temp+=1;
          GetRZLogger().LogInfo(GetCrateSystemConfig().ListLoots.Get(k).Loots.Get(l).LootName);
          for( int parc=0; parc < GetCrateSystemConfig().ListLoots.Get(k).Loots.Get(l).AttachmentsToLoot.Count() ; parc++)
          {
            if ( GetCrateSystemConfig().ListLoots.Get(k).Loots.Get(l).AttachmentsToLoot.Get(parc).ProbAttachToSpawn > Math.RandomFloatInclusive(0,1) )
            {
              m_Loot.GetInventory().CreateInInventory(GetCrateSystemConfig().ListLoots.Get(k).Loots.Get(l).AttachmentsToLoot.Get(parc).AttachName);
              temp+=1;
              GetRZLogger().LogInfo(GetCrateSystemConfig().ListLoots.Get(k).Loots.Get(l).AttachmentsToLoot.Get(parc).AttachName);
            }
          }
        }
      }
    }
  }

  void CheckCreaturesStatus()
  {
    GetRZLogger().LogInfo("[RZNM - LOOTSYSTEM]: [CreatureCleaner] !");
    if(DeadWolfObjs.Count() == 0){
      GetRZLogger().LogInfo("[RZNM - LOOTSYSTEM]: Creature equal to 0!");
            return;
        }
    else
    {
      for(int i = 0; i < DeadWolfObjs.Count(); i++){
        if(DeadWolfObjs.Get(i)!=NULL){
          GetGame().ObjectDelete(DeadWolfObjs.Get(i));
          GetRZLogger().LogInfo("[RZNM - LOOTSYSTEM]: Creature has been deleted!");
        }
      }
      DeadWolfObjs.Clear();
      return;
    }

  }

  void CheckRadCaseListStatus()
  {
    GetRZLogger().LogInfo("[RZNM - LOOTSYSTEM]: [RadCaseCleaner] !");
    if(m_LootList.Count() == 0){
      GetRZLogger().LogInfo("[RZNM - LOOTSYSTEM]: RadCaseList equal to 0!");
            return;
        }
    else
    {
      for(int i = 0; i < m_LootList.Count(); i++){
        if(m_LootList.Get(i)!=NULL){
          GetGame().ObjectDelete(m_LootList.Get(i));
          GetRZLogger().LogInfo("[RZNM - LOOTSYSTEM]: RadCaseList has been deleted!");
        }
      }
      m_LootList.Clear();
      return;
    }
  }

  void CheckParticlesStatus()
  {
    GetRZLogger().LogInfo("[RZNM - PARTICLES CLEANER]: [ParticlesCleaner] !");
    if(m_NukeWastes.Count() == 0)
    {
      GetRZLogger().LogInfo("[RZNM - PARTICLES CLEANER]: Particles equal to 0!");
      return;
    }
    else
    {
        int cpt = m_NukeWastes.Count() - 1;
        for(int i = 0; i <= cpt; i++)
        {
          if(m_NukeWastes.Get(i)!=NULL)
          {
            GetGame().ObjectDelete(m_NukeWastes.Get(i));
          }
        }
        m_NukeWastes.Clear();
        return;
    }
  }

   vector snapToGround(vector pos)
    {
        if(pos[1]>0)return pos;
        float pos_x = pos[0];
        float pos_z = pos[2];
        float pos_y = GetGame().SurfaceY( pos_x, pos_z );
        vector tmp_pos = Vector( pos_x, pos_y, pos_z );
        tmp_pos[1] = tmp_pos[1] + pos[1];

        return tmp_pos;
    }

    void GetPlayerPosFromNukeToServer(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target)
    {
     if (!GetGame().IsServer())
       return;

      Param1<int> data;
      if (!ctx.Read(data))return;

     PlayerBase player = RZGetPlayerByIdentity(sender);
     if(!player)return;
     player.ExplosionBlastEffect(data.param1);
    }

  PlayerBase RZGetPlayerByIdentity(PlayerIdentity sender)
  {
    int	low	 =	0;
    int	high =	0;
    GetGame().GetPlayerNetworkIDByIdentityID( sender.GetPlayerId(), low, high );
    return PlayerBase.Cast( GetGame().GetObjectByNetworkId(low, high ));
  }

  void SendNotifIfInRZ()
  {
    if(!GetRZNMConfig().IsWarningMsgActive)return;
    array<Man> m_Players = new array<Man>;
    GetGame().GetPlayers(m_Players);
    int cpt = m_Players.Count() - 1;
    for(int i = 0; i <=cpt ; i++)
    {
        PlayerBase player;
        Class.CastTo(player, m_Players.Get(i));
        FutureTZone(RZRadZonePicked.X,RZRadZonePicked.Y,RZRadZonePicked.Radius,player);
    }
  }

  void SendGlobalNotif()
  {
    if(!GetRZNMConfig().IsGlobalWarningMsgActive)return;
    array<Man> m_Players = new array<Man>;
    GetGame().GetPlayers(m_Players);
    int cpt = m_Players.Count() - 1;
    for(int i = 0; i <=cpt ; i++)
    {
        PlayerBase player;
        Class.CastTo(player, m_Players.Get(i));
        string globalmsg = GetRZNMConfig().GlobalWarningMsg + " " + RZRadZonePicked.RadZoneStatut;
        NotificationSystem.SendNotificationToPlayerIdentityExtended(player.GetIdentity(), 5, "RadZone", globalmsg, "RadZone_Data/images/radiation.paa");
    }
  }

  void FutureTZone(float m_X, float m_Y, float Zone_Radius,PlayerBase player)
  {
      string ZoneCheck;
      vector pos = player.GetPosition();
      float distance_squared = Math.Pow(m_X-pos[0], 2) + Math.Pow(m_Y-pos[2], 2);
      if ( distance_squared <= Math.Pow(Zone_Radius, 2) )
      {
          NotificationSystem.SendNotificationToPlayerIdentityExtended(player.GetIdentity(), 5, "RadZone", GetRZNMConfig().WarningMsg, "RadZone_Data/images/radiation.paa");
      }
  }
};
