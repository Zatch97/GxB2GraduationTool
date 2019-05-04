// Fill out your copyright notice in the Description page of Project Settings.


#include "GXB_Inventory_Widget.h"

#include "GXB_BaseLibrary.h"
#include "GXB_Girl.h"

//Get the girl number in the inventory by index
int32 UGXB_Inventory_Widget::GetGirlCountInInventoryByIndex(int32 _GirlIndex)
{
	for (int32 i = 0; i < m_GirlsList.Num(); i++)
	{
		if (m_GirlsList[i].f_Girl->GetGirlIndex() == _GirlIndex)
		{
			return m_GirlsList[i].GetTotalCount();
		}
	}

	return 0;
}

//Get the count of girls of the given faction excluding the indexes passed as parameter
int32 UGXB_Inventory_Widget::GetGirlCountInInventoryByFactionExcludingIndexes(EFaction _Faction, TArray<int32> _RequestedGirlsIndexes)
{
	int32 result = 0;
	for (int32 i = 0; i < m_GirlsList.Num(); i++)
	{
		if (m_GirlsList[i].f_Girl->GetFaction() == _Faction)
		{
			if (!_RequestedGirlsIndexes.Contains(m_GirlsList[i].f_Girl->GetGirlIndex()))
			{
				result += m_GirlsList[i].GetTotalCount();
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
	//@TODO Try get save game, initialize from there, if no save game, try to initialize from xml maybe? Or maybe I'm gonna need to keep every girl in xml and just the number and index in Save? For now creating each one by hand to test
}
