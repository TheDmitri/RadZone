class OldRadiationZoneLocation
{
  string RadiationZoneStatut;
  float X, Y, Radius;
  bool IsSquareZone;
	float X1,Y1,X2,Y2;
  bool 			IsMsgActive;
	string 		MsgEnterZone;
	string 		MsgExitZone;
  bool  IsOnlyGasMask;
  int   NbSickGivenForRadiation;


    void OldRadiationZoneLocation( string radiationzonestatut, float x, float y, float radius,bool isquarezone,float x1, float y1, float x2, float y2,bool ismsgactive, string msgenterzone, string msgexitzone,bool isonlygasmask,int giveradsickness, )
	  {
      IsOnlyGasMask = isonlygasmask;
      NbSickGivenForRadiation = giveradsickness;
  		IsSquareZone=isquarezone;
      RadiationZoneStatut = radiationzonestatut;
      X = x;
      Y = y;
  		X1= x1;
  		Y1= y1;
  		X2= x2;
  		Y2= y2;
      Radius = radius;
      IsMsgActive = ismsgactive;
      MsgEnterZone = msgenterzone;
      MsgExitZone = msgexitzone;
    }
}
