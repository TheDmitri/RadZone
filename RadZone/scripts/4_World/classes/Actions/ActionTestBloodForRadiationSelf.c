class ActionTestForRadiationSelfCB : ActionContinuousBaseCB
{
	override void CreateActionComponent()
	{
		m_ActionData.m_ActionComponent = new CAContinuousTime(UATimeSpent.TEST_BLOOD);
	}
};

class ActionTestForRadiationSelf: ActionContinuousBase
{
	void ActionTestForRadiationSelf()
	{
		m_CallbackClass = ActionTestForRadiationSelfCB;
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_CRAFTING;
		m_FullBody = true;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_CROUCH;
		m_SpecialtyWeight = UASoftSkillsWeight.PRECISE_LOW;
	}

	override void CreateConditionComponents()
	{
		m_ConditionItem = new CCINonRuined;
		m_ConditionTarget = new CCTSelf;
	}

	override bool HasTarget()
	{
		return false;
	}

	override string GetText()
	{
		return "Get Radiation Level";
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
			if ( item && item.GetCompEM().IsWorking() )
			{
				return true;
			}
			return false;
	}

	override void OnFinishProgressServer( ActionData action_data )
	{
		action_data.m_Player.InnerRadQty = action_data.m_Player.GetSingleAgentCount(RZAgents.RADSICK);
		action_data.m_Player.SetInnerRadQty(action_data.m_Player.InnerRadQty);
		string message = "Total Radiation Exposure : " + action_data.m_Player.InnerRadQty.ToString();
		NotificationSystem.SendNotificationToPlayerIdentityExtended(action_data.m_Player.GetIdentity(), 3, "Radiation Zone", message, "RadZone_Data/images/radiation.paa");

		#ifdef RZDEBUG
		GetRZLogger().LogInfo("player:"+action_data.m_Player.GetIdentity().GetName()+"action_dosimeter:"+message);
		#endif
		//action_data.m_MainItem.SetQuantity(action_data.m_MainItem.GetQuantity() - 20);
	}
};
