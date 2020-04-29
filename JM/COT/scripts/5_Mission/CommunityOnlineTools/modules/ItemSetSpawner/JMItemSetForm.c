class JMItemSetForm extends JMFormBase
{
	private Widget m_ActionsWrapper;

	private autoptr array< ref UIActionButton > m_ItemSetButtons;

	private JMItemSetSpawnerModule m_Module;

	void JMItemSetForm()
	{
		m_ItemSetButtons = new array< ref UIActionButton >;
	}

	void ~JMItemSetForm()
	{
	}

	protected override bool SetModule( ref JMRenderableModuleBase mdl )
	{
		return Class.CastTo( m_Module, mdl );
	}

	override void OnInit()
	{
		m_ActionsWrapper = layoutRoot.FindAnyWidget( "actions_wrapper" );
	}

	override void OnShow()
	{
		array< string > items = new array< string >;
		items.Copy( m_Module.GetItemSets() );
		
		JMStatics.SortStringArray( items );

		for ( int j = 0; j < items.Count(); j++ )
		{
			Widget wrapper = UIActionManager.CreateGridSpacer( m_ActionsWrapper, 1, 3 );

			string name = items[j];

			UIActionManager.CreateText( wrapper, name );
			
			UIActionButton selButton = UIActionManager.CreateButton( wrapper, "Selected Player(s)", this, "SpawnOnPlayers" );
			selButton.SetData( new JMItemSpawnerButtonData( name ) );
			m_ItemSetButtons.Insert( selButton );

			UIActionButton curButton = UIActionManager.CreateButton( wrapper, "Cursor", this, "SpawnOnCursor" );
			curButton.SetData( new JMItemSpawnerButtonData( name ) );
			m_ItemSetButtons.Insert( curButton );
		}
	}

	override void OnHide() 
	{
		Widget child = m_ActionsWrapper.GetChildren();
		while ( child != NULL )
		{
			child.Unlink();
			
			child = child.GetSibling();
		}

		m_ItemSetButtons.Clear();
	}

	void SpawnOnPlayers( UIEvent eid, ref UIActionBase action ) 
	{
		JMItemSpawnerButtonData data;
		if ( !Class.CastTo( data, action.GetData() ) )
			return;

		m_Module.SpawnPlayers( data.ClassName, GetSelectedPlayers() );
	}

	void SpawnOnCursor( UIEvent eid, ref UIActionBase action ) 
	{
		JMItemSpawnerButtonData data;
		if ( !Class.CastTo( data, action.GetData() ) )
			return;

		m_Module.SpawnPosition( data.ClassName, GetCursorPos() );
	}
}