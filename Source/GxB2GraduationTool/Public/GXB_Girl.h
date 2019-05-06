// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GXB_Girl.generated.h"

class UTexture2D;
enum class EFaction : uint8;

UCLASS(BlueprintType, Blueprintable, meta = (BlueprintSpawnableComponent))
class GXB2GRADUATIONTOOL_API UGXB_Girl : public UObject
{
	GENERATED_BODY()

public:

	//Get the image texture corresponding to this girl by rank
	UTexture2D* GetImageTextureByRank(uint8 _Rank);

	//Get the total count of girls possessed by rank
	int32 GetTotalCountByRank(uint8 _Rank);

	//Get this girl's id
	FORCEINLINE int32 GetGirlId() { return m_GirlId; }

	//Get the image texture corresponding to this girl by default rank
	FORCEINLINE UTexture2D* GetImageTexture() { return GetImageTextureByRank(m_DefaultRank); }

	//Get the faction of this girl
	FORCEINLINE EFaction GetFaction() { return m_Faction; }

	//Setters
	FORCEINLINE void SetGirlId(int32 _GirlId) { m_GirlId = _GirlId; }
	FORCEINLINE void SetName(FText _Name) { m_Name = _Name; }
	FORCEINLINE void SetFaction(EFaction _Faction) { m_Faction = _Faction; }
	FORCEINLINE void SetRanks(TArray<uint8> _PossibleRanks) { m_PossibleRanks = _PossibleRanks; }
	FORCEINLINE void SetDefaultRank(uint8 _DefaultRank) { m_DefaultRank = _DefaultRank; }
	FORCEINLINE void SetImagesTextures(TMap<uint8, UTexture2D*> _ImageTextures) { m_ImagesTextures = _ImageTextures; }

protected:

	/*BEGIN Json saved values*/

	//The id for this girl
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 m_GirlId = 0;

	//The Name of this girl
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText m_Name;

	//The faction of this girl
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EFaction m_Faction;

	//The possible ranks of this girl
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<uint8> m_PossibleRanks;

	//The default rank to display of this girl
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		uint8 m_DefaultRank;

	//The images of this girl depending on it's rank
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TMap<uint8, UTexture2D*> m_ImagesTextures;

	/*END Json saved values*/


	//The number of this girl in inventory depending on it's rank
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TMap<uint8, int32> m_CountInInventory;

	//The number of this girl in shards depending on it's rank
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TMap<uint8, int32> m_CountInShards;
};
