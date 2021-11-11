class Geigercounter_Sova extends ItemBase
{
	ItemBase					m_Battery; // Attached battery9v

	void Geigercounter_Sova()
	{
		 GetCompEM().SwitchOff();
	}

	void ~Geigercounter_Sova()
	{
	}

	override void EEItemAttached ( EntityAI item, string slot_name )
	{
		super.EEItemAttached ( item, slot_name );

		ItemBase item_IB = ItemBase.Cast( item );

		if ( item_IB.IsKindOf("Battery9V") )
		{
			m_Battery = item_IB;
		}
	}


	override void EEItemDetached ( EntityAI item, string slot_name )
	{
		super.EEItemDetached ( item, slot_name );

		ItemBase item_IB = ItemBase.Cast( item );

		if ( item_IB.IsKindOf("Battery9V") )
		{
			m_Battery = NULL;
		}
	}

	override void OnWorkStart()
	{

	}

	override void OnWork( float consumed_energy )
	{
		if(GetGame().IsServer())
		{
			PlayerBase player;
			Class.CastTo(player, GetHierarchyRootPlayer());

			if(!player || !player.IsAlive())
			{
				GetCompEM().SwitchOff();
			}
		}
	}

	override void OnWorkStop()
	{
		super.OnWorkStop();
	}

	override void SetActions()
	{
		super.SetActions();
		AddAction(ActionTurnOnWhileInHands);
		AddAction(ActionTurnOffWhileInHands);
		AddAction(ActionGetRadClotheLevel);
		AddAction(ActionGetRadClotheLevelTarget);
	}
};
