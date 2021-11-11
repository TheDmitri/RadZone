modded class MissionServer extends MissionBase
{
	void MissionServer()
	{
		m_RZRadZoneCore = NULL;
		GetRZRadZoneCore();
	}

	void ~MissionServer() {
	}

	override void InvokeOnConnect(PlayerBase player, PlayerIdentity identity)
	{
		super.InvokeOnConnect(player,identity);
		InitializeConfigToPlayer(player,identity);
	}

	void InitializeConfigToPlayer(PlayerBase player, PlayerIdentity identity)
	{
		#ifdef RZDEBUG
		GetRZLogger().LogInfo("Start - InitializeConfigToPlayer");
		#endif
		player.RadChanceVomit = GetRadConfig().RadChanceVomit;
		player.RadChanceBleeding = GetRadConfig().RadChanceBleeding;
		player.RadBloodLossDamage = GetRadConfig().RadBloodLossDamage;
		player.RadHealthDamage = GetRadConfig().RadHealthDamage;
		player.RadHighMultiplier = GetRadConfig().RadHighMultiplier;
		player.RadHighMultiplier = GetRadConfig().RadHighMultiplier;
		player.CriticalProtection = GetRadConfig().CriticalProtection;
		player.ClothesQuantityMultiplier = GetRadConfig().ClothesQuantityMultiplier;
		player.AmountGivenAfterCriticalProtection = GetRadConfig().AmountGivenAfterCriticalProtection;
		player.QtyRadReducedPerMin = GetRadConfig().QtyRadReducedPerMin;

		if(!GetRadConfig().IsRadiationZoneActive)return;
		GetRZRadZoneCore().m_RZRadZoneServer.SendRZConfigToClient(identity);
		GetRZRadZoneCore().TransfertClotheProtectionConfigToClient(identity);

		#ifdef RZDEBUG
		GetRZLogger().LogInfo("End - InitializeConfigToPlayer");
		#endif
	}


	override PlayerBase CreateCharacter(PlayerIdentity identity, vector pos, ParamsReadContext ctx, string characterName)
	{
		Entity playerEnt;
		playerEnt = GetGame().CreatePlayer(identity, characterName, pos, 0, "NONE");//Creates random player
		Class.CastTo(m_player, playerEnt);

		GetGame().SelectPlayer(identity, m_player);

		m_player.RZIsInside.RZStatut=false;
		m_player.RZIsInside.RZName="";

		return m_player;

		//super.CreateCharacter(identity,pos,ctx,characterName);
	}

};
