// Fill out your copyright notice in the Description page of Project Settings.


#include "GXB_Recipe_Widget.h"

#include "GXB_BaseLibrary.h"
#include "GXB_Inventory_Widget.h"


//Check if this recipe is possible with the current inventory
bool UGXB_Recipe_Widget::IsRecipePossible()
{
	if (m_InventoryReference != nullptr)
	{
		//Check the requested girls with index
		for (int32 i = 0; i < m_GirlRequisites.Num(); i++)
		{
			if (m_GirlRequisites[i].f_NumberNeeded > m_InventoryReference->GetGirlCountInInventoryByIndexAndRank(m_GirlRequisites[i].f_GirlId, m_GirlRequisites[i].f_Rank))
			{
				return false;
			}
		}

		//Check the requested girls by faction
		for (int32 i = 0; i < m_FactionGirlRequisites.Num(); i++)
		{
			if (m_FactionGirlRequisites[i].f_NumberNeeded > m_InventoryReference->GetGirlCountInInventoryByFactionAndRankExcludingIndexes(m_FactionGirlRequisites[i].f_Faction, m_FactionGirlRequisites[i].f_Rank, GetRequestedGirlsIndexes()))
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
		girlsIndexes.Add(m_GirlRequisites[i].f_GirlId);
	}

	return girlsIndexes;
}
