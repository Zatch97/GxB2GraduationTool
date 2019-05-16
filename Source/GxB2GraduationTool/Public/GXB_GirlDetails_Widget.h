// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GXB_GirlDetails_Widget.generated.h"

class UGXB_Girl;
class UGXB_RankInventory_Widget;

class UTextBlock;
class UPanelWidget;

UCLASS()
class GXB2GRADUATIONTOOL_API UGXB_GirlDetails_Widget : public UUserWidget
{
	GENERATED_BODY()


public:

	//Change the current girl and update the details
	UFUNCTION(BlueprintCallable)
		void ChangeGirl(UGXB_Girl* _NewGirl);

protected:

	//Begin Play of UserWidget
	virtual void NativeConstruct() override;

	//Initialize all the rank inventory widgets with all the ranks possible
	void InitializeRankInventoryWidgets();

	//Update the displayed details
	void UpdateDetails();

	//The text displaying the Girls Name
	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
		UTextBlock* m_NameText = nullptr;

	//The panel to add the RankInventory widgets
	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
		UPanelWidget* m_RankInventoryPanel = nullptr;


	//Blueprint to instantiate RankinventoyWidget
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<UGXB_RankInventory_Widget> m_RankInventoryWidgetBP = nullptr;
	   
	//All the ranks widgets for this girl
	TArray<UGXB_RankInventory_Widget*> m_RankInventoryWidgets;

	//Current girl to display it's details
	UGXB_Girl* m_CurrentGirl = nullptr;

};
