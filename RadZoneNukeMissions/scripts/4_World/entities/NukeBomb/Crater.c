class NukeCrater extends IrradiedDirtPile
{
  Particle m_ParticleCrater;

  void NukeCrater()
  {
      if (GetGame().IsClient() || !GetGame().IsMultiplayer())
      {
        m_ParticleCrater = Particle.PlayOnObject(ParticleList.REMAININGSMOKE, this);
      }
  }

  void RZDelete()
  {
    GetGame().ObjectDelete(this);
  }

  void ~NukeCrater()
  {
    if (m_ParticleCrater)
      m_ParticleCrater.Stop();
  }
};
