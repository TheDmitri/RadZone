class ClotheConfigTemp
{
  string SlotName;
  ref array<string> ClothesNames;
  ref array<int> Protection;

  void ClotheConfigTemp(int i,ClotheProtectionSettings m_config)
  {
    SlotName = m_config.RZListSlotProtection.Get(i).SlotName;
    ClothesNames = new array<string>;
    Protection = new array<int>;
    for(int k=0;k<m_config.RZListSlotProtection.Get(i).ListProtections.Count();k++)
    {
      ClothesNames.Insert(m_config.RZListSlotProtection.Get(i).ListProtections.Get(k).ClotheName);
      Protection.Insert(m_config.RZListSlotProtection.Get(i).ListProtections.Get(k).Protection);
    }
  }
}
