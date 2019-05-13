// Fill out your copyright notice in the Description page of Project Settings.


#include "GXB_Girl_Widget.h"

#include "Image.h"

#include "GXB_BaseLibrary.h"
#include "GXB_Girl.h"

//Initialize this widget
void UGXB_Girl_Widget::InitializeWidget(UGXB_Girl* _Girl)
{
	m_Girl = _Girl;

	if (m_Girl != nullptr)
	{
		if (m_Image != nullptr)
		{
			UTexture2D* image = m_Girl->GetDefaultTexture();
			if (image != nullptr)
			{
				m_Image->SetBrushFromTexture(image);
				//FBase64
				//IImageWrapperModule
					//image->
			}
		}
	}
}