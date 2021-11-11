// Script File
class GeigerCounter extends ItemBase
{
	protected EffectSound 		m_EngineLoop;

	ItemBase					m_Battery; // Attached battery9v
	int						    m_Level;

	ref Timer 					m_SoundLoopStartTimer;


	void GeigerCounter()
	{
		m_Level = 0;
		GetCompEM().SwitchOff();
	}

	void ~GeigerCounter()
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
		if ( GetGame().IsClient()  || !GetGame().IsMultiplayer() )
		{
			PlayerBase m_player,player;
			Class.CastTo(m_player, GetGame().GetPlayer());
			Class.CastTo(player, GetHierarchyRootPlayer());
			if(m_player && player && m_player.GetIdentity() == player.GetIdentity())
			{
				GetRZRadZoneCore().m_RZRadZoneClient.DisplayRadOutText(true);
				m_Level = GetLevelValue(GetRZRadZoneCore().m_RZRadZoneClient.NbSickGivenForRadiation);
				StartSound();
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
		if ( GetGame().IsClient() || !GetGame().IsMultiplayer())
		{
			PlayerBase m_player;
			Class.CastTo(m_player, GetGame().GetPlayer());
			if(m_player)
			{
				if(GetRZRadZoneCore().m_RZRadZoneClient.RZStatut)
				{
					StartSound();
					int nbrad = GetRZRadZoneCore().m_RZRadZoneClient.NbSickGivenForRadiation;
					m_Level = GetLevelValue(nbrad);
					GetRZRadZoneCore().m_RZRadZoneClient.SetRadOutText(nbrad);
				}else StopSound();
			}
		}
	}

	override void OnWorkStop()
	{
		super.OnWorkStop();
		if ( GetGame().IsClient()  || !GetGame().IsMultiplayer() )
		{
			PlayerBase m_player,player;
			Class.CastTo(m_player, GetGame().GetPlayer());
			Class.CastTo(player, GetHierarchyRootPlayer());
			if(m_player && player && m_player.GetIdentity() == player.GetIdentity())
			{
				GetRZRadZoneCore().m_RZRadZoneClient.DisplayRadOutText(false);
			}
			StopSound();
		}
	}

	void StartSound()
	{
		if (!m_SoundLoopStartTimer) m_SoundLoopStartTimer = new Timer( CALL_CATEGORY_SYSTEM );
		m_SoundLoopStartTimer.Run(0.2, this, "StartLoopSound", NULL, true);
	}

	void StopSound()
	{
		if ( GetGame().IsClient()  ||  !GetGame().IsMultiplayer() )
		{
			if (m_SoundLoopStartTimer)
			{
				m_SoundLoopStartTimer.Stop();
			}

			if (m_EngineLoop){
				if (m_EngineLoop.IsSoundPlaying()) m_EngineLoop.SoundStop();
			}
		}
	}

	void StartLoopSound()
	{
		if ( (GetGame().IsClient()  ||  !GetGame().IsMultiplayer()))
		{
					//Print("StartSoundLoop");
					if(m_Level == 0)
					{
						if (m_EngineLoop)
						{
							if (m_EngineLoop.IsSoundPlaying())	m_EngineLoop.SoundStop();
						}
						return;
					}
					else
					{
						if (m_EngineLoop)
						{
							//Print("VERYLOW");
							if ( !m_EngineLoop.IsSoundPlaying()) PlaySoundSet( m_EngineLoop, "rz_Geiger_"+m_Level.ToString()+"_SoundSet", 0, 0);
						}
						else {
								PlaySoundSet( m_EngineLoop, "rz_Geiger_"+m_Level.ToString()+"_SoundSet", 0, 0);
						}
					}
			}
	}

	int GetLevelValue(int nbradgiven)
	{
			//Print("nbrad:"+nbradgiven.ToString());
			if(GetRadQtyClient() == 0)return 0;
			if(nbradgiven == 0)return 0;
			return (GetRadQtyClient()/nbradgiven);
	}

	override void SetActions()
	{
		super.SetActions();
		AddAction(ActionTurnOnWhileInHands);
		AddAction(ActionTurnOffWhileInHands);
	}
};
