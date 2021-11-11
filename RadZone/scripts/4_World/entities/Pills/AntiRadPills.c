class AntiRadPills : Edible_Base
{
	override void OnConsume(float amount, PlayerBase consumer)
	{
		if( consumer.GetModifiersManager().IsModifierActive(RZModifiers.MDF_RZANTIRADPILLS))//effectively resets the timer
		{
			consumer.GetModifiersManager().DeactivateModifier( RZModifiers.MDF_RZANTIRADPILLS );
		}
		consumer.GetModifiersManager().ActivateModifier( RZModifiers.MDF_RZANTIRADPILLS );
	}

	override void SetActions()
	{
		super.SetActions();
		AddAction(ActionForceConsumeSingle);
		AddAction(ActionConsumeSingle);
	}
};
