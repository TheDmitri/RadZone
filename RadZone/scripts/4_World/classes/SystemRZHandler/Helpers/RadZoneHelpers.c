static ref RZRadZoneCore m_RZRadZoneCore;
static RZRadZoneCore GetRZRadZoneCore() {
	if ( !m_RZRadZoneCore ) {
		m_RZRadZoneCore = new RZRadZoneCore;
	}
	return m_RZRadZoneCore;
}

static int GetRadQtyClient()	{
	return GetRZRadZoneCore().m_RZRadZoneClient.NbSickGivenForRadiation;
}

static ref RadiationAreaSettings GetRadConfig()	{
	return GetRZRadZoneCore().m_ActiveRadiationAreaSettings;
}

static ref RadiationLocations GetRadConfigClient()	{
	return GetRZRadZoneCore().m_RZRadZoneClient.m_RadiationLocations;
}

static ref RZCrateSystemAreaSettings GetCrateSystemConfig(){
	return GetRZRadZoneCore().m_ActiveRZCrateSystemSettings;
}

static ref ClotheProtectionSettings GetClothesConfig()	{
return GetRZRadZoneCore().m_ClotheProtectionSettingsClient;
}

static ref ClotheProtectionSettings GetClothesConfigClient()	{
	return GetRZRadZoneCore().m_ClotheProtectionSettingsClient;
}

#ifdef RZNM
static ref RadNukeMissionsAreaSettings GetRZNMConfig()	{
	return GetRZRadZoneCore().m_ActiveRadNukeMissionsAreaSettings;
}

static ref RZRadNukeMissionsZoneServer GetRZNMServer()	{
	return GetRZRadZoneCore().m_RZRadNukeMissionsZoneServer;
}

static ref RadZoneNukeMissionsLocation GetRZNMConfigClient()	{
	return GetRZRadZoneCore().m_RZRadZoneClient.m_RadZoneNukeMissionsLocation;
}
#endif

static PlayerBase RZGetPlayerByIdentity(PlayerIdentity sender)
{
	int	low	 =	0;
	int	high =	0;
	GetGame().GetPlayerNetworkIDByIdentityID( sender.GetPlayerId(), low, high );
	return PlayerBase.Cast( GetGame().GetObjectByNetworkId(low, high ));
}

static int RZGetTimeStamp()
{
	int year, month, day, hour, minute, second;
	GetHourMinuteSecondUTC(hour, minute, second);
	GetYearMonthDayUTC(year, month, day);
	return JMDate.Timestamp(year,month,day,hour,minute,second);
}

class RadZoneHelper
{
	static Weapon_Base CreateWeaponWithMagazine( string sWeapon, string sMagazine, vector pos)
    {
        Weapon_Base oWpn = Weapon_Base.Cast(GetGame().CreateObject( sWeapon , "0 0 0" ));

        if ( !oWpn )
            return NULL;

        int stateId = -1;

        if ( oWpn.IsInherited( SKS_Base ) )
            return oWpn;
        else if ( oWpn.IsInherited( BoltActionRifle_InnerMagazine_Base ) )
            return oWpn;
        else if ( oWpn.IsInherited( DoubleBarrel_Base ) )
            return oWpn;
        else if ( oWpn.IsInherited( Pistol_Base ) )
            stateId = PistolStableStateID.CLO_DIS_BU0_MA1;
        else if ( oWpn.IsInherited( CZ527_Base ) )
            stateId = CZ527StableStateID.CZ527_CLO_BU0_MA1;
        else if ( oWpn.IsInherited( Repeater_Base ) )
            return oWpn;
        else if ( oWpn.IsInherited( RifleBoltFree_Base ) )
            stateId = RBFStableStateID.RBF_CLO_BU0_MA1;
        else if ( oWpn.IsInherited( RifleBoltLock_Base ) )
            stateId = RBLStableStateID.RBL_CLO_BU0_MA1; //stateId = RBLStableStateID.RBL_OPN_BU0_MA1;
        else if ( oWpn.IsInherited( Mp133Shotgun_Base ) )
            return oWpn;

        InventoryLocation mag_il = new InventoryLocation;
        mag_il.SetAttachment( oWpn, NULL, InventorySlots.MAGAZINE );
        Magazine oMag = Magazine.Cast( SpawnEntity( sMagazine, mag_il, ECE_IN_INVENTORY, RF_DEFAULT ) );
        if ( !oMag )
            return oWpn;

        GetGame().RemoteObjectDelete( oWpn );
        GetGame().RemoteObjectDelete( oMag );


        pushToChamberFromAttachedMagazine( oWpn, oWpn.GetCurrentMuzzle() );

        ScriptReadWriteContext ctx = new ScriptReadWriteContext;
        ctx.GetWriteContext().Write( stateId );
        oWpn.LoadCurrentFSMState( ctx.GetReadContext(), GetGame().SaveVersion() );


        GetGame().RemoteObjectCreate( oWpn );
        GetGame().RemoteObjectCreate( oMag );

        return oWpn;
    }
}
