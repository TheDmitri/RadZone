class ActionDestroyNukeCraterCB : ActionContinuousBaseCB
{
	override void CreateActionComponent()
	{
		m_ActionData.m_ActionComponent = new CAContinuousTime(120);
	}
};

class ActionDestroyNukeCrater: ActionContinuousBase
{
	void ActionDestroyNukeCrater()
	{
		m_CallbackClass = ActionDestroyNukeCraterCB;
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_MINEROCK;
		m_FullBody = true;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT;
		m_SpecialtyWeight = UASoftSkillsWeight.ROUGH_HIGH;
	}

	override void CreateConditionComponents()
	{
		m_ConditionTarget = new CCTCursor(UAMaxDistances.DEFAULT);
		m_ConditionItem = new CCINonRuined;
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		Object targetObject = target.GetObject();
		if ( targetObject.IsKindOf("NukeCrater") )
		{
			return true;
		}
		return false;
	}

	override string GetText()
	{
		return "Destroy Nuke Crater";
	}

	override void OnFinishProgressServer( ActionData action_data )
	{
		action_data.m_Player.GetSoftSkillsManager().AddSpecialty( m_SpecialtyWeight );
    IrradiedDirtPile m_NukeCrater = IrradiedDirtPile.Cast(action_data.m_Target.GetObject());
    GetRZNMServer().CheckNukeWaste(m_NukeCrater.GetPosition());
	}
};
