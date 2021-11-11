class RadiationCure: Inventory_Base
{
	override void SetActions()
	{
		super.SetActions();

		AddAction(ActionInjectRadiationCureTarget);
		AddAction(ActionInjectRadiationCureSelf);
	}

	override void OnApply(PlayerBase player)
	{
		if( player.GetModifiersManager().IsModifierActive(RZModifiers.MDF_RZRADIATIONCURE ) )//effectively resets the timer
		{
			player.GetModifiersManager().DeactivateModifier( RZModifiers.MDF_RZRADIATIONCURE );
		}
		player.GetModifiersManager().ActivateModifier( RZModifiers.MDF_RZRADIATIONCURE );
	}
};
