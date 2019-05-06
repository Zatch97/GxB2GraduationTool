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
	//@TODO Try get save game, initialize from there, if no save game, try to initialize from xml maybe? Or maybe I'm gonna need to keep every girl in xml and just the number and index in Save? For now creating each one by hand to test
	if (TryParseJsonFile(FPaths::ProjectContentDir() + "/Resources/All_Girls.json"))
	{
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
	}
}

//Try to parse the Json file with all the girls
bool UGXB_Inventory_Widget::TryParseJsonFile(FString _JsonFilePath)
{
	FString JsonString; //Json converted to FString

	FFileHelper::LoadFileToString(JsonString, *_JsonFilePath);

	//Create a json object to store the information from the json string
	//The json reader is used to deserialize the json object later on
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
	TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(JsonString);

	//Deserialize the main object
	if (JsonObject.IsValid())
	{
		if (FJsonSerializer::Deserialize(JsonReader, JsonObject))
		{
			//The girls "object" that is retrieved from the given json file
			TArray<TSharedPtr<FJsonValue>> allGirlsObject = JsonObject->GetArrayField("AllGirls");
			for (int32 i = 0; i < allGirlsObject.Num(); i++)
			{
				ParseGirlObject(allGirlsObject[i]->AsObject());
			}

			return true;
		}
	}
	return false;
}

//Parse one girl object
void UGXB_Inventory_Widget::ParseGirlObject(TSharedPtr<FJsonObject> _GirlObject)
{
	UGXB_Girl* newGirl = NewObject<UGXB_Girl>();

	newGirl->SetGirlId(_GirlObject->GetIntegerField("GirlId"));
	newGirl->SetName(FText::FromString(_GirlObject->GetStringField("GirlName")));
	newGirl->SetFaction(static_cast<EFaction>(_GirlObject->GetIntegerField("Faction")));

	//Parsing possible ranks array
	TArray<uint8> possibleRanks;
	TArray<TSharedPtr<FJsonValue>> possibleRanksJson = _GirlObject->GetArrayField("PossibleRanks");
	for (int32 i = 0; i < possibleRanksJson.Num(); i++)
	{
		possibleRanks.Add(FMath::TruncToInt(possibleRanksJson[i]->AsNumber()));
	}
	newGirl->SetRanks(possibleRanks);

	newGirl->SetDefaultRank(_GirlObject->GetIntegerField("DefaultRank"));

	//Parsing image textures array
	TMap<uint8, UTexture2D*> imagesTextures;
	TArray<TSharedPtr<FJsonValue>> imagesTexturesJson = _GirlObject->GetArrayField("ImagesTextures");
	for (int32 i = 0; i < imagesTexturesJson.Num(); i++)
	{
		TSharedPtr<FJsonObject> imageObject = imagesTexturesJson[i]->AsObject();
		imagesTextures.Add(imageObject->GetIntegerField("RankKey"), UGXB_BaseLibrary::LoadTextureFromBase64(imageObject->GetStringField("ImageValue")));
	}
	newGirl->SetImagesTextures(imagesTextures);

	m_GirlsList.Add(newGirl);
}