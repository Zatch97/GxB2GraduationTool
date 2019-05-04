// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GXB_BaseLibrary.h"
#include "GXB_Inventory_Widget.generated.h"

struct FGirlItem;
enum class EFaction : uint8;

UCLASS()
class GXB2GRADUATIONTOOL_API UGXB_Inventory_Widget : public UUserWidget
{
	GENERATED_BODY()
	

public:

	//Get the girl number in the inventory by index
	UFUNCTION(BlueprintCallable)
		int32 GetGirlCountInInventoryByIndex(int32 _GirlIndex);

	//Get the count of girls of the given faction excluding the indexes passed as parameter
	int32 GetGirlCountInInventoryByFactionExcludingIndexes(EFaction _Faction, TArray<int32> _RequestedGirlsIndexes);
protected:

	//BeginPlay of UserWidget
	virtual void NativeConstruct() override;

	//The list with all the girls item in the inventory
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FGirlItem> m_GirlsList;


private:
	//Initialize the girls list from Save if it exists
	void InitializeGirlsList();
};
