class ShowerKit extends ItemBase
{
    void ShowerKit()
    {

    }

    override void OnPlacementComplete( Man player, vector position = "0 0 0", vector orientation = "0 0 0" )
    {
        super.OnPlacementComplete( player );
        PlayerBase pb = PlayerBase.Cast( player );
        if ( GetGame().IsServer() )
        {
            PlayerBase player_base = PlayerBase.Cast( player );
            vector pposition = player_base.GetLocalProjectionPosition();
            vector oorientation = player_base.GetLocalProjectionOrientation();

            DecontaminationShower Shower = DecontaminationShower.Cast(GetGame().CreateObject("DecontaminationShower", pb.GetLocalProjectionPosition(), false ));
            Shower.SetPosition( pposition);
            Shower.SetOrientation( oorientation );

            this.Delete();
        }
        SetIsDeploySound( true );
    }

  override void SetActions()
	{
		super.SetActions();
		AddAction(ActionTogglePlaceObject);
		AddAction(ActionDeployObject);
	}
};
