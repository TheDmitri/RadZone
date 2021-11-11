class IrradiedDirtPile extends House
{
  Particle m_ParticleEfx;

  void IrradiedDirtPile()
  {
    if (GetGame().IsClient() || !GetGame().IsMultiplayer())
    {
      m_ParticleEfx = Particle.PlayOnObject(ParticleList.IRRADIEDPILE, this);
    }
  }

  void ~IrradiedDirtPile()
  {
    if (m_ParticleEfx)
      m_ParticleEfx.Stop();
  }

  void RZDelete()
  {
    GetGame().ObjectDelete(this);
  }
};
