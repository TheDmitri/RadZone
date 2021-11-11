class NukeBomb extends House
{
	ref Timer m_Timer;
	protected EffectSound m_RZWhistle;

	void NukeBomb()
	{
			EOnInit();
			if(GetGame().IsServer())
			{
				GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(EOnLand, 23000);
			}
			if (GetGame().IsClient() || !GetGame().IsMultiplayer()){
					GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(InitSound, 8000);
			}
	}

	void ~NukeBomb()
	{
		if (m_Timer)
			m_Timer.Stop();
	}

	void InitSound()
	{
		PlaySoundSet( m_RZWhistle, "rz_Whistle_SoundSet", 0, 0);
		m_RZWhistle.SetSoundLoop(false);
		m_RZWhistle.SetSoundAutodestroy( true );
	}

	void EOnInit()
	{
		vector m_TempPos = GetPosition();
		vector m_TempOri = GetOrientation();

		if (GetGame().IsServer())
		{
			SetOrientation(Vector(GetOrientation()[0], 0, 0));
			SetDirection(GetDirection());

			m_Timer = new Timer();
			m_Timer.Run(0.01, this, "NukeFall", NULL, true);
		}
	}

	void EOnFall()
	{
		if (GetVelocity(this).Length() >= 0)
		{
			CreateDynamicPhysics(PhxInteractionLayers.DYNAMICITEM);
			EnableDynamicCCD(true);

			SetOrientation(Vector(GetOrientation()[0], 0, -90));
			SetVelocity(this, Vector(0, -20, 0));
		}
	}

	void EOnLand()
	{
			m_Timer.Stop();
			SetSynchDirty();
			private NukeBombEffect m_NukeBombEffet = NukeBombEffect.Cast(GetGame().CreateObject( "NukeBombEffect", this.GetPosition(), false, true, true));
			DestroyTrees(this.GetPosition(),250);
			//Explode(DT_EXPLOSION);
			GetRZNMServer().StartAfterExplosion();
			GetGame().ObjectDelete(this);
	}

	private void DestroyTrees(vector pos, int radius)
	{
		array<Object> nearest_objects = new array<Object>();

		GetGame().GetObjectsAtPosition ( pos, radius, nearest_objects, null );

		for ( int i = 0; i < nearest_objects.Count(); i++ )
		{
			Object nearest_object = nearest_objects.Get(i);
			if (!nearest_object)
				continue;
			if (nearest_object.IsWoodBase())
			{
				nearest_object.SetHealth(0);
			}
		}
	}

	void NukeFall()
	{
		if (GetGame().IsServer())
		{
				GetRZLogger().LogInfo("NukeFall()");
				EOnFall();
		}
	}

	bool IsGround(float height)
	{
		vector m_Start = this.GetPosition();
		vector m_End = this.GetPosition() - Vector(0, height, 0);

		vector m_Hit;
		vector m_HitPos;

		int m_HitIndex;

		return DayZPhysics.RaycastRV(m_Start, m_End, m_HitPos, m_Hit, m_HitIndex, NULL, NULL, this);
	}

	override bool CanPutIntoHands( EntityAI parent )
	{
		return false;
	}

	override bool CanPutInCargo ( EntityAI parent )
	{
		return false;
	}

	override bool IsInventoryVisible()
    {
        return true;
    }

	override bool CanUseConstruction()
    {
        return true;
    }
};
