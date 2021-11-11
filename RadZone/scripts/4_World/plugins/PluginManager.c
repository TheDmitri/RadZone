modded class PluginManager
{
	override void Init()
	{
		super.Init();
		RegisterPlugin( "PluginRadStatus",	true, 	false );
	}
};
