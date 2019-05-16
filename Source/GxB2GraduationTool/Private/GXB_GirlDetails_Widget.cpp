// Fill out your copyright notice in the Description page of Project Settings.


#include "GXB_GirlDetails_Widget.h"

#include "GXB_Girl.h"
#include "GXB_RankInventory_Widget.h"

#include "PanelWidget.h"

//Change the current girl and update the details
void UGXB_GirlDetails_Widget::ChangeGirl(UGXB_Girl* _NewGirl)
{
	if (m_CurrentGirl != _NewGirl)
	{
		m_CurrentGirl = _NewGirl;
		UpdateDetails();
	}
}

//Begin Play of UserWidget
void UGXB_GirlDetails_Widget::NativeConstruct()
{
	Super::NativeConstruct();

	InitializeRankInventoryWidgets();
}

//Initialize all the rank inventory widgets with all the ranks possible
void UGXB_GirlDetails_Widget::InitializeRankInventoryWidgets()
{
	if (m_RankInventoryWidgetBP != nullptr && m_RankInventoryPanel != nullptr)
	{
		//@TODO change the way we keep min and max rank, maybe keep them from created girls, or somewhere in settings to use in addgirl widget also
		for (int32 i = 3; i <= 10; i++)
		{
			UGXB_RankInventory_Widget* newRankInventory = Cast<UGXB_RankInventory_Widget>(CreateWidget(this, m_RankInventoryWidgetBP));
			newRankInventory->InitializeRankInventory(i);

			m_RankInventoryPanel->AddChild(newRankInventory);

			m_RankInventoryWidgets.Add(newRankInventory);
		}
	}
}

//Update the displayed details
void UGXB_GirlDetails_Widget::UpdateDetails()
{
	for (int32 i = 0; i < m_RankInventoryWidgets.Num(); i++)
	{
		uint8 currentRank = m_RankInventoryWidgets[i]->GetRank();
		if (m_CurrentGirl->IsRank(currentRank))
		{
			m_RankInventoryWidgets[i]->UpdateGirlsNumbers(m_CurrentGirl->GetCountInInventoryByRank(currentRank), m_CurrentGirl->GetCountInShardsByRank(currentRank));
		}
		m_RankInventoryWidgets[i]->SetVisibility(ESlateVisibility::Visible);
	}
}
