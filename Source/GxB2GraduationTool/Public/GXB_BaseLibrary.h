// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GXB_BaseLibrary.generated.h"

class UGXB_Girl;
class UTexture2D;

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

//Struct representing a specific girl needed for a recipe
USTRUCT(BlueprintType)
struct FRecipeGirlRequisite
{
	GENERATED_BODY()

	int32 f_GirlId = 0;
	uint8 f_Rank;
	int32 f_NumberNeeded = 0;

	FRecipeGirlRequisite(){}
};

//Struct representing a girl needed for a recipe
USTRUCT(BlueprintType)
struct FRecipeFactionRequisite
{
	GENERATED_BODY()

	EFaction f_Faction;
	uint8 f_Rank;
	int32 f_NumberNeeded = 0;

	FRecipeFactionRequisite(){}
};


UCLASS()
class GXB2GRADUATIONTOOL_API UGXB_BaseLibrary : public UObject
{
	GENERATED_BODY()

public:
	static UTexture2D* LoadTextureFromBase64(FString _Base64String);
};
