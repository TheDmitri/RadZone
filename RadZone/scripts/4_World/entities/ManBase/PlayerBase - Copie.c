modded class PlayerBase extends ManBase
{
	override void SetActions()
	{
		super.SetActions();
		AddAction(ActionFillFuelLamp);
	}
};
