// Fill out your copyright notice in the Description page of Project Settings.


#include "GXB_AddGirl_Widget.h"

#include "GXB_Girl.h"
#include "GXB_BaseLibrary.h"

#include "EditableTextBox.h"
#include "ComboBoxString.h"
#include "FileHelper.h"

//Begin play of UserWidget
void UGXB_AddGirl_Widget::NativeConstruct()
{
	Super::NativeConstruct();

	m_Girl = NewObject<UGXB_Girl>();


}

//On save and reset button clicked
void UGXB_AddGirl_Widget::OnSaveAndResetClicked()
{
	//Update the values of the current girl object
	if (m_NameText != nullptr && m_FactionComboBox != nullptr && m_DefaultRankText != nullptr)
	{
		m_Girl->SetName(m_NameText->GetText());
		m_Girl->SetFaction(EFaction(m_FactionComboBox->GetSelectedIndex()));
		m_Girl->SetRanks(m_PossibleRanks);
		m_Girl->SetDefaultRank(FCString::Atoi(*(m_DefaultRankText->GetText().ToString())));
		m_Girl->SetImagesTextures(m_ImageTextures);
		
		//@TODO Save the girl to the Json now? Or Save in temporary array (inventory) and rewrite the Json on button click with every girls in the inventory?
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
			UTexture2D* imageTexture = UGXB_BaseLibrary::LoadTextureFromFile(m_ImageLinkText->GetText().ToString());
			if (imageTexture != nullptr)
			{
				m_ImageTextures.Add(rank, imageTexture);
			}
		}
	}
}