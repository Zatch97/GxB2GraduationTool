// Fill out your copyright notice in the Description page of Project Settings.


#include "GXB_Girl_Widget.h"

#include "Image.h"

#include "GXB_BaseLibrary.h"
#include "GXB_Girl.h"


//BeginPlay of UserWidget
void UGXB_Girl_Widget::NativeConstruct()
{
	Super::NativeConstruct();

	if (m_Image != nullptr)
	{
		m_Image->SetBrushFromTexture(m_Girl->GetImageTexture());
	}
}
