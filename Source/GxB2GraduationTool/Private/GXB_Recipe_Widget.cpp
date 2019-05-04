// Fill out your copyright notice in the Description page of Project Settings.


#include "GXB_Recipe_Widget.h"

#include "GXB_BaseLibrary.h"
#include "GXB_Inventory_Widget.h"


//Check if this recipe is possible with the current inventory
bool UGXB_Recipe_Widget::IsRecipePossible()
{
	if (m_InventoryReference != nullptr)
	{
		for (int32 i = 0; i < m_GirlRequisites.Num(); i++)
		{
			if (m_GirlRequisites[i].f_NumberNeeded > m_InventoryReference->GetGirlCountInInventoryByIndex(m_GirlRequisites[i].f_GirlIndex))
			{
				return false;
			}
		}

		for (int32 i = 0; i < m_FactionGirlRequisites.Num(); i++)
		{
			if (m_FactionGirlRequisites[i].f_NumberNeeded > m_InventoryReference->GetGirlCountInInventoryByFactionExcludingIndexes(m_FactionGirlRequisites[i].f_Faction, GetRequestedGirlsIndexes()))
			{
				return false;
			}
		}

		return true;
	}

	return false;
}

//Get the indexes of the Girls Requested
TArray<int32> UGXB_Recipe_Widget::GetRequestedGirlsIndexes()
{
	TArray<int32> girlsIndexes;

	for (int32 i = 0; i < m_GirlRequisites.Num(); i++)
	{
		girlsIndexes.Add(m_GirlRequisites[i].f_GirlIndex);
	}

	return girlsIndexes;
}
