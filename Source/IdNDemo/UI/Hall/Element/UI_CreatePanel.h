// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../Core/UI_Base.h"
#include "UI_CreatePanel.generated.h"

class UEditableTextBox;
class UButton;

/**
 * 
 */
UCLASS()
class IDNDEMO_API UUI_CreatePanel : public UUI_Base
{
	GENERATED_BODY()
		UPROPERTY(meta = (BindWidget))
		UEditableTextBox* EditNameBox;

	UPROPERTY(meta = (BindWidget))
		UButton* CheckButton;

	UPROPERTY(meta = (BindWidget))
		UButton* CreateButton;

	UPROPERTY(meta = (BindWidget))
		UButton* CancelButton;


public:
	virtual void NativeConstruct();

	virtual void NativeDestruct();

protected:
	UFUNCTION()
		void CheckName();

	UFUNCTION()
		void CreateCharacter();

	UFUNCTION()
		void Cancel();
};
