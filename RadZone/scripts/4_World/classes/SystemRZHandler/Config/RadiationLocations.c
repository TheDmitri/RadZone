class RadiationLocations
{
  int RequiredProtection;
  int CriticalProtection;
  float AmountGivenAfterCriticalProtection;
  float ClothesQuantityMultiplier;
  ref array<string> Statut;
  ref array<float> X;
  ref array<float> Y;
  ref array<float> Radius;
  ref array<float> X1;
  ref array<float> Y1;
  ref array<float> X2;
  ref array<float> Y2;
  ref array<float> Xc;
  ref array<float> Yc;
  ref array<bool> IsSquareZone;
  ref array<bool> IsMsgActive;
  ref array<string> MsgEnterZone;
  ref array<string> MsgExitZone;
  ref array<int> NbRadGiven;

    void RadiationLocations(){

    }

    void InitRadiationLocations(RadiationAreaSettings radAreaSettings)
	  {
      RequiredProtection = radAreaSettings.RequiredProtection;
      CriticalProtection = radAreaSettings.CriticalProtection;
      AmountGivenAfterCriticalProtection = radAreaSettings.AmountGivenAfterCriticalProtection;
      ClothesQuantityMultiplier = radAreaSettings.ClothesQuantityMultiplier;
      Statut = new array<string>;
      X = new array<float>;
      Y = new array<float>;
      Radius = new array<float>;
      X1 = new array<float>;
      Y1 = new array<float>;
      X2 = new array<float>;
      Y2 = new array<float>;
      Xc = new array<float>;
      Yc = new array<float>;
      IsSquareZone = new array<bool>;
      IsMsgActive = new array<bool>;
      MsgEnterZone = new array<string>;
      MsgExitZone = new array<string>;
      NbRadGiven =  new array<int>;

      TransferRadConfig(radAreaSettings);
    }

    void TransferRadConfig(RadiationAreaSettings radAreaSettings)
    {
      int cpt = -1 + radAreaSettings.RadiationAreaLocation.Count();
      for(int i = 0; i<=cpt ; i++)
      {
        Statut.Insert(radAreaSettings.RadiationAreaLocation.Get(i).RadiationZoneStatut);
        X.Insert(radAreaSettings.RadiationAreaLocation.Get(i).X);
        Y.Insert(radAreaSettings.RadiationAreaLocation.Get(i).Y);
        Radius.Insert(radAreaSettings.RadiationAreaLocation.Get(i).Radius);
        X1.Insert(radAreaSettings.RadiationAreaLocation.Get(i).X1);
        Y1.Insert(radAreaSettings.RadiationAreaLocation.Get(i).Y1);
        X2.Insert(radAreaSettings.RadiationAreaLocation.Get(i).X2);
        Y2.Insert(radAreaSettings.RadiationAreaLocation.Get(i).Y2);
        Xc.Insert((radAreaSettings.RadiationAreaLocation.Get(i).X2-radAreaSettings.RadiationAreaLocation.Get(i).X1)*0.5);
        Yc.Insert((radAreaSettings.RadiationAreaLocation.Get(i).Y2-radAreaSettings.RadiationAreaLocation.Get(i).Y1)*0.5);
        IsSquareZone.Insert(radAreaSettings.RadiationAreaLocation.Get(i).IsSquareZone);
        NbRadGiven.Insert(radAreaSettings.RadiationAreaLocation.Get(i).NbSickGivenForRadiation);
        IsMsgActive.Insert(radAreaSettings.RadiationAreaLocation.Get(i).IsMsgActive);
        MsgEnterZone.Insert(radAreaSettings.RadiationAreaLocation.Get(i).MsgEnterZone);
        MsgExitZone.Insert(radAreaSettings.RadiationAreaLocation.Get(i).MsgExitZone);
      }
    }
}
