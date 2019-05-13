// Fill out your copyright notice in the Description page of Project Settings.


#include "GXB_AddGirl_Widget.h"

#include "GXB_Girl.h"
#include "GXB_BaseLibrary.h"
#include "GXB_Inventory_Widget.h"

#include "EditableTextBox.h"
#include "ComboBoxString.h"
#include "FileHelper.h"
#include "WidgetBlueprintLibrary.h"


//Initialize the references
void UGXB_AddGirl_Widget::InitializeReferences(UGXB_Inventory_Widget* _InventoryReference)
{
	m_InventoryReference = _InventoryReference;
}

//Begin Play of UserWidget
void UGXB_AddGirl_Widget::NativeConstruct()
{
	Super::NativeConstruct();


}

//On save and reset button clicked
void UGXB_AddGirl_Widget::OnSaveAndResetClicked()
{
	//Update the values of the current girl object
	if (m_NameText != nullptr && m_FactionComboBox != nullptr && m_DefaultRankText != nullptr)
	{
		m_Girl = NewObject<UGXB_Girl>();

		m_Girl->SetName(m_NameText->GetText());
		m_NameText->SetText(FText());

		m_Girl->SetFaction(EFaction(m_FactionComboBox->GetSelectedIndex()));
		m_FactionComboBox->SetSelectedIndex(0);

		m_Girl->SetRanks(m_PossibleRanks);
		m_PossibleRanks.Empty();

		m_Girl->SetDefaultRank(FCString::Atoi(*(m_DefaultRankText->GetText().ToString())));
		m_DefaultRankText->SetText(FText());

		m_Girl->SetImagesTextures(m_ImagesTextures);
		m_ImagesTextures.Empty();
		m_Girl->SetImagesTextures64(m_ImagesTextures64);
		m_ImagesTextures64.Empty();

		if (m_InventoryReference != nullptr)
		{
			m_InventoryReference->AddGirlToInventory(m_Girl);
		}
	}
}

//Called when a rank button is clicked to add it to the possible ranks
void UGXB_AddGirl_Widget::OnRankButtonClicked(uint8 _RankClicked)
{
	if (m_PossibleRanks.Contains(_RankClicked))
	{
		m_PossibleRanks.Remove(_RankClicked);
	}
	else
	{
		//Add change of style
		m_PossibleRanks.Add(_RankClicked);
	}
}

//Called when the image add button is clicked to add it to the images textures
void UGXB_AddGirl_Widget::OnImageAddButtonClicked()
{
	if (m_RankImageText != nullptr && m_ImageLinkText != nullptr)
	{
		if (m_RankImageText->GetText().IsNumeric())
		{
			uint8 rank = FCString::Atoi(*(m_RankImageText->GetText().ToString()));
			FString imagepath = m_ImageLinkText->GetText().ToString();
			UTexture2D* imageTexture = UGXB_BaseLibrary::LoadTextureFromFile(imagepath);
			FString base64String = UGXB_BaseLibrary::MakeBase64FromFile(imagepath);
			if (imageTexture != nullptr)
			{
				m_ImagesTextures.Add(rank, imageTexture);
				m_ImagesTextures64.Add(rank, base64String);
			}
			m_RankImageText->SetText(FText());
			m_ImageLinkText->SetText(FText());
		}
	}
}

