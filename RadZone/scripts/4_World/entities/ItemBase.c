#ifndef RZFIX
modded class ItemBase extends InventoryItem
{
  void InjectRadAgent(int quantity)
  {
    #ifdef RZDEBUG
    GetRZLogger().LogInfo("Start - InjectRadAgent");
    #endif
    m_AttachedAgents = (m_AttachedAgents & 0x00000011);
    m_AttachedAgents = (m_AttachedAgents | (quantity << 8) );
    #ifdef RZDEBUG
    GetRZLogger().LogInfo("End - InjectRadAgent");
    #endif
  }

  int GetRadAgentQuantity()
  {
    return (m_AttachedAgents >> 8);
  }

  /*override bool OnStoreLoad(ParamsReadContext ctx, int version)
	{
		m_IsStoreLoad = true;
		if ( !super.OnStoreLoad(ctx, version) )
		{
			m_IsStoreLoad = false;
			return false;
		}

		if (version >= 116)
    {
      //rad trasmission system
      if ( !ctx.Read(m_RadAgentQuantity) )
      {
        m_IsStoreLoad = false;
        return false;
      }
    }

		return true;
	}
	//----------------------------------------------------------------

	override void OnStoreSave(ParamsWriteContext ctx)
	{
		super.OnStoreSave(ctx);
    ctx.Write(true);
    ctx.Write(m_RadAgentQuantity);
	}*/
};
#else
modded class ItemBase extends InventoryItem
{
  private int m_RadAgentQuantity = 0;

  override void InitItemVariables()
	{
    super.InitItemVariables();
    RegisterNetSyncVariableInt("m_RadAgentQuantity");
  }

  void InjectRadAgent(int quantity)
  {
    m_RadAgentQuantity = quantity;
  }

  int GetRadAgentQuantity()
  {
    return m_RadAgentQuantity;
  }


  override bool OnStoreLoad(ParamsReadContext ctx, int version)
  {
    super.OnStoreLoad(ctx,version);

    if ( !LoadRadAgentQuantity(ctx, version) )
  			return false;

    return true;
  }

  override void OnStoreSave(ParamsWriteContext ctx)
	{
		super.OnStoreSave(ctx);
    SaveRadAgentQuantity(ctx);
  }

  bool LoadRadAgentQuantity(ParamsReadContext ctx, int version)
	{
		if(!ctx.Read(m_RadAgentQuantity))
			return false;
		return true;
	}

	void SaveRadAgentQuantity(ParamsWriteContext ctx)
	{
		ctx.Write(m_RadAgentQuantity);
	}

};
#endif
