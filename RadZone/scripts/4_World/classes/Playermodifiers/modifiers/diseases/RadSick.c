class RadSickMdfr: ModifierBase
{
	static const int RADSICK_AGENT_THRESHOLD_ACTIVATE = 100;
	static const int RADSICK_AGENT_THRESHOLD_DEACTIVATE = 100;
	private ref array<string>m_BleedingSources = {"Head","Spine","LeftShoulder","LeftArm","RightShoulder","LeftLeg","RightLeg","LeftFoot","RightFoot"};
	float chanceVomit;
	float chanceBleeding;
	string m_RZState;
	float m_tick;
	bool m_HasFever;

	override void Init()
	{
		m_TrackActivatedTime 		= false;
		m_ID 										= RZModifiers.MDF_RZRADSICK;
		m_TickIntervalInactive 	= DEFAULT_TICK_TIME_INACTIVE;
		m_TickIntervalActive 	= DEFAULT_TICK_TIME_INACTIVE;
		m_tick=0;
		m_HasFever = false;
	}

	override protected bool ActivateCondition(PlayerBase player)
	{
		if(player.GetSingleAgentCount(RZAgents.RADSICK) > RADSICK_AGENT_THRESHOLD_ACTIVATE)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	override protected void OnActivate(PlayerBase player)
	{
	  //if( player.m_NotifiersManager ) player.m_NotifiersManager.AttachByType(eNotifiers.NTF_SICK);
		player.IncreaseDiseaseCount();
		chanceVomit=player.RadChanceVomit;
		chanceBleeding=player.RadChanceBleeding;

		#ifdef RZDEBUG
		GetRZLogger().LogInfo("player:"+player.GetIdentity().GetName()+"RadSickness Activated");
		#endif
	}

	override protected void OnDeactivate(PlayerBase player)
	{
		player.DecreaseDiseaseCount();

		#ifdef RZDEBUG
		GetRZLogger().LogInfo("player:"+player.GetIdentity().GetName()+"RadSickness Deactivated");
		#endif
	}

	override protected bool DeactivateCondition(PlayerBase player)
	{
		if(player.GetSingleAgentCount(RZAgents.RADSICK) < RADSICK_AGENT_THRESHOLD_DEACTIVATE)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	override protected void OnTick(PlayerBase player, float deltaT)
	{
		m_tick+=deltaT;
		if(m_tick<60.0)return;
		m_tick = 0;

		player.SetInnerRadQty(player.GetSingleAgentCount(RZAgents.RADSICK));
		if(player.InnerRadQty < 151 )
		{
			#ifdef RZDEBUG
			m_RZState = "State 1";
			#endif
			SetLowLevelEffetOnPlayer(1, player);
			return;
		}

		if(player.InnerRadQty > 151 && player.InnerRadQty < 200)
		{
			 	#ifdef RZDEBUG
				m_RZState = "State 2";
				#endif
				SetLowLevelEffetOnPlayer(player.RadHighMultiplier, player);
				if(chanceVomit > Math.RandomFloatInclusive(0,1))
				{
					player.GetSymptomManager().QueueUpPrimarySymptom(SymptomIDs.SYMPTOM_VOMIT);
				}
				return;
		}

		if(player.InnerRadQty > 200 && player.InnerRadQty < 300)
		{
			#ifdef RZDEBUG
			m_RZState = "State 3";
			#endif
			SetLowLevelEffetOnPlayer(player.RadHighMultiplier, player);
			if(chanceBleeding > Math.RandomFloatInclusive(0,1))
			{
				player.GetBleedingManagerServer().AttemptAddBleedingSourceBySelection(m_BleedingSources.GetRandomElement());
			}
			return;
		}

		if(player.InnerRadQty > 300 && player.InnerRadQty < 400)
		{
			#ifdef RZDEBUG
			m_RZState = "State 4";
			#endif
			SetLowLevelEffetOnPlayer(player.RadHighMultiplier*1.3, player);
			if(chanceBleeding > Math.RandomFloatInclusive(0,1))
			{
				player.GetBleedingManagerServer().AttemptAddBleedingSourceBySelection(m_BleedingSources.GetRandomElement());
			}
			return;
		}

		if(player.InnerRadQty > 400 && player.InnerRadQty < 500)
		{
			#ifdef RZDEBUG
			m_RZState = "State 5";
			#endif
			SetLowLevelEffetOnPlayer(player.RadHighMultiplier*1.6, player);
			if(!m_HasFever)
			{
				player.GetSymptomManager().QueueUpSecondarySymptom(SymptomIDs.SYMPTOM_FEVERBLUR);
				m_HasFever = true;
			}
			return;
		}

		if(player.GetSingleAgentCount(RZAgents.RADSICK) > 500)
		{
			#ifdef RZDEBUG
			m_RZState = "State 6";
			#endif
			SetLowLevelEffetOnPlayer(player.RadHighMultiplier*2, player);
			if(!m_HasFever)
			{
				player.GetSymptomManager().QueueUpSecondarySymptom(SymptomIDs.SYMPTOM_FEVERBLUR);
				m_HasFever = true;
			}
		}
		#ifdef RZDEBUG
		GetRZLogger().LogInfo("player:"+player.GetIdentity().GetName()+"Current Radiation level state"+m_RZState);
		#endif
	}

	void SetLowLevelEffetOnPlayer(float RadMultiplier, PlayerBase player)
	{
		float currenthealth = player.GetHealth("GlobalHealth", "Blood");
		player.SetHealth("GlobalHealth", "Blood" ,  currenthealth - player.RadBloodLossDamage*RadMultiplier);
		currenthealth = player.GetHealth();
		player.SetHealth(currenthealth - player.RadHealthDamage*RadMultiplier);
	}

};
