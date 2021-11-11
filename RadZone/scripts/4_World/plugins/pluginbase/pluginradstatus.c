class PluginRadStatus : PluginBase
{

	void DisplayRadInText(bool rep)
  {
		Mission mission = GetGame().GetMission();
		if (mission)
		{
			Hud hud = mission.GetHud();
			if (hud)
			{
    		hud.DisplayRadInText(rep);
			}
		}
  }

	void SetRadLogoHasToBeVisible(bool rep)
  {
		Mission mission = GetGame().GetMission();
		if (mission)
		{
			Hud hud = mission.GetHud();
			if (hud)
			{
				hud.SetRadLogoHasToBeVisible(rep);
			}
  	}
	}

	void DisplayRadUI(bool rep)
  {
		Mission mission = GetGame().GetMission();
		if (mission)
		{
			Hud hud = mission.GetHud();
			if (hud)
			{
    		hud.DisplayRadUI(rep);
			}
		}
  }

  void DisplayRadOutText(bool rep)
  {
		Mission mission = GetGame().GetMission();
		if (mission)
		{
			Hud hud = mission.GetHud();
			if (hud)
			{
    		hud.DisplayRadOutText(rep);
			}
		}
  }

  void SetRadInText(int rad_value)
  {
		Mission mission = GetGame().GetMission();
		if (mission)
		{
			Hud hud = mission.GetHud();
			if (hud)
			{
    		hud.SetRadInText(rad_value);
			}
		}
  }

  void SetRadOutText(int rad_value)
  {
		Mission mission = GetGame().GetMission();
		if (mission)
		{
			Hud hud = mission.GetHud();
			if (hud)
			{
    		hud.SetRadOutText(rad_value);
			}
		}
  }
};
