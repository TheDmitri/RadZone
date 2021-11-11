class RZRadZoneServer
{
  ref RadiationLocations m_RadiationLocations;

  void RZRadZoneServer()
  {
      GetRZLogger().LogInfo("RZRadZoneServer - Started");
      GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(InitRZRadZoneServer, 1000);
  }

  void InitRZRadZoneServer()
  {
    //We convert our radzone config so we can send it to client
    m_RadiationLocations = new RadiationLocations;
    m_RadiationLocations.InitRadiationLocations(GetRadConfig());
  }

  void  ~RZRadZoneServer()
  {

  }

  void SendRZConfigToClient(PlayerIdentity sender)
  {
      if(m_RadiationLocations)
      {
          GetRPCManager().SendRPC("RZRadZone", "GetRadConfigResponse", new Param1<ref RadiationLocations>(m_RadiationLocations), true, sender);
      }
  }

  //-----------------------------------RPC called on server-------------------------------------//
  void GetRadStatut(CallType type,  ParamsReadContext ctx,  PlayerIdentity sender,  Object target)
  {
   if (!GetGame().IsServer())
     return;

    Param2<string, bool> data;
     if (!ctx.Read(data))
       return;
     PlayerBase player = RZGetPlayerByIdentity(sender);
     player.RZIsInside.RZName = data.param1;
     player.RZIsInside.RZStatut = data.param2;

     #ifdef RZDEBUG
     GetRZLogger().LogInfo("[RadStatut] : PlayerName:"+ sender.GetName() + " Name:"+data.param1 + " Statut:"+data.param2);
     #endif
  }

  void GetSickQtyToGive(CallType type,  ParamsReadContext ctx,  PlayerIdentity sender,  Object target)
  {
   if (!GetGame().IsServer())
     return;

    Param1<float> data;
     if (!ctx.Read(data))
       return;
     PlayerBase player = RZGetPlayerByIdentity(sender);
     player.GiveRadSickness(data.param1);

     #ifdef RZDEBUG
     GetRZLogger().LogInfo("GetSickQtyToGive");
     #endif
  }

  void GetRadQtyToClothesRequest(CallType type,  ParamsReadContext ctx,  PlayerIdentity sender,  Object target)
  {
   if (!GetGame().IsServer())
     return;

     Param1<int> data;
      if (!ctx.Read(data))
        return;
     PlayerBase player = RZGetPlayerByIdentity(sender);
     player.GiveRadQtyToPlayerClothes(data.param1);

     #ifdef RZDEBUG
     GetRZLogger().LogInfo("GetRadQtyToClothesRequest");
     #endif
  }

  void GetDamageClotheRequest(CallType type,  ParamsReadContext ctx,  PlayerIdentity sender,  Object target)
  {
   if (!GetGame().IsServer())
     return;
     PlayerBase player = RZGetPlayerByIdentity(sender);
     player.SetRadDamageOnClothes();

     #ifdef RZDEBUG
     GetRZLogger().LogInfo("GetDamageClotheRequest");
     #endif
  }
  //---------------------------------------------------------------------------------------------------------//
};
