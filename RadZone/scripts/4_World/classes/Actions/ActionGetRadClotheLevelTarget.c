class ActionGetRadClotheLevelTargetCB : ActionContinuousBaseCB
{
	override void CreateActionComponent()
	{
		m_ActionData.m_ActionComponent = new CAContinuousTime(UATimeSpent.SALINE);
	}
};

class ActionGetRadClotheLevelTarget: ActionContinuousBase
{
	void ActionGetRadClotheLevelTarget()
	{
		m_CallbackClass = ActionGetRadClotheLevelTargetCB;
		m_SpecialtyWeight = UASoftSkillsWeight.PRECISE_LOW;

		m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_SPRAYPLANT;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_CROUCH;
		m_FullBody = true;
	}

	override void CreateConditionComponents()
	{
		m_ConditionItem = new CCINonRuined;
		m_ConditionTarget = new CCTMan(UAMaxDistances.DEFAULT);
	}

	override string GetText()
	{
		return "Check player's clothes";
	}

	override bool ActionCondition ( PlayerBase player, ActionTarget target, ItemBase item )
	{
		PlayerBase m_player = PlayerBase.Cast(target.GetObject() );
		if ( m_player )
		{
				if ( item.GetCompEM().IsWorking() )
				{
					return true;
				}
		}
		return false;
	}

	override void OnFinishProgressServer( ActionData action_data )
	{
		PlayerBase m_player = PlayerBase.Cast(action_data.m_Target.GetObject());
		if ( m_player )
		{
			bool m_HasRadiationOnClothes = m_player.CheckForRadiationOnClothes();
			if(m_HasRadiationOnClothes)
			{
	  		NotificationSystem.SendNotificationToPlayerIdentityExtended(action_data.m_Player.GetIdentity(), 3, "Radiation Zone","Radiation has been detected on the player's clothes !", "RadZone_Data/images/radiation.paa");
			}
			else
			{
				NotificationSystem.SendNotificationToPlayerIdentityExtended(action_data.m_Player.GetIdentity(), 3, "Radiation Zone", "No Radiation has been detected on the player's clothes !", "RadZone_Data/images/radiation.paa");
			}
    }
	}

	override void OnEndServer( ActionData action_data )
	{
		/*PlayerBase m_player = PlayerBase.Cast(action_data.m_Target.GetObject());
		if ( m_player )
		{
			bool m_HasRadiationOnClothes = m_player.CheckForRadiationOnClothes();
			if(m_HasRadiationOnClothes)
			{
	  		NotificationSystem.SendNotificationToPlayerIdentityExtended(action_data.m_Player.GetIdentity(), 3, "Radiation Zone","Radiation has been detected on the player's clothes !", "RadZone/images/radiation.paa");
			}
			else
			{
				NotificationSystem.SendNotificationToPlayerIdentityExtended(action_data.m_Player.GetIdentity(), 3, "Radiation Zone", "No Radiation has been detected on the player's clothes !", "RadZone/images/radiation.paa");
			}
		}*/
	}
};
