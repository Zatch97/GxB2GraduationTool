// Fill out your copyright notice in the Description page of Project Settings.


#include "GXB_Girl.h"

#include "GXB_BaseLibrary.h"


//Get the image texture corresponding to this girl by rank
UTexture2D* UGXB_Girl::GetImageTextureByRank(uint8 _Rank)
{
	if (m_ImageTextures.Contains(_Rank))
	{
		return m_ImageTextures[_Rank];
	}
	return nullptr;
}