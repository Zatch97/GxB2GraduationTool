// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GXB_Inventory_Widget.generated.h"

class UGXB_Girl;
class UGXB_Girl_Widget;
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
protected:

	//BeginPlay of UserWidget
	virtual void NativeConstruct() override;

	//The panel to add the girls
	UPROPERTY(meta=(BindWidgetOptional))
		UPanelWidget* m_BaseGirlsPanel = nullptr;

	//The BP for the girls widget
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<UGXB_Girl_Widget> m_GirlWidgetBP = nullptr;

	//The list with all the girls item in the inventory
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<UGXB_Girl*> m_GirlsList;

	//Girls widget list
	TArray<UGXB_Girl_Widget*> m_GirlsWidgetList;

private:
	//Initialize the girls list from Save if it exists
	void InitializeGirlsList();
};
