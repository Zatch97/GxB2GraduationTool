// Fill out your copyright notice in the Description page of Project Settings.


#include "GXB_Viewport_Widget.h"

#include "GXB_Inventory_Widget.h"
#include "GXB_AddGirl_Widget.h"

#include "WidgetSwitcher.h"

//Begin play of Userwidget
void UGXB_Viewport_Widget::NativeConstruct()
{
	if (m_InventoryWidget != nullptr && m_AddGirlWidget != nullptr)
	{
		m_AddGirlWidget->InitializeReferences(m_InventoryWidget);
	}
}

//Switch to the next widget
void UGXB_Viewport_Widget::SwitchWidget()
{
	if (m_WidgetSwitcher != nullptr)
	{
		int32 index = m_WidgetSwitcher->GetActiveWidgetIndex();
		index++;

		if (index >= m_WidgetSwitcher->GetNumWidgets())
		{
			index = 0;
		}

		m_WidgetSwitcher->SetActiveWidgetIndex(index);
	}
}
