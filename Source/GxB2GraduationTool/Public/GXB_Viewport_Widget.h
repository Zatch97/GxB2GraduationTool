// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GXB_Viewport_Widget.generated.h"

class UWidgetSwitcher;
class UGXB_AddGirl_Widget;
class UGXB_Inventory_Widget;

UCLASS()
class GXB2GRADUATIONTOOL_API UGXB_Viewport_Widget : public UUserWidget
{
	GENERATED_BODY()
	

protected:

	//Begin play of Userwidget
	virtual void NativeConstruct() override;

	//Switch to the next widget
	UFUNCTION(BlueprintCallable)
		void SwitchWidget();


	//The Widget switcher
	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
		UWidgetSwitcher* m_WidgetSwitcher = nullptr;

	//The inventory Widget
	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
		UGXB_Inventory_Widget* m_InventoryWidget = nullptr;

	//The add girl Widget
	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
		UGXB_AddGirl_Widget* m_AddGirlWidget = nullptr;


};
