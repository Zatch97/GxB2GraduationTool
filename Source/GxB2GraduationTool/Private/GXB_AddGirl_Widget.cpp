// Fill out your copyright notice in the Description page of Project Settings.


#include "GXB_AddGirl_Widget.h"

#include "GXB_Girl.h"

//Begin play of UserWidget
void UGXB_AddGirl_Widget::NativeConstruct()
{
	Super::NativeConstruct();

	m_Girl = NewObject<UGXB_Girl>();
}

//On validate button clicked
void UGXB_AddGirl_Widget::OnValidateClicked()
{
	//m_Girl->SetName(m_NameText->GetText());

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
