class ActionTestForRadiationTargetCB : ActionContinuousBaseCB
{
	override void CreateActionComponent()
	{
		m_ActionData.m_ActionComponent = new CAContinuousTime(UATimeSpent.SALINE);
	}
};

class ActionTestForRadiationTarget: ActionContinuousBase
{
	void ActionTestForRadiationTarget()
	{
		m_CallbackClass = ActionTestForRadiationTargetCB;
		m_SpecialtyWeight = UASoftSkillsWeight.PRECISE_MEDIUM;

		m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_CRAFTING;
		m_FullBody = true;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_CROUCH;
	}

	override void CreateConditionComponents()
	{
		m_ConditionItem = new CCINonRuined;
		m_ConditionTarget = new CCTMan(UAMaxDistances.DEFAULT);
	}

	override string GetText()
	{
		return "Get Radiation Level Target";
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
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
		PlayerBase ntarget = PlayerBase.Cast( action_data.m_Target.GetObject() );
		ntarget.InnerRadQty = ntarget.GetSingleAgentCount(RZAgents.RADSICK);
		ntarget.SetInnerRadQty(ntarget.InnerRadQty);
		string message = "Total Radiation Exposure : " + ntarget.InnerRadQty.ToString();
		NotificationSystem.SendNotificationToPlayerIdentityExtended(ntarget.GetIdentity(), 3, "Radiation Zone", message, "RadZone_Data/images/radiation.paa");
		NotificationSystem.SendNotificationToPlayerIdentityExtended(action_data.m_Player.GetIdentity(), 3, "Radiation Zone", message, "RadZone_Data/images/radiation.paa");

		#ifdef RZDEBUG
		GetRZLogger().LogInfo("playerTarget:"+ntarget.GetIdentity().GetName()+"action_dosimeter:"+message);
		#endif
	}
};
