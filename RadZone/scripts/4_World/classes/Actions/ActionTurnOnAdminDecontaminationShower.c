class ActionTurnOnAdminDecontaminationShower: ActionInteractBase
{
	void ActionTurnOnAdminDecontaminationShower()
	{
		m_CommandUID        = DayZPlayerConstants.CMD_ACTIONMOD_OPENDOORFW;
		m_StanceMask        = DayZPlayerConstants.STANCEMASK_CROUCH | DayZPlayerConstants.STANCEMASK_ERECT;
	}

	override string GetText()
	{
		return "Turn on shower";
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		Object targetObject = target.GetObject();
		if ( targetObject )
		{
			DecontaminationShowerUnlimitedStatic shower = DecontaminationShower.Cast( targetObject );
			if (!shower.GetCompEM().IsWorking())
			{
					return true;
			}
			return false;
		}
		return false;
	}

	override void OnExecuteServer( ActionData action_data )
	{
		Object targetObject = action_data.m_Target.GetObject();
		if (targetObject)
		{
			EntityAI target_EAI = EntityAI.Cast( targetObject );
			if(target_EAI.IsKindOf("DecontaminationShowerUnlimitedStatic"))
			{
				DecontaminationShowerUnlimitedStatic sh = DecontaminationShower.Cast(target_EAI);
				sh.WaterQty = 20000;
				sh.CanStartShower();
			}
		}
	}
};
