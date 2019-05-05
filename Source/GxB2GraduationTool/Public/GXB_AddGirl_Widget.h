// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GXB_AddGirl_Widget.generated.h"

class UEditableTextBox;
class UComboBoxString;
class UGXB_Girl;

UCLASS()
class GXB2GRADUATIONTOOL_API UGXB_AddGirl_Widget : public UUserWidget
{
	GENERATED_BODY()
	

protected:

	//Begin play of UserWidget
	virtual void NativeConstruct() override;

	//On validate button clicked
	UFUNCTION(BlueprintCallable)
		void OnValidateClicked();

	//Called when a rank button is clicked to add it to the possible ranks
	UFUNCTION(BlueprintCallable)
		void OnRankButtonClicked(uint8 _RankClicked);

	//Girl to create
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UGXB_Girl* m_Girl = nullptr;

	//The text box to enter the Girls Name
	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
		UEditableTextBox* m_NameText = nullptr;

	//The combo box to choose the Girls faction
	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
		UComboBoxString* m_FactionComboBox = nullptr;

	//The text box to enter the Girls rank
	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
		UEditableTextBox* m_RankText = nullptr;

	//The ranks for this girl
	TArray<uint8> m_PossibleRanks;
};
