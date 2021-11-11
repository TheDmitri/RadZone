class ActionDestroyNukeWasteCB : ActionContinuousBaseCB
{
	override void CreateActionComponent()
	{
		m_ActionData.m_ActionComponent = new CAContinuousTime(45);
	}
};

class ActionDestroyNukeWaste: ActionContinuousBase
{
	void ActionDestroyNukeWaste()
	{
		m_CallbackClass = ActionDestroyNukeWasteCB;
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
		if ( targetObject.IsKindOf("IrradiedDirtPile") )
		{
			return true;
		}
		return false;
	}

	override string GetText()
	{
		return "Destroy Nuke waste";
	}

	override void OnFinishProgressServer( ActionData action_data )
	{
		action_data.m_Player.GetSoftSkillsManager().AddSpecialty( m_SpecialtyWeight );

    IrradiedDirtPile m_NukeWaste = IrradiedDirtPile.Cast(action_data.m_Target.GetObject());
    GetRZNMServer().CheckNukeWaste(m_NukeWaste.GetPosition());
	}
};
