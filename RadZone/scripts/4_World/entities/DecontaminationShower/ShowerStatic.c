class DecontaminationShowerStatic extends DecontaminationShower{};
class DecontaminationShowerUnlimitedStatic extends DecontaminationShower
{
  int WaterQty = 2000;

  void DecontaminationShowerUnlimitedStatic()
  {
      SetAllowDamage(false);
  }

  void ~DecontaminationShowerUnlimitedStatic()
  {

  }

  override void OnWorkStart()
  {
    #ifdef RZDEBUG
    GetRZLogger().LogInfo("Shower_OnWork start"+"current energy: "+GetCompEM().GetEnergy().ToString());
    #endif
    if ( GetGame().IsClient()  ||  !GetGame().IsMultiplayer() )
    {
      StartSound();
      PlayParticle();
    }
  }

  override void OnWork( float consumed_energy )
  {
      if ( !GetCompEM().HasEnoughStoredEnergy())
      GetCompEM().SwitchOff();

      DecontaminatePlayerNearby();
      ConsumeFakeTank();

      #ifdef RZDEBUG
      GetRZLogger().LogInfo("Shower_OnWork on"+"current energy: "+GetCompEM().GetEnergy().ToString());
      #endif
  }

  void ConsumeFakeTank()
  {
    if (WaterQty != 0)
    {
      WaterQty-=500;
      GetCompEM().AddEnergy(m_WorkingTimePerLiter);
    }
    if(WaterQty == 0)
    {
      GetCompEM().SwitchOff();
    }
  }

  override void CanStartShower()
  {
    if(WaterQty >= 500)
    {
      GetCompEM().SwitchOn();
    }
  }

  override void SetActions()
  {
    super.SetActions();
    AddAction(ActionTurnOnAdminDecontaminationShower);
    AddAction(ActionTurnOffDecontaminationShower);
  }
};
