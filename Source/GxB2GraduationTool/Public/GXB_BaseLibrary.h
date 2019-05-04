// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GXB_BaseLibrary.generated.h"

class UGXB_Girl;

//Enum representing all of the games Factions
UENUM(BlueprintType)
enum class EFaction : uint8
{
	GHOST UMETA(DisplayName = "Ghost"),
	HUMAN UMETA(DisplayName = "Human"),
	MONSTER UMETA(DisplayName = "Monster"),
	FAIRY UMETA(DisplayName = "Fairy"),
	DARK UMETA(DisplayName = "Dark"),
	LIGHT UMETA(DisplayName = "Light")
};

//Struct representing a girl item in the inventory ie with it's number possessed
USTRUCT(BlueprintType)
struct FGirlItem
{
	GENERATED_BODY()

	UGXB_Girl* f_Girl = nullptr;
	int32 f_CountInInventory = 0;
	int32 f_CountInShards = 0;

	FGirlItem(){}

	//Get the total count of the girl represented by this item
	int32 GetTotalCount()
	{
		return f_CountInInventory + f_CountInShards;
	}
};


//Struct representing a specific girl needed for a recipe
USTRUCT(BlueprintType)
struct FRecipeGirlRequisite
{
	GENERATED_BODY()

	int32 f_GirlIndex = 0;
	int32 f_NumberNeeded = 0;

	FRecipeGirlRequisite(){}
};

//Struct representing a girl needed for a recipe
USTRUCT(BlueprintType)
struct FRecipeFactionRequisite
{
	GENERATED_BODY()

	EFaction f_Faction;
	int32 f_NumberNeeded = 0;

	FRecipeFactionRequisite(){}
};


UCLASS()
class GXB2GRADUATIONTOOL_API UGXB_BaseLibrary : public UObject
{
	GENERATED_BODY()

};
