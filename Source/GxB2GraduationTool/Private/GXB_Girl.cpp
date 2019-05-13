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

//Get the total count of girls possessed by rank
int32 UGXB_Girl::GetTotalCountByRank(uint8 _Rank)
{
	int32 total = 0;
	if (m_CountInInventory.Contains(_Rank))
	{
		total += m_CountInInventory[_Rank];
	}
	if (m_CountInShards.Contains(_Rank))
	{
		total += m_CountInShards[_Rank];
	}

	return total;
}