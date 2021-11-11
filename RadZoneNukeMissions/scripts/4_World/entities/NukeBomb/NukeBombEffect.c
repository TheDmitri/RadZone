class NukeBombEffect extends House
{
		Particle m_ParticleEfx;
		Particle m_Particle2Efx;
		Particle m_Particle3Efx;
		protected EffectSound m_RZNukeLoop;

		void NukeBombEffect()
		{
			if (GetGame().IsClient() || !GetGame().IsMultiplayer()){
	            GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(InitSound, 15);
			}
			if(GetGame().IsServer())
			{
				GetRZLogger().LogInfo("NukeBombEffect()");
				GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(DeleteNuke, 90000);
			}
		}

	  void DeleteNuke()
		{
			if (m_ParticleEfx)
				m_ParticleEfx.Stop();

				if (m_Particle3Efx)
					m_Particle3Efx.Stop();

				if (m_Particle2Efx)
					m_Particle2Efx.Stop();
			GetGame().ObjectDelete(this);
		}

		void InitSound()
		{
			PlaySoundSetLoop( m_RZNukeLoop, "rz_NukeBomb_SoundSet", 0.1, 24.5);
			m_RZNukeLoop.SetSoundLoop(false);
			m_RZNukeLoop.SetSoundAutodestroy( true );
			StartParticleChemine();
			StartPPEffect();
	    //GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(StartParticleChemine, 13000);
		}

		void StartPPEffect()
		{
			thread NukeColorization(80000);
			thread CameraShakeHandler();
		}

		void CameraShakeHandler()
		{
			int nbtime = 60;
			while(nbtime > 0)
			{
				CreateCameraShake(5)
				nbtime--;
				Sleep(100);
			}
		}

		void CreateCameraShake(float intensity)
		{
			GetGame().GetPlayer().GetCurrentCamera().SpawnCameraShake(Math.Clamp(intensity, 0.25, 1), 1.75, 4, 4);
		}

		void NukeColorization(int time)
		{
			int td = 0;
			while (td < time) {
				float time_value = 1 / time * td;
				PPEffects.SetColorizationNV(0.70, 0.23, 0.0);
				if(td < 5000)
				{
					PPEffects.SetEVValuePP(2);
					PPEffects.SetNVParams(3.0, 2.0, 9.0, 1.0);
				}
				else
				{
					PPEffects.SetEVValuePP(1);
					PPEffects.SetNVParams(1.0, 0.0, 2.35, 2.75);
				}
				PPEffects.UpdateColorize();
				td += 10;

				Sleep(10);
			}

			PPEffects.ResetAll();
			PPEffects.SetEVValuePP(0);
			PPEffects.SetColorizationNV(1.0, 1.0, 1.0);
			PPEffects.SetNVParams(1.0, 0.0, 2.35, 2.75);
			PPEffects.UpdateColorize();
		}

    void StartParticleChemine()
    {
				m_Particle3Efx = Particle.PlayInWorld(ParticleList.RING,this.GetPosition());
				m_Particle2Efx = Particle.PlayInWorld(ParticleList.CHEMINE,this.GetPosition());
			  //m_Particle3Efx = Particle.PlayOnObject(ParticleList.RING, this);
        //m_Particle2Efx = Particle.PlayOnObject(ParticleList.CHEMINE, this);
				GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(StartParticleMushroom, 5200);
    }

		void StartParticleMushroom()
    {
			  m_ParticleEfx = Particle.PlayInWorld(ParticleList.NUKEBOMB,this.GetPosition());
        //m_ParticleEfx = Particle.PlayOnObject(ParticleList.NUKEBOMB, this);
    }

		void ~NukeBombEffect()
		{
			if (m_ParticleEfx)
				m_ParticleEfx.Stop();

			if (m_Particle2Efx)
				m_Particle2Efx.Stop();

			if (m_Particle3Efx)
				m_Particle3Efx.Stop();
		}
};
