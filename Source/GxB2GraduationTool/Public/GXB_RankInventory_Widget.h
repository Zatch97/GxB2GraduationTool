// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GXB_RankInventory_Widget.generated.h"

class UTextBlock;

UCLASS()
class GXB2GRADUATIONTOOL_API UGXB_RankInventory_Widget : public UUserWidget
{
	GENERATED_BODY()


public:
	//Initialize the number of girls in shards and in inventory for this rank
	void InitializeRankInventory(uint8 _Rank);

	//Update the girls numbers
	void UpdateGirlsNumbers(int32 _NumberInInventory, int32 _NumberInShards);

	//Getters
	FORCEINLINE uint8 GetRank() { return m_Rank; }

protected:

	//Add a number of girls to the inventory
	UFUNCTION(BlueprintCallable)
		void AddGirls(int32 _NumberToAdd, bool _IsShard);

	//@TEMP (replace with image later) The text to display the rank of this widget
	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
		UTextBlock* m_RankText = nullptr;

	//The text to display the number of girls in inventory
	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
		UTextBlock* m_NumberOfGirlsText = nullptr;

	//The text to display the number of girls in shards
	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
		UTextBlock* m_NumberOfGirlsInShardsText = nullptr;

	//The rank for this inventory
	UPROPERTY(BlueprintReadWrite)
		uint8 m_Rank = 0;

	//The number of girls in the inventory for this rank
	UPROPERTY(BlueprintReadWrite)
		int32 m_NumberOfGirls = 0;

	//The number of girls in the shards inventory for this rank
	UPROPERTY(BlueprintReadWrite)
		int32 m_NumberOfGirlsInShards = 0;
private:
	void UpdateDisplayNumbers();
};
