// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GXB_Girl_Widget.generated.h"

class UImage;
class UGXB_Girl;
enum class EFaction : uint8;


UCLASS()
class GXB2GRADUATIONTOOL_API UGXB_Girl_Widget : public UUserWidget
{
	GENERATED_BODY()


public:

	//Initialize this widget
	UFUNCTION(BlueprintCallable)
		void InitializeWidget(UGXB_Girl* _Girl);

protected:

	//The girl represented by this widget
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UGXB_Girl* m_Girl = nullptr;

	//The image of this girl (@TODO maybe convert to base64 image so that I can save it in xml? Maybe not needed, we'll see)
	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
		UImage* m_Image = nullptr;


};
