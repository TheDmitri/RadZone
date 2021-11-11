class RZCrateSystem
{
	private EntityAI m_Loot=NULL;
	private ref array<EntityAI> m_LootList;
	private ref array<Object> DeadWolfObjs;

    void RZCrateSystem()
    {
			GetRZLogger().LogInfo("CrateSystem - Started !");

			DeadWolfObjs = new array<Object>;
			m_LootList = new array<EntityAI>;

			if ( GetGame().IsServer() ) {
				GetGame ().GetCallQueue (CALL_CATEGORY_SYSTEM).CallLater (this.StartLootSpawner, 2000);
			}
    }

	void StartLootSpawner()
	{
		//GetGame().GameScript.Call( this, "LootSpawner", null );
		LootSpawner();
		GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(LootSpawner, GetCrateSystemConfig().TimerLoot, true);
	}

	void ~RZCrateSystem()
    {

    }

	void LootSpawner()
	{
		int SpawnSeed = RZGetTimeStamp();
		Math.Randomize(SpawnSeed);
		GetRZLogger().LogInfo("LootSpawner - Started !");
		CheckDeadWolfStatus();
		CheckCrateListStatus();
		for( int i=0;i<GetCrateSystemConfig().AreaLocation.Count();i++)
		{
			GetRZLogger().LogInfo("NumberOfCratePerTime: " + GetCrateSystemConfig().AreaLocation.Get(i).RZNbCrate.ToString());
			array<ref RZCrateLocation>m_tempCrateLocations = new array<ref RZCrateLocation>;
			for(int j=0; j< GetCrateSystemConfig().AreaLocation.Get(i).RZNbCrate; j++)
			{
				GetRZLogger().LogInfo("Crates count:"+GetCrateSystemConfig().AreaLocation.Get(i).RZCrateLocations.Count().ToString());
				int fin=-1+GetCrateSystemConfig().AreaLocation.Get(i).RZCrateLocations.Count();
				int WhichZone;
				while(m_tempCrateLocations.Find(GetCrateSystemConfig().AreaLocation.Get(i).RZCrateLocations[WhichZone]) != -1)
				{
					WhichZone=Math.RandomIntInclusive(0,fin);
				}
				m_tempCrateLocations.Insert(GetCrateSystemConfig().AreaLocation.Get(i).RZCrateLocations[WhichZone]);
				GetRZLogger().LogInfo("Crate pos:"+GetCrateSystemConfig().AreaLocation.Get(i).RZCrateLocations[WhichZone].POS.ToString()+"maxloot: "+GetCrateSystemConfig().AreaLocation.Get(i).RZCrateLocations[WhichZone].RZMaxLoot.ToString());
				CreateEzDrop(GetCrateSystemConfig().AreaLocation.Get(i).RZCrateLocations[WhichZone].RZMaxLoot,GetCrateSystemConfig().AreaLocation.Get(i).RZCrateLocations[WhichZone].RZContainer,GetCrateSystemConfig().AreaLocation.Get(i).RZCrateLocations[WhichZone].POS, GetCrateSystemConfig().AreaLocation.Get(i).RZCrateLocations[WhichZone].ORI,GetCrateSystemConfig().AreaLocation.Get(i).RZCrateLocations[WhichZone].Name, i);
			}
		}
	}

	void CreateEzDrop(int maxloot, string container_name,vector v, vector o, string name, int m_i)
	{
		int k,temp;
		if(v[1]==0)v[1]=GetGame().SurfaceY(v[0], v[2]);
		CheckForPreviousCrateAtPosition(v,container_name);
		m_Loot = EntityAI.Cast(GetGame().CreateObject( container_name, "0 0 0", false, true, true));
		GetRZLogger().LogInfo("[LOOTSYSTEM]: Spawned CrateName: "+ name + "- Position: X:"+v[0].ToString()+" Y:"+v[1].ToString()+" Z:"+v[2].ToString());
		int count=-1+GetCrateSystemConfig().ListLoots.Count();
		for(int i=0; i<=count;i++)
		{
			if(GetCrateSystemConfig().ListLoots.Get(i).Name==name){
				k=i;
			}
		}
		for(int l=0;l<GetCrateSystemConfig().ListLoots.Get(k).Loots.Count();l++)
		{
			if(temp>=maxloot && maxloot!=-1)continue;
			if ( GetCrateSystemConfig().ListLoots.Get(k).Loots.Get(l).ProbToSpawn > Math.RandomFloatInclusive(0,1) )
			{
				if (GetCrateSystemConfig().ListLoots.Get(k).Loots.Get(l).AttachmentsToLoot.Count() == 0)
				{
					if(GetCrateSystemConfig().ListLoots.Get(k).Loots.Get(l).IsWeapon)
					{
						Weapon_Base wpn = RadZoneHelper.CreateWeaponWithMagazine(GetCrateSystemConfig().ListLoots.Get(k).Loots.Get(l).LootName, GetCrateSystemConfig().ListLoots.Get(k).Loots.Get(l).Magazine,v);
						//wpn.Update();
						if(wpn)
						{
								m_Loot.GetInventory().AddEntityToInventory(wpn);
								GetRZLogger().LogInfo(GetCrateSystemConfig().ListLoots.Get(k).Loots.Get(l).LootName + " + " + GetCrateSystemConfig().ListLoots.Get(k).Loots.Get(l).Magazine);
						  	temp+=1;
						}
					}
					else
					{
						m_Loot.GetInventory().CreateInInventory(GetCrateSystemConfig().ListLoots.Get(k).Loots.Get(l).LootName);
						GetRZLogger().LogInfo(GetCrateSystemConfig().ListLoots.Get(k).Loots.Get(l).LootName);
						temp+=1;
					}
					continue;
				}
				else
				{
					if(GetCrateSystemConfig().ListLoots.Get(k).Loots.Get(l).IsWeapon)
					{
						Weapon_Base wpn1 = RadZoneHelper.CreateWeaponWithMagazine(GetCrateSystemConfig().ListLoots.Get(k).Loots.Get(l).LootName, GetCrateSystemConfig().ListLoots.Get(k).Loots.Get(l).Magazine,v);
						//wpn1.Update();
						if(wpn1)
						{
							for( int wpnatt=0; wpnatt < GetCrateSystemConfig().ListLoots.Get(k).Loots.Get(l).AttachmentsToLoot.Count() ; wpnatt++)
							{
								if ( GetCrateSystemConfig().ListLoots.Get(k).Loots.Get(l).AttachmentsToLoot.Get(wpnatt).ProbAttachToSpawn > Math.RandomFloatInclusive(0,1) )
								{
									wpn1.GetInventory().CreateAttachment( GetCrateSystemConfig().ListLoots.Get(k).Loots.Get(l).AttachmentsToLoot.Get(wpnatt).AttachName );
									GetRZLogger().LogInfo(GetCrateSystemConfig().ListLoots.Get(k).Loots.Get(l).AttachmentsToLoot.Get(wpnatt).AttachName);
									temp+=1;
								}
							}
							//wpn1.Update();
							m_Loot.GetInventory().AddEntityToInventory(wpn1);
							//m_Loot.Update();
							GetRZLogger().LogInfo(GetCrateSystemConfig().ListLoots.Get(k).Loots.Get(l).LootName + " + " + GetCrateSystemConfig().ListLoots.Get(k).Loots.Get(l).Magazine);
						  temp+=1;
						}
					}
					else
					{
						m_Loot.GetInventory().CreateInInventory(GetCrateSystemConfig().ListLoots.Get(k).Loots.Get(l).LootName);
						temp+=1;
						GetRZLogger().LogInfo(GetCrateSystemConfig().ListLoots.Get(k).Loots.Get(l).LootName);
						for( int parc=0; parc < GetCrateSystemConfig().ListLoots.Get(k).Loots.Get(l).AttachmentsToLoot.Count() ; parc++)
						{
							if ( GetCrateSystemConfig().ListLoots.Get(k).Loots.Get(l).AttachmentsToLoot.Get(parc).ProbAttachToSpawn > Math.RandomFloatInclusive(0,1) )
							{
								m_Loot.GetInventory().CreateInInventory(GetCrateSystemConfig().ListLoots.Get(k).Loots.Get(l).AttachmentsToLoot.Get(parc).AttachName);
								temp+=1;
								GetRZLogger().LogInfo(GetCrateSystemConfig().ListLoots.Get(k).Loots.Get(l).AttachmentsToLoot.Get(parc).AttachName);
							}
						}
					}
				}
			}
		}
		m_Loot.SetPosition(v);
		m_Loot.SetOrientation(o);
		m_LootList.Insert(m_Loot);
		for(int parc_i = 0;parc_i<GetCrateSystemConfig().AreaLocation.Get(m_i).CreaturesLists.Count();parc_i++)
    {
			for(int parc_j=0;parc_j<GetCrateSystemConfig().AreaLocation.Get(m_i).CreaturesLists.Get(parc_i).Max;parc_j++)
			{
				if(GetCrateSystemConfig().AreaLocation.Get(m_i).CreaturesLists.Get(parc_i).ProbToSpawn > Math.RandomFloatInclusive(0,1))
	      {
	        vector offset = v;
	        offset[0] = offset[0] + Math.RandomIntInclusive(-30,30);
	        offset[2] = offset[2] + Math.RandomIntInclusive(-30,30);
	        string creature = GetCrateSystemConfig().AreaLocation.Get(m_i).CreaturesLists.Get(parc_i).CreatureName;
	        Object m_creature=GetGame().CreateObject(creature, snapToGround(offset), false, true, true);
					GetRZLogger().LogInfo("[CREATURE SYSTEM] " + creature +" has spawned !");
					DeadWolfObjs.Insert(m_creature);
	      }
			}
    }
	}

	void CheckForPreviousCrateAtPosition(vector pos, string name)
	{
		array<Object> ObjectArray = new array<Object>;
		GetGame().GetObjectsAtPosition3D(pos, 3, ObjectArray, NULL);
		if (ObjectArray.Count() < 1)return;
		for (int i = 0; i < ObjectArray.Count(); i++)
		{
			if(ObjectArray.Get(i).IsKindOf("SurvivorBase"))
			{
				GetRZLogger().LogInfo("[LOOTSYSTEM]: A player is close by, we don't delete the case in case he is looting it");
				return;
			}
		}
		for (int j = 0; j < ObjectArray.Count(); j++)
		{
			if(ObjectArray.Get(j).IsKindOf(name))
			{
				GetRZLogger().LogInfo("[LOOTSYSTEM]: A previous case has been found at that location and got deleted!");
				GetGame().ObjectDelete(ObjectArray.Get(j));
			}
		}
	}

	private vector snapToGround(vector pos)
    {
        float pos_x = pos[0];
        float pos_z = pos[2];
        float pos_y = GetGame().SurfaceY( pos_x, pos_z );
        vector tmp_pos = Vector( pos_x, pos_y, pos_z );
        tmp_pos[1] = tmp_pos[1] + pos[1];

        return tmp_pos;
    }

	void CheckDeadWolfStatus()
	{
		GetRZLogger().LogInfo("CheckCreatureStatus Started !");
		if(DeadWolfObjs.Count() == 0){
			GetRZLogger().LogInfo("Object:Creature equal to 0!");
            return;
        }
		else
		{
			for(int i = 0; i < DeadWolfObjs.Count(); i++){
				if(DeadWolfObjs.Get(i)!=NULL){
					GetGame().ObjectDelete(DeadWolfObjs.Get(i));
					GetRZLogger().LogInfo("Object:Creature deleted!");
				}
			}
			DeadWolfObjs.Clear();
			return;
		}

	}

	void CheckCrateListStatus()
	{
		GetRZLogger().LogInfo("[LOOTSYSTEM]: [CrateCleaner] !");
		if(m_LootList.Count() == 0){
			GetRZLogger().LogInfo("[LOOTSYSTEM]: CrateList equal to 0!");
            return;
        }
		else
		{
			for(int i = 0; i < m_LootList.Count(); i++){
				if(m_LootList.Get(i)!=NULL){
					GetGame().ObjectDelete(m_LootList.Get(i));
					GetRZLogger().LogInfo("[LOOTSYSTEM]: CrateList has been deleted!");
				}
			}
			m_LootList.Clear();
			return;
		}

	}
};
