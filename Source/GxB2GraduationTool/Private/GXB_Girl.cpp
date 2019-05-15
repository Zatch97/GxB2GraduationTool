// Fill out your copyright notice in the Description page of Project Settings.


#include "GXB_Girl.h"

#include "GXB_BaseLibrary.h"


//Get the image texture corresponding to this girl by rank (default texture if no texture exists, @TODO switch for 4-5 stars texture and for 6-7-8-9 textures too)
UTexture2D* UGXB_Girl::GetImageTextureByRank(uint8 _Rank)
{
	if (m_ImagesTextures.Contains(_Rank))
	{
		return m_ImagesTextures[_Rank];
	}
	return nullptr;
}

//Get Count in inventory by rank
int32 UGXB_Girl::GetCountInInventoryByRank(uint8 _Rank)
{
	if (m_CountInInventory.Contains(_Rank))
	{
		return m_CountInInventory[_Rank];
	}

	return 0;
}

//Get Count in shards by rank
int32 UGXB_Girl::GetCountInShardsByRank(uint8 _Rank)
{
	if (m_CountInShards.Contains(_Rank))
	{
		return m_CountInShards[_Rank];
	}

	return 0;
}

//Get the total count of girls possessed by rank
int32 UGXB_Girl::GetTotalCountByRank(uint8 _Rank)
{
	return GetCountInInventoryByRank(_Rank) + GetCountInShardsByRank(_Rank);
}


//True if the girl has the given rank in it's possible ranks
bool UGXB_Girl::IsRank(uint8 _Rank)
{
	return m_PossibleRanks.Contains(_Rank);
}
