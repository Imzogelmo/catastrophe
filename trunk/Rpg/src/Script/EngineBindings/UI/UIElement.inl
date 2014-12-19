// catastrophe rpg engine
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.


#include <Catastrophe/Gui/Widget.h>

#include "Script/MonoEngineBinding.h"



void MonoEngineBinding::Widget_SetPosition( Widget* self, Vector2 position )
{
	SAFE_CALL(self, SetPosition(position));
}


enum WidgetFloatComponent
{
	WidgetFloatComponent_x,
	WidgetFloatComponent_y,
	WidgetFloatComponent_w,
	WidgetFloatComponent_h
};

void MonoEngineBinding::Widget_SetFloatValue( Widget* self, float value, int type )
{
	if( self == null )
		return;

	switch(type)
	{
		case WidgetFloatComponent_x:
			self->SetX(value);
			break;
		case WidgetFloatComponent_y:
			self->SetY(value);
			break;
		case WidgetFloatComponent_w:
			self->SetWidth(value);
			break;
		case WidgetFloatComponent_h:
			self->SetHeight(value);
			break;
	}
}


float MonoEngineBinding::Widget_GetFloatValue( Widget* self, int type )
{
	float value = 0.f;

	if( self != null )
	{
		switch(type)
		{
			case WidgetFloatComponent_x:
				value = self->GetX();
				break;
			case WidgetFloatComponent_y:
				value = self->GetY();
				break;
			case WidgetFloatComponent_w:
				value = self->GetWidth();
				break;
			case WidgetFloatComponent_h:
				value = self->GetHeight();
				break;
		}
	}

	return value;
}


void MonoEngineBinding::Widget_SetDimensions( Widget* self, Rectf rect )
{
	SAFE_CALL(self, SetDimensions(rect));
}


enum WidgetPropertyType
{
	WidgetPropertyType_Active,
	WidgetPropertyType_Selected,
	WidgetPropertyType_Visible,
	WidgetPropertyType_Enabled,
};

void MonoEngineBinding::Widget_SetProperty( Widget* self, int prop, bool value )
{
	if( !self )
		return;

	if( prop == WidgetPropertyType_Active )
		self->SetActive(value);
	else if( prop == WidgetPropertyType_Selected )
		self->SetSelected(value);
	else if( prop == WidgetPropertyType_Visible )
		self->SetVisible(value);
	else if( prop == WidgetPropertyType_Enabled )
		self->SetEnabled(value);
}


bool MonoEngineBinding::Widget_GetProperty( Widget* self, int prop )
{
	bool value = false;
	if( self )
	{
		if( prop == WidgetPropertyType_Active )
			value = self->IsActive();
		else if( prop == WidgetPropertyType_Selected )
			value = self->IsSelected();
		else if( prop == WidgetPropertyType_Visible )
			value = self->IsVisible();
		else if( prop == WidgetPropertyType_Enabled )
			value = self->IsEnabled();
	}

	return value;
}


void MonoEngineBinding::Widget_SetSize( Widget* self, Vector2 size )
{
	SAFE_CALL(self, SetSize(size));
}


void MonoEngineBinding::Widget_SetColor( Widget* self, Color color )
{
	SAFE_CALL(self, SetColor(color));
}


void MonoEngineBinding::Widget_SetBlendMode( Widget* self, BlendMode blendMode )
{
	SAFE_CALL(self, SetBlendMode(blendMode));
}


void MonoEngineBinding::Widget_AddChild( Widget* self, Widget* element )
{
	SAFE_CALL(self, AddChild(element));
}


void MonoEngineBinding::Widget_InsertChild( Widget* self, int index, Widget* element )
{
	SAFE_CALL(self, InsertChild(index, element));
}


void MonoEngineBinding::Widget_RemoveChild( Widget* self, Widget* element )
{
	SAFE_CALL(self, RemoveChild(element));
}


void MonoEngineBinding::Widget_RemoveAllChildren( Widget* self )
{
	SAFE_CALL(self, RemoveAllChildren());
}


void MonoEngineBinding::Widget_Remove( Widget* self )
{
	SAFE_CALL(self, Remove());
}


void MonoEngineBinding::Widget_SetParent( Widget* self, Widget* parent )
{
	SAFE_CALL(self, SetParent(parent));
}


Vector2 MonoEngineBinding::Widget_GetPosition( Widget* self )
{
	SAFE_CALL_RETURN(self, GetPosition(), Vector2::Zero);
}


Vector2 MonoEngineBinding::Widget_GetSize( Widget* self )
{
	SAFE_CALL_RETURN(self, GetSize(), Vector2::Zero);
}


Rectf MonoEngineBinding::Widget_GetDimensions( Widget* self )
{
	SAFE_CALL_RETURN(self, GetDimensions(), Rectf::Zero);
}


Vector2 MonoEngineBinding::Widget_GetScreenPosition( Widget* self )
{
	SAFE_CALL_RETURN(self, GetScreenPosition(), Vector2::Zero);
}


bool MonoEngineBinding::Widget_IsRoot( Widget* self )
{
	SAFE_CALL_RETURN(self, IsRoot(), false);
}


Color MonoEngineBinding::Widget_GetColor( Widget* self )
{
	SAFE_CALL_RETURN(self, GetColor(), Color::White());
}


BlendMode MonoEngineBinding::Widget_GetBlendMode( Widget* self )
{
	SAFE_CALL_RETURN(self, GetBlendMode(), BlendMode::Alpha);
}


int MonoEngineBinding::Widget_GetNumChildren( Widget* self, bool recurse )
{
	SAFE_CALL_RETURN(self, GetNumChildren(recurse), 0);
}


Widget* MonoEngineBinding::Widget_GetChild( Widget* self, int index )
{
	SAFE_CALL_RETURN(self, GetChild(index), 0);
}


bool MonoEngineBinding::Widget_HasChild( Widget* self, Widget* element )
{
	SAFE_CALL_RETURN(self, HasChild(element), false);
}


MonoArray* MonoEngineBinding::Widget_GetChildren( Widget* self )
{
	//
	return 0;
}


Widget* MonoEngineBinding::Widget_GetParent( Widget* self )
{
	SAFE_CALL_RETURN(self, GetParent(), 0);
}


Widget* MonoEngineBinding::Widget_GetRoot( Widget* self )
{
	SAFE_CALL_RETURN(self, GetRoot(), 0);
}


Rectf MonoEngineBinding::Widget_GetBoundingRect( Widget* self, bool recurse )
{
	SAFE_CALL_RETURN(self, GetBoundingRect(recurse), Rectf::Zero);
}


void MonoEngineBinding::Widget_AddRef( Widget* self )
{
	SAFE_CALL(self, AddRef());
}


void MonoEngineBinding::Widget_ReleaseRef( Widget* self )
{
	SAFE_CALL(self, ReleaseRef());
}



void MonoEngineBinding::BindWidget()
{
	SetNamespace("CatastropheEngine.UI.UIElement::");

	AddInternalCall("SetPosition", Widget_SetPosition);
	AddInternalCall("SetSize", Widget_SetSize);
	AddInternalCall("SetDimensions", Widget_SetDimensions);
	AddInternalCall("SetColor", Widget_SetColor);
	AddInternalCall("SetBlendMode", Widget_SetBlendMode);
	AddInternalCall("SetProperty", Widget_SetProperty);
	AddInternalCall("AddChild", Widget_AddChild);
	AddInternalCall("InsertChild", Widget_InsertChild);
	AddInternalCall("RemoveChild", Widget_RemoveChild);
	AddInternalCall("RemoveAllChildren", Widget_RemoveAllChildren);
	AddInternalCall("Remove", Widget_Remove);
	AddInternalCall("SetParent", Widget_SetParent);
	AddInternalCall("GetPosition", Widget_GetPosition);
	AddInternalCall("GetSize", Widget_GetSize);
	AddInternalCall("GetDimensions", Widget_GetDimensions);
	AddInternalCall("GetColor", Widget_GetColor);
	AddInternalCall("GetBlendMode", Widget_GetBlendMode);
	AddInternalCall("GetScreenPosition", Widget_GetScreenPosition);
	AddInternalCall("GetRoot", Widget_IsRoot);
	AddInternalCall("GetProperty", Widget_GetProperty);
	AddInternalCall("GetNumChildren", Widget_GetNumChildren);
	AddInternalCall("GetChild", Widget_GetChild);
	AddInternalCall("HasChild", Widget_HasChild);
	AddInternalCall("GetChildren", Widget_GetChildren);
	AddInternalCall("GetParent", Widget_GetParent);
	AddInternalCall("GetRoot", Widget_GetRoot);
	AddInternalCall("GetBoundingRect", Widget_GetBoundingRect);
	AddInternalCall("AddRef", Widget_AddRef);
	AddInternalCall("ReleaseRef", Widget_ReleaseRef);
}


