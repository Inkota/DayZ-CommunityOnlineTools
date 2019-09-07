
modded class PlayerBase
{
	protected JMPlayerInstance m_AuthenticatedPlayer;

	protected bool m_HasGodMode;
	protected bool m_IsInvisible;

	override void Init()
	{
		super.Init();

		RegisterNetSyncVariableBool( "m_HasGodMode" );
		RegisterNetSyncVariableBool( "m_IsInvisible" );
	}

	override void OnVariablesSynchronized()
	{
		super.OnVariablesSynchronized();

		if ( m_IsInvisible )
		{
			ClearFlags( EntityFlags.VISIBLE, true );
		} else
		{
			SetFlags( EntityFlags.VISIBLE, true );
		}
		//SetInvisible( m_IsInvisible );
	}

	void SetAuthenticatedPlayer( ref JMPlayerInstance player )
	{
		m_AuthenticatedPlayer = player;
	}

	JMPlayerInstance GetAuthenticatedPlayer()
	{
		return m_AuthenticatedPlayer;
	}

	bool HasGodMode()
	{
		return m_HasGodMode;
	}

	bool IsInvisible()
	{
		return m_IsInvisible;
	}

	void SetGodMode( bool mode )
	{
		if ( GetGame().IsServer() )
		{
			m_HasGodMode = mode;

			SetAllowDamage( !m_HasGodMode );
		}
	}

	void SetInvisibility(bool mode)
	{
		if ( GetGame().IsServer() )
		{
			m_IsInvisible = mode

			SetSynchDirty();
		}
	}
}