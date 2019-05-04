// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GXB_BaseLibrary.h"
#include "GXB_Recipe_Widget.generated.h"

class UGXB_Inventory_Widget;
struct FRecipeGirlRequisite;
struct FRecipeFactionRequisite;

UCLASS()
class GXB2GRADUATIONTOOL_API UGXB_Recipe_Widget : public UUserWidget
{
	GENERATED_BODY()

public:

	//Check if this recipe is possible with the current inventory
	UFUNCTION(BlueprintCallable)
		bool IsRecipePossible();

	//Get the indexes of the Girls Requested
	TArray<int32> GetRequestedGirlsIndexes();

protected:
	//RecipeGirlRequisite needed for this recipe
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FRecipeGirlRequisite> m_GirlRequisites;

	//RecipeFactionRequisite needed for this recipe
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FRecipeFactionRequisite> m_FactionGirlRequisites;

	//Reference to the inventory widget
	UGXB_Inventory_Widget* m_InventoryReference = nullptr;
};
