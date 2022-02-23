// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../Core/UI_Base.h"
#include "NetGameType.h"
#include "UI_CharacterButton.generated.h"

class UButton;
class UImage;
class UVerticalBox;
class UTextBlock;

/**
 * 
 */
UCLASS()
class IDNDEMO_API UUI_CharacterButton : public UUI_Base
{
	GENERATED_BODY()
		UPROPERTY(meta = (BindWidget))
		UButton* CharacterButton;
	UPROPERTY(meta = (BindWidget))
		UImage* CreateShowIcon;
	UPROPERTY(meta = (BindWidget))
		UVerticalBox* CharacterInfo;
	UPROPERTY(meta = (BindWidget))
		UImage* CharacterIcon;
	UPROPERTY(meta = (BindWidget))
		UTextBlock* CharacterName;
	UPROPERTY(meta = (BindWidget))
		UTextBlock* Date;

	UPROPERTY(EditDefaultsOnly, Category = UI)
	FLinearColor HighLightColor;

public:
	virtual void NativeConstruct();

	virtual void NativeDestruct();

	void SetSlotPostion(const int32 InNewPos);

	FORCEINLINE int32 GetSlotPostion() { return SlotPosition; }

	void InitCharacterButton(const FIdNCharacterAppearance& InCA);

	void SetHighLight(bool bHighLight);

protected:
	UFUNCTION()
	void ClickedCharacter();

	int32 SlotPosition;

	FLinearColor DefaultColor;
};
