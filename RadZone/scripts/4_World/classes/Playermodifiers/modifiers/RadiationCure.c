class RadiationCureMdfr: ModifierBase
{
	float 			m_LastWaterLevel;
	ref HumanMovementState		m_MovementState	= new HumanMovementState();
	float m_RegenTime;
	float m_TickMin;

	override void Init()
	{
		m_TrackActivatedTime = true;
		m_IsPersistent = true;
		m_ID 					= RZModifiers.MDF_RZRADIATIONCURE;
		m_TickIntervalInactive 	= DEFAULT_TICK_TIME_INACTIVE;
		m_TickIntervalActive 	= DEFAULT_TICK_TIME_ACTIVE;
		m_RegenTime = 300;
		m_TickMin = 0;
	}

	override bool ActivateCondition(PlayerBase player)
	{
		return false;
	}

	override void OnReconnect(PlayerBase player)
	{
		OnActivate(player);
	}

	override string GetDebugText()
	{
		return (m_RegenTime - GetAttachedTime()).ToString();
	}

	override void OnActivate(PlayerBase player)
	{
		player.GetSymptomManager().RemoveSecondarySymptom(SymptomIDs.SYMPTOM_FEVERBLUR);
		#ifdef RZDEBUG
		GetRZLogger().LogInfo("player:"+player.GetIdentity().GetName()+"Cured"+"Rad_Pills_Treatment_Activated");
		#endif
		if( player.GetNotifiersManager() )
		player.GetNotifiersManager().ActivateByType(eNotifiers.NTF_PILLS);
	}

	override void OnDeactivate(PlayerBase player)
	{
		if( player.GetNotifiersManager() )
		  player.GetSymptomManager().RemoveSecondarySymptom(SymptomIDs.SYMPTOM_FEVERBLUR);
			player.GetNotifiersManager().DeactivateByType(eNotifiers.NTF_PILLS);
	}

	override bool DeactivateCondition(PlayerBase player)
	{
		float attached_time = GetAttachedTime();

		if( attached_time >= m_RegenTime )
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	override void OnTick(PlayerBase player, float deltaT)
	{
			m_TickMin += deltaT;
			if(m_TickMin < 60.0)return;
			m_TickMin = 0;

		  player.InnerRadQty = player.GetSingleAgentCount(RZAgents.RADSICK);
			player.InnerRadQty -= player.QtyRadReducedPerMin;
			player.SetInnerRadQty(player.InnerRadQty);
			if(player.InnerRadQty<0 || player.InnerRadQty==0)
			{
				player.SetInnerRadQty(0);
				player.m_ModifiersManager.DeactivateModifier(RZModifiers.MDF_RZRADSICK);
			}
			player.m_AgentPool.SetAgentCount(RZAgents.RADSICK,player.InnerRadQty);
	}
};
