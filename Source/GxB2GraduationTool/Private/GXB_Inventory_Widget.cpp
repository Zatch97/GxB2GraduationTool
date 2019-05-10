// Fill out your copyright notice in the Description page of Project Settings.


#include "GXB_Inventory_Widget.h"

#include "GXB_BaseLibrary.h"
#include "GXB_Girl.h"
#include "GXB_Girl_Widget.h"

#include "JsonUtilities.h"
#include "PanelWidget.h"

//Get the girl number in the inventory by index
int32 UGXB_Inventory_Widget::GetGirlCountInInventoryByIndexAndRank(int32 _GirlIndex, uint8 _Rank)
{
	for (int32 i = 0; i < m_GirlsList.Num(); i++)
	{
		if (m_GirlsList[i]->GetGirlId() == _GirlIndex)
		{
			return m_GirlsList[i]->GetTotalCountByRank(_Rank);
		}
	}

	return 0;
}

//Get the count of girls of the given faction excluding the indexes passed as parameter
int32 UGXB_Inventory_Widget::GetGirlCountInInventoryByFactionAndRankExcludingIndexes(EFaction _Faction, uint8 _Rank, TArray<int32> _RequestedGirlsIndexes)
{
	int32 result = 0;
	for (int32 i = 0; i < m_GirlsList.Num(); i++)
	{
		if (m_GirlsList[i]->GetFaction() == _Faction)
		{
			if (!_RequestedGirlsIndexes.Contains(m_GirlsList[i]->GetGirlId()))
			{
				result += m_GirlsList[i]->GetTotalCountByRank(_Rank);
			}
		}
	}

	return result;
}

//BeginPlay of UserWidget
void UGXB_Inventory_Widget::NativeConstruct()
{
	Super::NativeConstruct();

	InitializeGirlsList();
}

//Initialize the girls list from Save if it exists
void UGXB_Inventory_Widget::InitializeGirlsList()
{
	//@TODO Try get save game, initialize from there, if no save game, try to initialize from Json
	m_GirlsList = UGXB_BaseLibrary::ParseJsonFile(FPaths::ProjectContentDir() + "/Resources/All_Girls.json");
	if (m_GirlWidgetBP != nullptr)
	{
		for (int32 i = 0; i < m_GirlsList.Num(); i++)
		{
			UGXB_Girl_Widget* girlWidget = Cast<UGXB_Girl_Widget>(CreateWidget(this, m_GirlWidgetBP));
			girlWidget->InitializeWidget(m_GirlsList[i]);

			m_GirlsWidgetList.Add(girlWidget);
			m_BaseGirlsPanel->AddChild(girlWidget);
		}
	}

	UGXB_BaseLibrary::SaveToJson("", TArray<UGXB_Girl*>());
}