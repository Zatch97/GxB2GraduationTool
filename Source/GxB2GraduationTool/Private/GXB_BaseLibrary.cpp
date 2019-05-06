// Fill out your copyright notice in the Description page of Project Settings.


#include "GXB_BaseLibrary.h"

#include "Engine/Texture2D.h"
#include "Base64.h"
#include "ModuleManager.h"
#include "IImageWrapper.h"
#include "IImageWrapperModule.h"
#include "FileHelper.h"

UTexture2D* UGXB_BaseLibrary::LoadTextureFromBase64(FString _Base64String)
{
	UTexture2D* loadedTexture = nullptr;


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



	//Decode the base64string
	TArray<uint8> byteArrayDecoded;
	FBase64::Decode(_Base64String, byteArrayDecoded);

	//Load the image wrapper
	IImageWrapperModule& imageWrapperModule = FModuleManager::LoadModuleChecked<IImageWrapperModule>(FName("ImageWrapper"));
	TSharedPtr<IImageWrapper> imageWrapper = imageWrapperModule.CreateImageWrapper(EImageFormat::PNG);

	if (imageWrapper.IsValid())
	{
		if (imageWrapper->SetCompressed(byteArrayDecoded.GetData(), byteArrayDecoded.Num()))
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
