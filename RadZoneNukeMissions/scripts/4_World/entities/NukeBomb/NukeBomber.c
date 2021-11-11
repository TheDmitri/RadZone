class NukeBomber extends House
{
	protected EffectSound m_Sound;

	protected bool m_Drop;
	protected float m_Angle;
	protected float m_Radius;
	protected float m_Speed;
	protected int m_Height;
	protected vector m_Location;

	bool IsInRect(float x, float y, float min_x, float max_x, float min_y, float max_y)
	{
		if ( x > min_x && x < max_x && y > min_y && y < max_y ) return true;
		return false;
	}

	void SetupBomber(vector pos)
	{
		m_Location = pos;
		m_Radius = 5;
		m_Speed = 25.0;
		m_Height = 500;

		GetRZLogger().LogInfo("SetupBomber");

		SetOrientation(Vector(GetOrientation()[0], 0, 0));
		SetDirection(GetDirection());

		vector position = GetPosition();
		m_Angle = Math.Atan2( m_Location[2] - position[2], m_Location[0] - position[0] );
	}

	void NukeBomber()
	{
		SetEventMask( EntityEvent.CONTACT | EntityEvent.SIMULATE );

		if (GetGame().IsClient() || !GetGame().IsMultiplayer())
			PlayLoop();
	}

	void ~NukeBomber()
	{
		if (m_Sound)
			m_Sound.Stop();
	}

	void PlayLoop()
	{
		if (GetGame())
		{
			if (GetGame().GetPlayer())
			{
				PlaySoundLoop("rz_BomberPlane_Sound", 1000);
			}
		}
	}

	void SendMessageClient(string message)
	{
		ref array<Man> players = new array<Man>;
		GetGame().GetPlayers( players );
		foreach( auto player : players  )
		{
			Param1<string> m_MessageParam = new Param1<string>(message);
			GetGame().RPCSingleParam(player, ERPCs.RPC_USER_ACTION_MESSAGE, m_MessageParam, true, player.GetIdentity());
		}
	}

	override void EOnSimulate( IEntity owner, float dt )
	{
		if ( GetGame().IsServer() )
		{
			vector position = GetPosition();

			vector velocity = Vector( Math.Cos( m_Angle ), 0, Math.Sin( m_Angle ) );

			velocity[0] = velocity[0] * (m_Speed*2.5) * dt;
			velocity[2] = velocity[2] * (m_Speed*2.5) * dt;

			vector transform[4];
			GetTransform( transform );
			transform[3] = transform[3] + velocity;
			transform[3][1] = GetGame().SurfaceY(GetPosition()[0], GetPosition()[2]) + m_Height;

			MoveInTime( transform, dt );

			//GetRZLogger().LogInfo("EOnSimulate" + "pos:" + GetPosition());

			EOnBeforeDrop();
		}
	}

	bool EOnBeforeDelete()
	{
		vector position = GetPosition();
		if ( !IsInRect( position[0], position[2], -10.0, 15470.0, -10.0, 15470.0 ) )
		{
			return true;
		}

		return false;
	}

	void EOnBeforeDrop()
	{
		float dist = Math.Sqrt(Math.Pow(m_Location[0] - GetPosition()[0], 2) + Math.Pow(m_Location[2] - GetPosition()[2], 2));
		if (dist <= Math.RandomFloat(0, m_Radius))
		{
			GetRZNMServer().StopSiren();
			if (!m_Drop)
			{
				EOnDrop();
				m_Drop = true;
			}
		}
	}

	void EOnDrop()
	{
		GetRZLogger().LogInfo("EOnDrop");
		House drop = House.Cast( GetGame().CreateObject( "NukeBomb", Vector( GetPosition()[0], GetPosition()[1] - 10, GetPosition()[2]) ));
		drop.SetPosition(Vector( GetPosition()[0], GetPosition()[1] - 10, GetPosition()[2]));
		drop.SetOrientation(Vector(0, 0, 0));
		GetRZLogger().LogInfo("NukeBomb Created");
		GetGame().GetCallQueue( CALL_CATEGORY_SYSTEM ).CallLater( GetGame().ObjectDelete, 20000, false, this );
	}
};
