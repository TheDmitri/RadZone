class RadiationUI extends UIScriptedMenu
{
  private Widget m_RadlayoutRoot;
  private TextWidget m_RadValueInText;
  private TextWidget m_RadValueOutText;
  private bool m_HasToBeVisible = false;

  void RadiationUI(Widget parent)
  {
	bool canshow = false;
  	#ifdef HEROESANDBANDITSMOD
  	m_RadlayoutRoot = GetGame().GetWorkspace().CreateWidgets("RadZone_Data/GUI/RadiationUIBis.layout",parent);
	canshow = true;
	#endif
	#ifdef PVEZ
	if(!canshow)
	{
		m_RadlayoutRoot = GetGame().GetWorkspace().CreateWidgets("RadZone_Data/GUI/RadiationUIBis.layout",parent);
		canshow = true;
	}
	#endif
    if(!canshow)
	{
		m_RadlayoutRoot = GetGame().GetWorkspace().CreateWidgets("RadZone_Data/GUI/RadiationUI.layout",parent);
		canshow = true;
	}
	m_RadValueInText = TextWidget.Cast( m_RadlayoutRoot.FindAnyWidget("RadValueInText") );
    m_RadValueOutText = TextWidget.Cast( m_RadlayoutRoot.FindAnyWidget("RadValueOutText") );
    m_RadlayoutRoot.Show(false);
    m_RadValueInText.Show(false);
    m_RadValueOutText.Show(false);
  }

  void SetHasToBeVisible(bool rep)
  {
    m_HasToBeVisible = rep;
  }

  bool GetHasToBeVisible()
  {
    return m_HasToBeVisible;
  }

  void DisplayUI(bool show)
  {
    m_RadlayoutRoot.Show(show);
  }

  void DisplayRadInText(bool rep)
  {
    m_RadValueInText.Show(rep);
  }

  void DisplayRadOutText(bool rep)
  {
    m_RadValueOutText.Show(rep);
  }

  void SetRadInText(int rad_value)
  {
    m_RadValueInText.SetText(rad_value.ToString());
  }

  void SetRadOutText(int rad_value)
  {
    m_RadValueOutText.SetText(rad_value.ToString());
  }
};
