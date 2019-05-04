// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GXB_Girl.generated.h"

class UTexture2D;
enum class EFaction : uint8;

UCLASS()
class GXB2GRADUATIONTOOL_API UGXB_Girl : public UObject
{
	GENERATED_BODY()

public:
	//Get this girl's index
	int32 GetGirlIndex() { return m_GirlIndex; }

	//Get the image texture corresponding to this girl
	UTexture2D* GetImageTexture() { return m_ImageTexture; }

	//Get the faction of this girl
	EFaction GetFaction() { return m_Faction; }

protected:

	//The index for this girl
	int32 m_GirlIndex = 0;

	//The Name of this girl
	FName m_Name;

	//The faction of this girl
	EFaction m_Faction;

	//The rank of this girl
	uint8 m_Rank = 0;

	//The image of this girl
	UTexture2D* m_ImageTexture = nullptr;
	
};
