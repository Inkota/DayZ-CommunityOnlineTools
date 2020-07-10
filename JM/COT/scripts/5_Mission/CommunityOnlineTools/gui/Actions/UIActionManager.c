class UIActionManager
{
	static GridSpacerWidget CreateGridSpacer( Widget parent, int rows, int columns )
	{
		Widget widget = GetGame().GetWorkspace().CreateWidgets( "JM/COT/GUI/layouts/uiactions/Wrappers/" + rows.ToString() + "/GridSpacer" + columns.ToString() + ".layout", parent );

		if ( widget )
		{
			return GridSpacerWidget.Cast( widget );
		}

		return NULL;
	}

	static Widget CreateActionRows( Widget parent )
	{
		Widget widget = GetGame().GetWorkspace().CreateWidgets( "JM/COT/GUI/layouts/uiactions/UIActionContentRows.layout", parent );

		return widget;
	}
	
	static Widget CreateSpacer( Widget parent )
	{
		Widget widget = GetGame().GetWorkspace().CreateWidgets( "JM/COT/GUI/layouts/uiactions/UISpacer.layout", parent );

		return widget;
	}

	static Widget CreatePanel( Widget parent, int color = 0x00000000, float height = -1 )
	{
		Widget widget = GetGame().GetWorkspace().CreateWidgets( "JM/COT/GUI/layouts/uiactions/UIPanel.layout", parent );

		widget.SetColor( color );

		if ( height != -1 )
		{
			float w;
			float h;
			widget.SetFlags( WidgetFlags.VEXACTSIZE );
			widget.GetSize( w, h );
			widget.SetSize( w, height );
		}

		return widget;
	}

	static UIActionButton CreateButton( Widget parent, string button, Class instance, string funcname )
	{
		Widget widget = GetGame().GetWorkspace().CreateWidgets( "JM/COT/GUI/layouts/uiactions/UIActionButton.layout", parent );

		UIActionButton action;
		widget.GetScript( action );

		if ( action )
		{
			action.SetCallback( instance, funcname );
			action.SetButton( button );

			return action;
		}

		return NULL;
	}

	static UIActionEditableText CreateEditableText( Widget parent, string label, Class instance = NULL, string funcname = "", string text = "", string button = "" )
	{
		Widget widget = GetGame().GetWorkspace().CreateWidgets( "JM/COT/GUI/layouts/uiactions/UIActionEditableText.layout", parent );

		UIActionEditableText action;
		widget.GetScript( action );

		if ( action )
		{
			if ( button == "" || instance == NULL || funcname == "" )
			{
				action.HasButton( false );
			} else 
			{
				action.HasButton( true );

				action.SetButton( button );
			}

			action.SetCallback( instance, funcname );

			action.SetLabel( label );
			action.SetText( text );

			return action;
		}

		return NULL;
	}

	static UIActionDropdownList CreateDropdownBox( Widget parent, Widget dropDownParent, string label, array< string > values, Class instance = NULL, string funcname = "" )
	{
		Widget widget = GetGame().GetWorkspace().CreateWidgets( "JM/COT/GUI/layouts/uiactions/UIActionDropdownList.layout", parent );

		UIActionDropdownList action;
		widget.GetScript( action );

		if ( action )
		{
			if ( !dropDownParent )
				dropDownParent = parent;
				
			action.InitListWidget( dropDownParent );

			action.SetItems( values );

			action.SetCallback( instance, funcname );

			action.SetLabel( label );
			action.SetText( values[0] );

			return action;
		}

		return NULL;
	}

	static UIActionEditableVector CreateEditableVector( Widget parent, string label, Class instance = NULL, string funcname = "", string button = "" )
	{
		Widget widget = GetGame().GetWorkspace().CreateWidgets( "JM/COT/GUI/layouts/uiactions/UIActionEditableVector.layout", parent );

		UIActionEditableVector action;
		widget.GetScript( action );

		if ( action )
		{
			if ( button == "" || instance == NULL || funcname == "" )
			{
				action.HasButton( false );
			} else 
			{
				action.HasButton( true );

				action.SetButton( button );
			}

			action.SetCallback( instance, funcname );

			action.SetLabel( label );

			return action;
		}

		return NULL;
	}

	static UIActionCheckbox CreateCheckbox( Widget parent, string label, Class instance = NULL, string funcname = "", bool checked = false )
	{
		Widget widget = GetGame().GetWorkspace().CreateWidgets( "JM/COT/GUI/layouts/uiactions/UIActionCheckbox.layout", parent );

		UIActionCheckbox action;
		widget.GetScript( action );

		if ( action )
		{
			action.SetCallback( instance, funcname );
			action.SetLabel( label );
			action.SetChecked( checked );

			return action;
		}

		return NULL;
	}

	static UIActionText CreateText( Widget parent, string label, string text = "", Class instance = NULL, string funcname = "", UIActionHAlign lha = UIActionHAlign.LEFT, UIActionHAlign lva = UIActionHAlign.CENTER, UIActionHAlign tha = UIActionHAlign.RIGHT, UIActionHAlign tva = UIActionHAlign.CENTER )
	{
		Widget widget = GetGame().GetWorkspace().CreateWidgets( "JM/COT/GUI/layouts/uiactions/UIActionText.layout", parent );

		UIActionText action;
		widget.GetScript( action );

		if ( action )
		{
			action.SetCallback( instance, funcname );
			action.SetLabel( label );
			action.SetText( text );

			action.SetLabelHAlign( lha );
			action.SetLabelVAlign( lva );

			action.SetTextHAlign( tha );
			action.SetTextVAlign( tva );

			return action;
		}

		return NULL;
	}

	static UIActionSelectBox CreateSelectionBox( Widget parent, string label, notnull ref array< string > options, Class instance = NULL, string funcname = "" )
	{
		Widget widget = GetGame().GetWorkspace().CreateWidgets( "JM/COT/GUI/layouts/uiactions/UIActionSelectBox.layout", parent );

		UIActionSelectBox action;
		widget.GetScript( action );

		if ( action )
		{
			action.SetCallback( instance, funcname );
			action.SetLabel( label );
			action.SetSelections( options );

			return action;
		}

		return NULL;
	}

	static UIActionSlider CreateSlider( Widget parent, string label, float min, float max, Class instance = NULL, string funcname = "" )
	{
		Widget widget = GetGame().GetWorkspace().CreateWidgets( "JM/COT/GUI/layouts/uiactions/UIActionSlider.layout", parent );

		UIActionSlider action;
		widget.GetScript( action );

		if ( action )
		{
			action.SetCallback( instance, funcname );
			action.SetLabel( label );
			action.SetMin( min );
			action.SetMax( max );
			action.SetStepValue( 0 );

			return action;
		}

		return NULL;
	}

	static UIActionScroller CreateScroller( Widget parent )
	{
		Widget widget = GetGame().GetWorkspace().CreateWidgets( "JM/COT/GUI/layouts/uiactions/UIActionScroller.layout", parent );

		UIActionScroller action;
		widget.GetScript( action );

		if ( action )
		{
			return action;
		}

		return NULL;
	}
}