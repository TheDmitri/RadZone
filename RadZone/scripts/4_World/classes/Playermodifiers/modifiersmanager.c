modded class ModifiersManager
{
	override void Init()
	{
		super.Init();
		AddModifier(new RadSickMdfr);
		AddModifier(new AntiRadPillsMdfr);
		AddModifier(new RadiationCureMdfr);
	}
}
