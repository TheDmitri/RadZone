modded class IngameHud
{
  ref RadiationUI m_RadiationUI = NULL;

	override void Init(Widget hud_panel_widget)
	{
		super.Init(hud_panel_widget);

		m_RadiationUI = new ref RadiationUI(hud_panel_widget);
	}

  void SetRadLogoHasToBeVisible(bool rep)
  {
    m_RadiationUI.SetHasToBeVisible(rep);
  }

  void DisplayRadUI(bool rep)
  {
    m_RadiationUI.DisplayUI(rep);
  }

  void DisplayRadInText(bool rep)
  {
    m_RadiationUI.DisplayRadInText(rep);
  }

  override void RefreshHudVisibility()
	{
    super.RefreshHudVisibility();
    if(m_RadiationUI.GetHasToBeVisible())
    {
      m_RadiationUI.DisplayUI((!m_HudHidePlayer && !m_HudHideUI && m_HudState ) || m_HudInventory);
    }
	}

  void DisplayRadOutText(bool rep)
  {
    m_RadiationUI.DisplayRadOutText(rep);
  }

  void SetRadInText(int rad_value)
  {
    m_RadiationUI.SetRadInText(rad_value);
  }

  void SetRadOutText(int rad_value)
  {
    m_RadiationUI.SetRadOutText(rad_value);
  }
};
