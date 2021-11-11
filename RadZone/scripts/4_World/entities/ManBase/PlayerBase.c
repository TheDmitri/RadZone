class InsideRZ{

	string RZName;
	bool   RZStatut;

	void InsideRZ(){
		RZName="";
		RZStatut=false;
	}
};

modded class PlayerBase extends ManBase
{
	private ref array<string>m_SLOTS = {"Mask","Headgear","Body","Gloves","Legs","Feet"};
	private ref array<string>m_Suits = {"GP5GasMask","NBCHoodBase","NBCJacketBase","NBCGloves_ColorBase","NBCPantsBase","NBCBootsBase"};
	ref array<string> m_SLOTS_ALL = {"Head","Shoulder","Melee","Headgear","Mask","Eyewear","Hands","LeftHand","Gloves","Armband","Vest","Body","Back","Hips","Legs","Feet"};
	private int cpt=0;
	int InnerRadQty=0;
	bool AntiRadPillsActivated;
	bool IsGasMaskWorking;
	bool UndefinedOrRuined;
	ref InsideRZ RZIsInside;
	bool IsUnprotected;
	float RadChanceVomit;
	float RadChanceBleeding;
	float RadBloodLossDamage;
	float RadHealthDamage;
	float RadHighMultiplier;
	float AmountGivenAfterCriticalProtection;
	int CriticalProtection;
	int NbSickGivenForRadiation;
	int QtyRadReducedPerMin;
	int RadProtection=0;
	float ClothesQuantityMultiplier;

	override void Init()
	{
		super.Init();
		UndefinedOrRuined = false;
		IsUnprotected=false;
		AntiRadPillsActivated=false;
		RZIsInside=new InsideRZ;

		RegisterNetSyncVariableInt("InnerRadQty");
	}

	void GiveRadSickness(float NbSickGiven)
	{
		if (GetGame().IsServer() || !GetGame().IsMultiplayer())
		{
			if(InnerRadQty>=600)return;
			if(!AntiRadPillsActivated || InnerRadQty < 150)
			{
				InsertAgent(RZAgents.RADSICK,NbSickGiven);
				#ifdef RZDEBUG
				InnerRadQty += NbSickGiven;
				SetSynchDirty();
				GetRZLogger().LogInfo(this.GetIdentity().GetName()+" no_pills "+"is taking radiation point => Rad quantity:" + InnerRadQty.ToString());
				#endif
			}
			else
			{
				m_AgentPool.SetAgentCount(RZAgents.RADSICK,150);
				#ifdef RZDEBUG
				GetRZLogger().LogInfo(this.GetIdentity().GetName() + " with_anti_rad_pills "+"is taking radiation point=> Rad quantity:" + InnerRadQty.ToString());
				#endif
				return;
			}
		}
	}

	void SetInnerRadQty(int qty)
	{
		InnerRadQty = qty;
		SetSynchDirty();
	}

	void SetRadDamageOnClothes()
	{
		if (GetGame().IsServer() || !GetGame().IsMultiplayer())
		{
			if (GetGame().IsServer() || !GetGame().IsMultiplayer())
			{
				int count = m_SLOTS.Count();
				for (int i = 0; i < count ;i++)
				{
					EntityAI SuitsPart;
					SuitsPart = this.FindAttachmentBySlotName(m_SLOTS.Get(i));
					if(SuitsPart == NULL || SuitsPart.IsRuined())return;
					float Health = SuitsPart.GetMaxHealth();
					SuitsPart.AddHealth( "", "", -Health*(GetRadConfig().SuitsDamage*0.01));
				}
			}
		}
	}

	override void EEItemAttached(EntityAI item, string slot_name)
	{
		if (GetGame().IsServer() || !GetGame().IsMultiplayer())
		{
			#ifdef RZDEBUG
			GetRZLogger().LogInfo("EEItemAttached: item: " + item.GetType() + "slot_name: " + slot_name);
	  	#endif
			if(!RZIsInside.RZStatut)
			{
				HandleRadAgentsOnClothes(item);
			}
		}
		super.EEItemAttached(item, slot_name);
	}

	override void EEItemDetached(EntityAI item, string slot_name)
	{
		super.EEItemDetached(item, slot_name);
	}

	void HandleRadAgentsOnClothes(EntityAI item)
	{
		#ifdef RZDEBUG
		GetRZLogger().LogInfo("HandleRadAgentsOnClothesd");
		#endif
		ItemBase item_IB = ItemBase.Cast(item);
		if(item_IB.GetRadAgentQuantity() > 0)
		{
			GiveRadSickness(item_IB.GetRadAgentQuantity());
		}
	}

	bool CheckForRadiationOnClothes()
	{
		if (GetGame().IsServer() || !GetGame().IsMultiplayer())
		{
			for (int i = 0; i < m_SLOTS_ALL.Count();i++)
			{
				EntityAI Clothes;
				Clothes = FindAttachmentBySlotName(m_SLOTS_ALL.Get(i));

				if (Clothes != NULL && !Clothes.IsRuined())
				{
					ItemBase m_item_IB = ItemBase.Cast(Clothes);
					if(m_item_IB.GetRadAgentQuantity()>0)
					{
						return true;
					}
				}
		  }
			return false;
    }
		return false;
	}

	void GiveRadQtyToPlayerClothes(int qty)
  {
		#ifdef RZDEBUG
		GetRZLogger().LogInfo("Start - GiveRadQtyToPlayerClothes");
		#endif
    if (GetGame().IsServer() || !GetGame().IsMultiplayer())
		{
			for (int i = 0; i < m_SLOTS_ALL.Count();i++)
			{
				EntityAI Clothes;
				Clothes = FindAttachmentBySlotName(m_SLOTS_ALL.Get(i));

				if (Clothes != NULL && !Clothes.IsRuined())
				{
					ItemBase item_IB = ItemBase.Cast(Clothes);
					item_IB.InjectRadAgent(qty);
				}
		  }
    }
	}
};
