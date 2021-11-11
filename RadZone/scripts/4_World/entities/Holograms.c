modded class Hologram
{

	override string ProjectionBasedOnParent()
	{
		ItemBase item_in_hands = ItemBase.Cast( m_Player.GetHumanInventory().GetEntityInHands() );

		 if ( item_in_hands.IsInherited( ShowerKit ))
		{
			return "DecontaminationShower";
		}

		return super.ProjectionBasedOnParent();
	}

	override EntityAI PlaceEntity( EntityAI entity_for_placing )
	{
		//string-based comparison
		if ( entity_for_placing.IsInherited( ShowerKit ) || entity_for_placing.IsInherited( DecontaminationShower ) ) //special little snowflakes
		{
			return entity_for_placing;
		}

		return super.PlaceEntity(entity_for_placing);
	}

	override vector SetOnGround( vector position )
	{
		vector from = position;
		vector ground;
		vector player_to_projection_vector;
		float projection_diameter = GetProjectionDiameter();

		ground = Vector(0, - Math.Max( projection_diameter, SMALL_PROJECTION_GROUND ), 0);
		/*
		if( projection_diameter < SMALL_PROJECTION_GROUND )
		{
			ground = Vector(0, - SMALL_PROJECTION_GROUND, 0);
		}
		else
		{
			ground = Vector(0, - projection_diameter, 0);
		}
		*/

		vector to = from + ground;
		vector contact_pos;
		//vector contact_dir;
		int contact_component;

		DayZPhysics.RaycastRV( from, to, contact_pos, m_ContactDir, contact_component, NULL, NULL, m_Projection, false, false );

		HideWhenClose( contact_pos );

		if(m_Projection.GetType() == "DecontaminationShower")
		{
			contact_pos = contact_pos + Vector(0,0.42,0);
		}

		return contact_pos;
	}

	override void EvaluateCollision(ItemBase action_item = null)
	{
		ItemBase item_in_hands = ItemBase.Cast( m_Player.GetHumanInventory().GetEntityInHands() );

		if(item_in_hands)
		{
			 if ( item_in_hands.IsInherited( ShowerKit ))
			{
				SetIsColliding(false);
				return;
			}
		}
		super.EvaluateCollision();
	}
};
