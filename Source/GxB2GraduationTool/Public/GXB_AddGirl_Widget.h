// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GXB_AddGirl_Widget.generated.h"

class UEditableTextBox;
class UComboBoxString;
class UTexture2D;
class UGXB_Girl;
class UGXB_Inventory_Widget;

UCLASS()
class GXB2GRADUATIONTOOL_API UGXB_AddGirl_Widget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	//Initialize the references
	void InitializeReferences(UGXB_Inventory_Widget* _InventoryReference);

protected:

	//Begin Play of UserWidget
	virtual void NativeConstruct() override;

	//On save and reset button clicked
	UFUNCTION(BlueprintCallable)
		void OnSaveAndResetClicked();

	//Called when a rank button is clicked to add it to the possible ranks
	UFUNCTION(BlueprintCallable)
		void OnRankButtonClicked(uint8 _RankClicked);

	//Called when the image add button is clicked to add it to the images textures
	UFUNCTION(BlueprintCallable)
		void OnImageAddButtonClicked();

	//Girl to create
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UGXB_Girl* m_Girl = nullptr;

	//Class of Inventory bp
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<UUserWidget> m_InventoryBP = nullptr;

	//The text box to enter the Girls Name
	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
		UEditableTextBox* m_NameText = nullptr;

	//The combo box to choose the Girls faction
	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
		UComboBoxString* m_FactionComboBox = nullptr;

	//The text box to enter the Girls default rank
	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
		UEditableTextBox* m_DefaultRankText = nullptr;

	//The text box to enter the Girls rank for the image
	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
		UEditableTextBox* m_RankImageText = nullptr;

	//The text box to enter the Girls image link
	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
		UEditableTextBox* m_ImageLinkText = nullptr;

	//The ranks for this girl
	TArray<uint8> m_PossibleRanks;

	//Images textures by rank
	TMap<uint8, UTexture2D*> m_ImagesTextures;

	//Images textures by rank as base64 string
	TMap<uint8, FString> m_ImagesTextures64;

	//Inventory reference
	UGXB_Inventory_Widget* m_InventoryReference = nullptr;

};
