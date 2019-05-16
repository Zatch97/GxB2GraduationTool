// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GXB_Inventory_Widget.generated.h"

class UGXB_Girl;
class UGXB_Girl_Widget;
class UGXB_GirlDetails_Widget;
class UWidgetSwitcher;
class FJsonObject;
enum class EFaction : uint8;

UCLASS()
class GXB2GRADUATIONTOOL_API UGXB_Inventory_Widget : public UUserWidget
{
	GENERATED_BODY()


public:

	//Get the girl number in the inventory by index
	UFUNCTION(BlueprintCallable)
		int32 GetGirlCountInInventoryByIndexAndRank(int32 _GirlIndex, uint8 _Rank);

	//Get the count of girls of the given faction excluding the indexes passed as parameter
	int32 GetGirlCountInInventoryByFactionAndRankExcludingIndexes(EFaction _Faction, uint8 _Rank, TArray<int32> _RequestedGirlsIndexes);

	//Add a girl to the inventory
	void AddGirlToInventory(UGXB_Girl* _Girl);

protected:

	//BeginPlay of UserWidget
	virtual void NativeConstruct() override;

	//Save all the girls to Json
	UFUNCTION(BlueprintCallable)
		void SaveGirlsToJson();

	//On Details clicked on any girl widget
	UFUNCTION()
		void OnDetailsClicked(UGXB_Girl* _Girl);

	//The inventory switcher
	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
		UWidgetSwitcher* m_InventorySwitcher = nullptr;

	//The tab with the inventory
	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
		UWidget* m_BaseInventoryTab = nullptr;

	//The girl details tab
	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
		UPanelWidget* m_BaseGirlsPanel = nullptr;

	//The panel to add the girls
	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
		UGXB_GirlDetails_Widget* m_GirlDetails_Widget = nullptr;

	//The BP for the girls widget
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<UGXB_Girl_Widget> m_GirlWidgetBP = nullptr;

	//The list with all the girls item in the inventory
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<UGXB_Girl*> m_GirlsList;

	//Girls widget list
	TArray<UGXB_Girl_Widget*> m_GirlsWidgetList;

	//The last index used for a girl in the inventory
	int32 m_LastExistingIndex = 0;

private:
	//Initialize the girls list from Save if it exists
	void InitializeGirlsList();

	//Update the Widget to display all the girls in the list
	void UpdateWidgetDisplay();

	//Update the last girl index
	void UpdateLastGirlIndex();
};
