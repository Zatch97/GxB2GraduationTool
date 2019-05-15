// Fill out your copyright notice in the Description page of Project Settings.


#include "GXB_RankInventory_Widget.h"

#include "TextBlock.h"

//Initialize the number of girls in shards and in inventory for this rank
void UGXB_RankInventory_Widget::InitializeRankInventory(uint8 _Rank)
{
	m_Rank = _Rank;

	//RankInventoryWidgets starts Hidden
	//@TODO update visibility depending on if display needed or not
	SetVisibility(ESlateVisibility::Hidden);

	//@TEMP
	if (m_RankText != nullptr)
	{
		m_RankText->SetText(FText::FromString(FString::FromInt(m_Rank)));
	}
}

//Update the girls numbers
void UGXB_RankInventory_Widget::UpdateGirlsNumbers(int32 _NumberInInventory, int32 _NumberInShards)
{
	m_NumberOfGirls = _NumberInInventory;
	m_NumberOfGirlsInShards = _NumberInShards;

	//Update the numbers displayed
	UpdateDisplayNumbers();
}

//Add a girl to the inventory
void UGXB_RankInventory_Widget::AddGirls(int32 _NumberToAdd, bool _IsShard)
{
	if (_IsShard)
	{
		m_NumberOfGirlsInShards += _NumberToAdd;
		if (m_NumberOfGirlsInShards < 0)
		{
			m_NumberOfGirlsInShards = 0;
		}
	}
	else
	{
		m_NumberOfGirls += _NumberToAdd;
		if (m_NumberOfGirls < 0)
		{
			m_NumberOfGirls = 0;
		}
	}
	UpdateDisplayNumbers();
}

//Update the display texts with the girls numbers
void UGXB_RankInventory_Widget::UpdateDisplayNumbers()
{
	if (m_NumberOfGirlsText != nullptr)
	{
		m_NumberOfGirlsText->SetText(FText::FromString(FString::FromInt(m_NumberOfGirls)));
	}

	if (m_NumberOfGirlsInShardsText != nullptr)
	{
		m_NumberOfGirlsInShardsText->SetText(FText::FromString(FString::FromInt(m_NumberOfGirlsInShards)));
	}
}
