// Script File
class Geigercounter_Opal extends ItemBase
{
		protected EffectSound 		m_EngineLoop;

	ItemBase					m_Battery; // Attached battery9v

	ref Timer 					m_SoundLoopStartTimer;


	void Geigercounter_Opal()
	{
		  GetCompEM().SwitchOff();
	}

	void ~Geigercounter_Opal()
	{
	}

	override void EEItemAttached ( EntityAI item, string slot_name )
	{
		super.EEItemAttached ( item, slot_name );

		ItemBase item_IB = ItemBase.Cast( item );

		if ( item_IB.IsKindOf("Battery9V") )
		{
			m_Battery = item_IB;
		}
	}


	override void EEItemDetached ( EntityAI item, string slot_name )
	{
		super.EEItemDetached ( item, slot_name );

		ItemBase item_IB = ItemBase.Cast( item );

		if ( item_IB.IsKindOf("Battery9V") )
		{
			m_Battery = NULL;
		}
	}

	override void OnWorkStart()
	{
		if ( GetGame().IsClient() || !GetGame().IsMultiplayer() )
		{
			PlayerBase m_player,player;
			Class.CastTo(player, GetHierarchyRootPlayer());
			Class.CastTo(m_player, GetGame().GetPlayer());
		  if(m_player && player && m_player.GetIdentity() == player.GetIdentity())
			{
				GetRZRadZoneCore().m_RZRadZoneClient.DisplayRadInText(true);
			}
		}
	}

	override void OnWork( float consumed_energy )
	{
		if(GetGame().IsServer())
		{
			PlayerBase player;
			Class.CastTo(player, GetHierarchyRootPlayer());

			if(!player || !player.IsAlive())
			{
				GetCompEM().SwitchOff();
			}
		}
		if ( GetGame().IsClient()  || !GetGame().IsMultiplayer() )
		{
			PlayerBase m_player, n_player;
			Class.CastTo(n_player, GetHierarchyRootPlayer());
			Class.CastTo(m_player, GetGame().GetPlayer());
			if(m_player && n_player && m_player.GetIdentity() == n_player.GetIdentity())
			{
					if(GetRZRadZoneCore().m_RZRadZoneClient.RZStatut)
					{
					  GetRZRadZoneCore().m_RZRadZoneClient.SetRadInText(GetRZRadZoneCore().m_RZRadZoneClient.InnerRad);
					  int nbrad = GetRZRadZoneCore().m_RZRadZoneClient.NbSickGivenForRadiation;
					}
			}
		}
	}

	override void OnWorkStop()
	{
		super.OnWorkStop();
		if ( GetGame().IsClient() || !GetGame().IsMultiplayer() )
		{
			PlayerBase m_player,player;
			Class.CastTo(m_player, GetGame().GetPlayer());
			Class.CastTo(player, GetHierarchyRootPlayer());
			if(m_player && m_player.GetIdentity() == player.GetIdentity())
			{
					GetRZRadZoneCore().m_RZRadZoneClient.DisplayRadInText(false);
			}
		}
	}

	override void SetActions()
	{
		super.SetActions();
		AddAction(ActionTurnOnWhileInHands);
		AddAction(ActionTurnOffWhileInHands);
		AddAction(ActionTestForRadiationTarget);
		AddAction(ActionTestForRadiationSelf);
	}
};
