class JMRenderableModuleBase extends JMModuleBase
{
	private ref JMWindowBase m_Window;

	private ButtonWidget m_MenuButton;

	private int m_MenuButtonColour = 0;

	void JMRenderableModuleBase()
	{
		SetMenuButtonColour( 1, 1, 0, 0 );
	}

	bool InitButton( Widget button_bkg )
	{
		Class.CastTo( m_MenuButton, button_bkg.FindAnyWidget( "btn" ) );

		if ( button_bkg && m_MenuButton )
		{
			m_MenuButton.SetColor( m_MenuButtonColour );

			TextWidget ttl = TextWidget.Cast( button_bkg.FindAnyWidget( "ttl" ) );
			ttl.SetText( GetLocalisedTitle() );

			ImageWidget btn_img = ImageWidget.Cast( button_bkg.FindAnyWidget( "btn_img" ) );
			TextWidget btn_txt = TextWidget.Cast( button_bkg.FindAnyWidget( "btn_txt" ) );

			if ( ImageIsIcon() )
			{
				btn_txt.Show( false );
				btn_img.Show( true );

				btn_img.LoadImageFile( 0, "set:" + GetImageSet() + " image:" + GetIconName() );
			} else
			{
				btn_txt.Show( true );
				btn_img.Show( false );

				btn_txt.SetText( GetIconName() );
			}

			return true;
		}

		return false;
	}

	void SetMenuButtonColour( float r, float g, float b, float alpha )
	{
		m_MenuButtonColour = ARGB( r * 255, g * 255, b * 255, alpha * 255 );
		if ( m_MenuButton )
			m_MenuButton.SetColor( m_MenuButtonColour );
	}

	ButtonWidget GetMenuButton()
	{
		return m_MenuButton;
	}

	JMFormBase GetForm()
	{
		if ( !m_Window )
			return NULL;

		return m_Window.GetForm();
	}

	string GetInputToggle()
	{
		return "";
	}

	string GetLayoutRoot()
	{
		return "";
	}

	string GetTitle()
	{
		return "";
	}

	string GetLocalisedTitle()
	{
		string text = Widget.TranslateString( "#" + GetTitle() );

		if ( text == "" || text.Get( 0 ) == " " )
		{
			return GetTitle();
		}
		
		return text;
	}

	string GetImageSet()
	{
		return "";
	}

	string GetIconName()
	{
		return "";
	}

	bool ImageIsIcon()
	{
		return false;
	}

	bool HasAccess()
	{
		return true;
	}

	bool HasButton()
	{
		return true;
	}

	bool IsVisible()
	{
		if ( !m_Window )
			return false;
		
		return m_Window.IsVisible();
	}

	void Show()
	{
		if ( HasAccess() )
		{
			if ( !m_Window )
			{
				m_Window = GetCOTWindowManager().Create();
				m_Window.SetModule( this );
			}

			m_Window.Show();
		}
	}

	void Hide()
	{
		//Print( "+" + Type().ToString() + "::Hide" );
		//Print( "  m_Window=" + m_Window );
		if ( m_Window )
		{
			delete m_Window;
		}
		//Print( "-" + Type().ToString() + "::Hide" );
	}

	void ToggleShow()
	{
		if ( IsVisible() ) 
		{
			Hide();
		} else
		{
			if ( GetGame().GetUIManager().GetMenu() )
			{
				return;
			}

			if ( !GetCommunityOnlineToolsBase().IsActive() )
			{
				COTCreateLocalAdminNotification( new StringLocaliser( "STR_COT_NOTIFICATION_WARNING_TOGGLED_OFF" ) );
				return;
			}
			
			Show();
		}
	}

	override void OnSettingsUpdated()
	{
		super.OnSettingsUpdated();

		if ( GetForm() )
		{
			GetForm().OnSettingsUpdated();
		}
	}

	override void OnClientPermissionsUpdated()
	{
		super.OnClientPermissionsUpdated();

		bool hasAccess = HasAccess();

		if ( GetForm() && hasAccess )
		{
			GetForm().OnClientPermissionsUpdated();
		}

		if ( IsVisible() && !hasAccess )
		{
			Hide();
		}
	}
	
	override void RegisterKeyMouseBindings() 
	{
		super.RegisterKeyMouseBindings();

		if ( GetInputToggle() != "" )
		{
			RegisterBinding( new JMModuleBinding( "Input_ToggleShow", GetInputToggle(), true ) );
		}
	}

	void Input_ToggleShow( UAInput input )
	{
		if ( !input.LocalClick() )
			return;
		
		ToggleShow();
	}
}