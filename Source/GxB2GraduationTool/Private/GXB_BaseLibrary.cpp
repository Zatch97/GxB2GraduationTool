// Fill out your copyright notice in the Description page of Project Settings.


#include "GXB_BaseLibrary.h"

#include "GXB_Girl.h"

#include "Engine/Texture2D.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Base64.h"
#include "ImageUtils.h"
#include "ModuleManager.h"
#include "IImageWrapper.h"
#include "IImageWrapperModule.h"
#include "FileHelper.h"
#include "JsonUtilities.h"

#include "HighResScreenshot.h"

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
	/* @USELESS there's a UE function doing this
	TArray<uint8> bufferData;
	FFileHelper::LoadFileToArray(bufferData, *_Filepath);

	return LoadTextureFromBuffer(bufferData);*/
	return FImageUtils::ImportFileAsTexture2D(_Filepath);
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

	return FImageUtils::ImportBufferAsTexture2D(_BufferData);

	/* @USELESS there's a UE function doing this
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
	return loadedTexture;*/
}

//Make a Base64 String from file
FString UGXB_BaseLibrary::MakeBase64FromFile(FString _Filepath)
{
	TArray<uint8> bufferData;

	FFileHelper::LoadFileToArray(bufferData, *_Filepath);

	return FBase64::Encode(bufferData);
}

/*
@INFO it's almost impossible to make a png from a UTexture2D so I'm gonna save my base64 on png load

//Make a Byte buffer from Texture
TArray<uint8> UGXB_BaseLibrary::MakeBufferFromTexture(UTexture2D* _Texture)
{
	UTextureRenderTarget2D *render = new UTextureRenderTarget2D(,);
	
	FImageUtils::CompressImageArray(_Texture, );
	FImageUtils::ExportRenderTarget2DAsPNG
	
		
	//Load the image wrapper
	IImageWrapperModule& imageWrapperModule = FModuleManager::LoadModuleChecked<IImageWrapperModule>(FName("ImageWrapper"));
	TSharedPtr<IImageWrapper> PNGImageWrapper = imageWrapperModule.CreateImageWrapper(EImageFormat::PNG);

	const FColor* colorArray = static_cast<FColor*>(_Texture->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_WRITE));
	const TArray<uint8> uncompressedBGRA =

	//FMemory::Memcpy(uncompressedBGRA, uncompressedBGRA, textureData.GetBulkDataSize());

	PNGImageWrapper->SetRaw(uncompressedBGRA->GetData(), uncompressedBGRA->Num(), _Texture->GetSurfaceWidth(), _Texture->GetSurfaceWidth(), ERGBFormat::BGRA, 8);
	_Texture->PlatformData->Mips[0].BulkData.Unlock();

	const TArray<uint8>& PNGData = PNGImageWrapper->GetCompressed(100);

	return PNGData;

	
	if (PNGImageWrapper.IsValid())
	{
		if (PNGImageWrapper->SetCompressed(_BufferData.GetData(), _BufferData.Num()))
		{

			if (PNGImageWrapper->GetRaw(ERGBFormat::BGRA, 8, uncompressedBGRA))
			{
				loadedTexture = UTexture2D::CreateTransient(PNGImageWrapper->GetWidth(), PNGImageWrapper->GetHeight(), PF_B8G8R8A8);

				//Copy texture data
				void* textureData = loadedTexture->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_WRITE);
				FMemory::Memcpy(textureData, uncompressedBGRA->GetData(), uncompressedBGRA->Num());
				loadedTexture->PlatformData->Mips[0].BulkData.Unlock();

				//Update
				loadedTexture->UpdateResource();
			}
		}
	}
}

//Make a Base64 String from Texture
FString UGXB_BaseLibrary::MakeBase64FromTexture(UTexture2D* _Texture)
{
	return FBase64::Encode(UGXB_BaseLibrary::MakeBufferFromTexture(_Texture));
}*/

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
		int rankKey = imageObject->GetIntegerField("RankKey");
		FString base64String = imageObject->GetStringField("ImageValue");

		imagesTextures.Add(rankKey, UGXB_BaseLibrary::LoadTextureFromBase64(base64String));
	}
	newGirl->SetImagesTextures(imagesTextures);

	return newGirl;
}

//Save the girls in array to a Json file
bool UGXB_BaseLibrary::SaveToJson(FString _Filepath, TArray<UGXB_Girl*> _Girls)
{
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);

	TArray<TSharedPtr<FJsonValue>> allGirlsObject;
	for (UGXB_Girl* girl : _Girls)
	{
		//Make new girl object in JsonObject
		TSharedPtr<FJsonObject> girlJsonObject = MakeShareable(new FJsonObject);
		girlJsonObject->SetNumberField("GirlId", girl->GetGirlId());
		girlJsonObject->SetStringField("GirlName", girl->GetGirlName().ToString());
		girlJsonObject->SetNumberField("Faction", static_cast<int32>(girl->GetFaction()));

		//Serializing possible ranks array
		TArray<uint8> possibleRanks = girl->GetPossibleRanks();
		TArray<TSharedPtr<FJsonValue>> possibleRanksJson;
		for (int32 i = 0; i < possibleRanks.Num(); i++)
		{
			possibleRanksJson.Add(MakeShareable(new FJsonValueNumber(possibleRanks[i])));
		}
		girlJsonObject->SetArrayField("PossibleRanks", possibleRanksJson);


		girlJsonObject->SetNumberField("DefaultRank", girl->GetDefaultRank());

		//Serializing textures array as Base64
		TMap<uint8, FString> imagesTextures64 = girl->GetImagesTextures64();
		TArray<TSharedPtr<FJsonValue>> imagesTexturesJson;
		for (const TPair<uint8, FString> pair : imagesTextures64)
		{
			TSharedPtr<FJsonObject> imageObject = MakeShareable(new FJsonObject);

			imageObject->SetNumberField("RankKey", pair.Key);
			imageObject->SetStringField("ImageValue", pair.Value);
			
			imagesTexturesJson.Add(MakeShareable(new FJsonValueObject(imageObject)));
		}
		girlJsonObject->SetArrayField("ImagesTextures", imagesTexturesJson);

		//Convert to JsonValue and add to array
		TSharedPtr<FJsonValue> girlJsonValue = MakeShareable(new FJsonValueObject(girlJsonObject));
		allGirlsObject.Add(girlJsonValue);
	}

	JsonObject->SetArrayField("AllGirls", allGirlsObject);

	FString OutputString;
	TSharedRef< TJsonWriter<TCHAR, TPrettyJsonPrintPolicy<TCHAR>> > Writer = TJsonWriterFactory< TCHAR, TPrettyJsonPrintPolicy<TCHAR> >::Create(&OutputString);
	FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer);

	FFileHelper::SaveStringToFile(OutputString, *_Filepath);

	return false;
}
