class JMConfirmation extends ScriptedWidgetEventHandler 
{
	private Widget layoutRoot;
	
	private JMWindowBase m_Window;
    
    private TextWidget m_TextTitle;
    private TextWidget m_TextMessage;

    private Widget m_Buttons1Panel;
    private Widget m_Buttons2Panel;
    private Widget m_Buttons3Panel;

    private ButtonWidget m_Button1;
    private ButtonWidget m_Button2;
    private ButtonWidget m_Button3;

    private TextWidget m_ButtonText1;
    private TextWidget m_ButtonText2;
    private TextWidget m_ButtonText3;

    private string m_Callback1;
    private string m_Callback2;
    private string m_Callback3;

	void JMConfirmation() 
	{
	}

	void ~JMConfirmation() 
	{
	}

	void OnWidgetScriptInit( Widget w )
	{
		layoutRoot = w;
		layoutRoot.SetHandler( this );
	}

	void Init( JMWindowBase wdw )
	{
		m_Window = wdw;

		OnInit();
	}

	void OnInit()
	{
        GetGame().GetWorkspace().CreateWidgets( "JM/COT/gui/layouts/confirmation.layout", layoutRoot );

        m_TextTitle = TextWidget.Cast( layoutRoot.FindAnyWidget( "confirmation_title_text" ) );
        m_TextMessage = TextWidget.Cast( layoutRoot.FindAnyWidget( "confirmation_message_text" ) );

        m_Buttons1Panel = layoutRoot.FindAnyWidget( "confirmation_buttons_1" );
        m_Buttons2Panel = layoutRoot.FindAnyWidget( "confirmation_buttons_2" );
        m_Buttons3Panel = layoutRoot.FindAnyWidget( "confirmation_buttons_3" );
	}

	bool IsVisible()
	{
		return layoutRoot.IsVisible();
	}

	override bool OnClick( Widget w, int x, int y, int button )
	{
        if ( w == NULL )
        {
            return false;
        }

		if ( w == m_Button1 )
		{
            Close();

            if ( m_Callback1 != "" )
            {
                GetGame().GetCallQueue( CALL_CATEGORY_GUI ).CallByName( m_Window.GetForm(), m_Callback1 );
            }
			return true;
		}

		if ( w == m_Button2 )
		{
            Close();

            if ( m_Callback2 != "" )
            {
                GetGame().GetCallQueue( CALL_CATEGORY_GUI ).CallByName( m_Window.GetForm(), m_Callback2 );
            }
			return true;
		}

		if ( w == m_Button3 )
		{
            Close();

            if ( m_Callback3 != "" )
            {
                GetGame().GetCallQueue( CALL_CATEGORY_GUI ).CallByName( m_Window.GetForm(), m_Callback3 );
            }
			return true;
		}

		return false;
	}

    void CreateConfirmation_One( string title, string message, string button1Title, string button1Callback )
    {
        layoutRoot.Show( true );

        m_Buttons1Panel.Show( true );

        m_Buttons2Panel.Show( false );
        m_Buttons3Panel.Show( false );

        m_TextTitle.SetText( title );
        m_TextMessage.SetText( message );

        if ( Class.CastTo( m_Button1, m_Buttons1Panel.FindAnyWidget( "confirmation_button_1" ) ) )
        {
            m_Callback1 = button1Callback;

            m_ButtonText1 = TextWidget.Cast( m_Button1.FindAnyWidget( "confirmation_text" ) );
            m_ButtonText1.SetText( button1Title );
        }
    }

    void CreateConfirmation_Two( string title, string message, string button1Title, string button2Title, string button1Callback, string button2Callback )
    {        
        layoutRoot.Show( true );

        m_Buttons2Panel.Show( true );

        m_Buttons1Panel.Show( false );
        m_Buttons3Panel.Show( false );

        m_TextTitle.SetText( title );
        m_TextMessage.SetText( message );

        if ( Class.CastTo( m_Button1, m_Buttons2Panel.FindAnyWidget( "confirmation_button_1" ) ) )
        {
            m_Callback1 = button1Callback;

            m_ButtonText1 = TextWidget.Cast( m_Button1.FindAnyWidget( "confirmation_text" ) );
            m_ButtonText1.SetText( button1Title );
        }

        if ( Class.CastTo( m_Button2, m_Buttons2Panel.FindAnyWidget( "confirmation_button_2" ) ) )
        {
            m_Callback2 = button2Callback;

            m_ButtonText2 = TextWidget.Cast( m_Button2.FindAnyWidget( "confirmation_text" ) );
            m_ButtonText2.SetText( button2Title );
        }
    }

    void CreateConfirmation_Three( string title, string message, string button1Title, string button2Title, string button3Title, string button1Callback, string button2Callback, string button3Callback )
    {        
        layoutRoot.Show( true );

        m_Buttons3Panel.Show( true );

        m_Buttons1Panel.Show( false );
        m_Buttons2Panel.Show( false );

        m_TextTitle.SetText( title );
        m_TextMessage.SetText( message );

        if ( Class.CastTo( m_Button1, m_Buttons3Panel.FindAnyWidget( "confirmation_button_1" ) ) )
        {
            m_Callback1 = button1Callback;

            m_ButtonText1 = TextWidget.Cast( m_Button1.FindAnyWidget( "confirmation_text" ) );
            m_ButtonText1.SetText( button1Title );
        }

        if ( Class.CastTo( m_Button2, m_Buttons3Panel.FindAnyWidget( "confirmation_button_2" ) ) )
        {
            m_Callback2 = button2Callback;

            m_ButtonText2 = TextWidget.Cast( m_Button2.FindAnyWidget( "confirmation_text" ) );
            m_ButtonText2.SetText( button2Title );
        }

        if ( Class.CastTo( m_Button3, m_Buttons3Panel.FindAnyWidget( "confirmation_button_3" ) ) )
        {
            m_Callback3 = button3Callback;

            m_ButtonText3 = TextWidget.Cast( m_Button3.FindAnyWidget( "confirmation_text" ) );
            m_ButtonText3.SetText( button2Title );
        }
    }

    void Close()
    {
        layoutRoot.Show( false );
    }

	void OnShow()
	{
	}

	void OnHide() 
	{
	}

	Widget GetLayoutRoot() 
	{
		return layoutRoot;
	}
}