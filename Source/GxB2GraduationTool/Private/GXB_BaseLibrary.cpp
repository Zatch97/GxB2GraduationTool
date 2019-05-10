// Fill out your copyright notice in the Description page of Project Settings.


#include "GXB_BaseLibrary.h"

#include "GXB_Girl.h"

#include "Engine/Texture2D.h"
#include "Base64.h"
#include "ModuleManager.h"
#include "IImageWrapper.h"
#include "IImageWrapperModule.h"
#include "FileHelper.h"
#include "JsonUtilities.h"

//TESTS OF BASE64 CONVERSION FROM FILEPATH

//@TODO USELESS HERE, for loading image to base64 and saving it to a file, will be useful for creating all girls, but not right now
/*
FString fileName = FPaths::ProjectContentDir() + "/Resources/Annie_6.png";
FString fileNameTest = FPaths::ProjectContentDir() + "/Resources/test.txt";

TArray<uint8> bufferData;
//FFileHelper::LoadFileToArray(bufferData, *fileName);

FString base64String = FBase64::Encode(bufferData);

//FFileHelper::SaveStringToFile(base64String, *fileNameTest);

FFileHelper::LoadFileToString(base64String, *fileNameTest);
*/
//END USELESS HERE


//Load a texture from a Filepath
UTexture2D* UGXB_BaseLibrary::LoadTextureFromFile(FString _Filepath)
{
	TArray<uint8> bufferData;
	FFileHelper::LoadFileToArray(bufferData, *_Filepath);

	return LoadTextureFromBuffer(bufferData);
}

//Load a texture from a Base64 String
UTexture2D* UGXB_BaseLibrary::LoadTextureFromBase64(FString _Base64String)
{
	//Decode the base64string
	TArray<uint8> byteArrayDecoded;
	FBase64::Decode(_Base64String, byteArrayDecoded);

	return LoadTextureFromBuffer(byteArrayDecoded);
}

//Load a texture from a Byte buffer
UTexture2D* UGXB_BaseLibrary::LoadTextureFromBuffer(TArray<uint8> _BufferData)
{
	UTexture2D* loadedTexture = nullptr;

	//Load the image wrapper
	IImageWrapperModule& imageWrapperModule = FModuleManager::LoadModuleChecked<IImageWrapperModule>(FName("ImageWrapper"));
	TSharedPtr<IImageWrapper> imageWrapper = imageWrapperModule.CreateImageWrapper(EImageFormat::PNG);

	if (imageWrapper.IsValid())
	{
		if (imageWrapper->SetCompressed(_BufferData.GetData(), _BufferData.Num()))
		{
			const TArray<uint8>* uncompressedBGRA = nullptr;
			if (imageWrapper->GetRaw(ERGBFormat::BGRA, 8, uncompressedBGRA))
			{
				loadedTexture = UTexture2D::CreateTransient(imageWrapper->GetWidth(), imageWrapper->GetHeight(), PF_B8G8R8A8);

				//Copy texture data
				void* textureData = loadedTexture->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_WRITE);
				FMemory::Memcpy(textureData, uncompressedBGRA->GetData(), uncompressedBGRA->Num());
				loadedTexture->PlatformData->Mips[0].BulkData.Unlock();

				//Update
				loadedTexture->UpdateResource();
			}
		}
	}

	return loadedTexture;

}

//Try to parse the Json file with all the girls
TArray<UGXB_Girl*> UGXB_BaseLibrary::ParseJsonFile(FString _JsonFilePath)
{
	TArray<UGXB_Girl*> allGirls;

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
				allGirls.Add(UGXB_BaseLibrary::ParseGirlObject(allGirlsObject[i]->AsObject()));
			}
		}
	}

	return allGirls;
}

//Parse one girl object
UGXB_Girl* UGXB_BaseLibrary::ParseGirlObject(TSharedPtr<FJsonObject> _GirlObject)
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

	return newGirl;
}

//Save the girls in array to a Json file
bool UGXB_BaseLibrary::SaveToJson(FString _Filepath, TArray<UGXB_Girl*> _Girls)
{
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);

	JsonObject->SetStringField("Name", "Super Sword");
	JsonObject->SetNumberField("Damage", 15);
	JsonObject->SetNumberField("Weight", 3);

	FString OutputString;
	TSharedRef< TJsonWriter<TCHAR, TPrettyJsonPrintPolicy<TCHAR>> > Writer = TJsonWriterFactory< TCHAR, TPrettyJsonPrintPolicy<TCHAR> >::Create(&OutputString);
	FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer);

	FString fileNameTest = FPaths::ProjectContentDir() + "/Resources/test.json";
	FFileHelper::SaveStringToFile(OutputString, *fileNameTest);

	return false;
}
