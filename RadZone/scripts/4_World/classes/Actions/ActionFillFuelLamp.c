class ActionFillFuelLampCB : ActionContinuousBaseCB
{
	override void CreateActionComponent()
	{
		m_ActionData.m_ActionComponent = new CAContinuousDisinfectPlant(5);
	}
};

class ActionFillFuelLamp: ActionContinuousBase
{
	void ActionFillFuelLamp()
	{
		m_CallbackClass = ActionFillFuelLampCB;
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_EMPTY_VESSEL;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
		m_FullBody = true;
		m_SpecialtyWeight = UASoftSkillsWeight.PRECISE_LOW;
	}

	override void CreateConditionComponents()
	{
		m_ConditionTarget = new CCTNonRuined(UAMaxDistances.DEFAULT);
		m_ConditionItem = new CCINonRuined;
	}

	override string GetText()
	{
		return "Fill Fuel Lamp";
	}

	override bool ActionCondition ( PlayerBase player, ActionTarget target, ItemBase item )
	{
		ItemBase m_lamp = ItemBase.Cast(target.GetObject());
		if ( item.GetLiquidType() == LIQUID_GASOLINE && item.GetQuantity() > 1000 && !m_lamp.GetCompEM().IsWorking())
		{
			return true;
		}
		return false;
	}

	override void OnEndServer( ActionData action_data )
	{
		ItemBase m_lamp = ItemBase.Cast(action_data.m_Target.GetObject());
		if(m_lamp)
		{
			m_lamp.GetCompEM().AddEnergy(1000);
			m_lamp.GetCompEM().SetQuantity(1000);
		}
	}
};
