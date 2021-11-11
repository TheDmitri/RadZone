modded class PlayerBase extends ManBase
{
	void ExplosionBlastEffect(int i)
	{
		switch (i)
			{
				case 0: SetHealth(0);
				break;

				case 1:
				{
					SetHealth(10);
					GiveShock(-100);
					AddToEnvironmentTemperature(1000.0);
				}
				break;

				case 3:AddToEnvironmentTemperature(2000.0);
				break;

				default:
				break;
		 }
	}
};
