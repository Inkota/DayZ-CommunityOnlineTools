class JMESPWidgetHandler extends ScriptedWidgetEventHandler 
{
	static JMESPForm espMenu;
	static JMESPModule espModule;

	static bool UseClassName = false;

	private Widget layoutRoot;

	private CheckBoxWidget m_chbx_SelectedObject;
	private TextWidget m_txt_ObjectName;
	private ButtonWidget m_btn_ToggleActions;
	private ImageWidget m_img_ToggleActions;

	private Widget m_pnl_Actions;

	private UIActionScroller m_scrler_Actions;
	private Widget m_rows_Actions;

	private bool m_DidUnlink;

	private vector m_LastPosition;
	private string m_TargetType;

	bool ShowOnScreen;

	int Width;
	int Height;
	float FOV;
	vector ScreenPos;

	JMESPMeta Info;

	void OnWidgetScriptInit( Widget w )
	{
		m_DidUnlink = false;

		layoutRoot = w;
		layoutRoot.SetHandler( this );

		Init();
	}

	void ~JMESPWidgetHandler()
	{
		#ifdef JM_COT_ESP_DEBUG
		Print( "+JMESPWidgetHandler::~JMESPWidgetHandler();" );
		#endif

		OnHide();

		#ifdef JM_COT_ESP_DEBUG
		Print( "-JMESPWidgetHandler::~JMESPWidgetHandler();" );
		#endif
	}

	void Init() 
	{
		Widget header;
		Class.CastTo( header, layoutRoot.FindAnyWidget( "esp_object_header" ) );

		Class.CastTo( m_chbx_SelectedObject, header.FindAnyWidget( "esp_select_checkbox" ) );
		Class.CastTo( m_txt_ObjectName, header.FindAnyWidget( "esp_object_name" ) );
		Class.CastTo( m_btn_ToggleActions, header.FindAnyWidget( "esp_toggle_button" ) );

		if ( Class.CastTo( m_img_ToggleActions, header.FindAnyWidget( "esp_toggle_button_image" ) ) )
		{
			m_img_ToggleActions.LoadImageFile( 0, "set:dayz_gui image:icon_expand" );
			m_img_ToggleActions.LoadImageFile( 1, "set:dayz_gui image:icon_collapse" );
		}

		Class.CastTo( m_pnl_Actions, layoutRoot.FindAnyWidget( "esp_actions_container" ) );

		m_scrler_Actions = UIActionManager.CreateScroller( m_pnl_Actions );
		Class.CastTo( m_rows_Actions, m_scrler_Actions.GetContentWidget() );

		HideActions();

		JMScriptInvokers.ON_DELETE_ALL.Insert( OnDeleteAll );
	}

	void Show()
	{
		layoutRoot.Show( true );
		OnShow();
	}

	void Hide()
	{
		OnHide();
		layoutRoot.Show( false );

		JMScriptInvokers.ON_DELETE_ALL.Remove( OnDeleteAll );
	}

	void ToggleESPActions()
	{
		if ( m_pnl_Actions.IsVisible() )
		{
			HideActions();
		} else
		{
			ShowActions();
		}
	}

	void ShowActions()
	{
		m_pnl_Actions.Show( true );

		m_img_ToggleActions.SetImage( 0 );
	}

	void HideActions()
	{		
		m_pnl_Actions.Show( false );

		m_img_ToggleActions.SetImage( 1 );
	}

	void OnShow()
	{
		GetGame().GetUpdateQueue( CALL_CATEGORY_GUI ).Insert( this.Update );
	}

	void OnHide() 
	{
		GetGame().GetUpdateQueue( CALL_CATEGORY_GUI ).Remove( this.Update );
	}

	void OnDeleteAll()
	{
		if ( !Info.type.IsInherited( JMESPViewTypePlayer ) && m_chbx_SelectedObject.IsChecked() )
		{
			Hide();
		}
	}

	float ATan( float a )
	{
		return Math.Asin( a ) / Math.Acos( a );
	}

	private vector Player_GetPosition()
	{
		Human man;
		if ( !Class.CastTo( man, Info.target ) )
		{
			return Info.target.GetPosition();
		}

		if ( man.IsInTransport() )
		{
			return man.GetPosition() + "0 1.1 0";
		}

		vector position = man.GetPosition() + "0 1.85 0";

		int bone = man.GetBoneIndexByName( "Head" );

		if ( bone != -1 )
		{
			position = man.GetBonePositionWS( bone ) + "0 0.2 0";
		}

		return position;
	}

	vector GetPosition()
	{
		if ( Info.target )
		{
			if ( Info.type.IsInherited( JMESPViewTypePlayer ) )
			{
				return Player_GetPosition();
			} else
			{
				return Info.target.GetPosition();
			}
		}

		return m_LastPosition;
	}

	void Update() 
	{
		if ( Info == NULL ) 
		{
			ShowOnScreen = false;
			Hide();
			return;
		}

		m_LastPosition = GetPosition();

		ScreenPos = GetGame().GetScreenPos( m_LastPosition );

		float distance = vector.Distance( GetCurrentPosition(), m_LastPosition );

		GetScreenSize( Width, Height );

		if ( ScreenPos[0] <= 0 || ScreenPos[1] <= 0 )
		{
			ShowOnScreen = false;
		} else 
		{
			ShowOnScreen = true;
		}

		if ( ShowOnScreen && ( ScreenPos[0] >= Width || ScreenPos[1] >= Height ) )
		{
			ShowOnScreen = false;
		}

		if ( ShowOnScreen && ScreenPos[2] < 0 )
		{
			ShowOnScreen = false;
		}

		if ( ShowOnScreen && Info )
		{
			layoutRoot.SetPos( ScreenPos[0], ScreenPos[1], true );

			string text = "";

			if ( Info.type.IsInherited( JMESPViewTypePlayer ) )
			{
				text = Info.name + " (" + distance + "m)";
			} else
			{
				if ( UseClassName )
				{
					text = m_TargetType + " (" + distance + "m)";
				} else
				{
					text = Info.name + " (" + distance + "m)";
				}
			}

			m_txt_ObjectName.SetText( text );

			//Info.UpdateActions();

			m_scrler_Actions.UpdateScroller();
			
			layoutRoot.Show( true );
		} else 
		{
			layoutRoot.Show( false );
		}
	}

	ref Widget GetLayoutRoot() 
	{
		return layoutRoot;
	}

	void SetInfo( ref JMESPMeta info, out Widget action_rows )
	{
		action_rows = m_rows_Actions;

		Info = info;
		
		if ( Info == NULL || Info.target == NULL ) 
		{
			ShowOnScreen = false;
			Hide();
			return;
		}

		m_chbx_SelectedObject.SetChecked( JM_GetSelected().IsObjectSelected( Info.target ) );

		m_TargetType = Info.target.GetType();

		m_txt_ObjectName.SetColor( Info.colour );

		m_chbx_SelectedObject.Show( true );
			
		ShowOnScreen = true;
		
		Show();
	}

	override bool OnClick( Widget w, int x, int y, int button )
	{
		if ( w == NULL )
		{
			return false;
		}
		
		if ( w == m_chbx_SelectedObject )
		{
			if ( Info.type.IsInherited( JMESPViewTypePlayer ) )
			{
				JMScriptInvokers.MENU_PLAYER_CHECKBOX.Invoke( Info.player.GetGUID(), m_chbx_SelectedObject.IsChecked() );
			} else if ( Info.target )
			{
				if ( m_chbx_SelectedObject.IsChecked() )
				{
					JMScriptInvokers.ADD_OBJECT.Invoke( Info.target );
				} else
				{
					JMScriptInvokers.REMOVE_OBJECT.Invoke( Info.target );
				}
			}

			return true;
		}

		if ( w == m_btn_ToggleActions )
		{
			ToggleESPActions();

			return true;
		}

		return false;
	}
}