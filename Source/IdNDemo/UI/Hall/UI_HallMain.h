// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Core/UI_Base.h"
#include "SimpleNetChannelType.h"
#include "UI_HallMain.generated.h"

class UUI_Print;
class UUI_CharacterPanel;
class UUI_CreatePanel;
/**
 * 
 */
UCLASS()
class IDNDEMO_API UUI_HallMain : public UUI_Base
{
	GENERATED_BODY()
		UPROPERTY(meta = (BindWidget))
		UUI_Print* UI_Print;

	UPROPERTY(meta = (BindWidget))
		UUI_CharacterPanel* UI_CharacterPanel;

	UPROPERTY(meta = (BindWidget))
		UUI_CreatePanel* UI_CreatePanel;

public:
	virtual void NativeConstruct();

	virtual void NativeDestruct();
public:

	void PrintLog(const FString& InMsg);
	void PrintLog(const FText& InMsg);

	void PlayCreateIn();
	void PlayCreateOut();

	void ResetCharacterPanel();

	void SpawnRecentlyCharacter();
	void HighLightDefaultSelection();
protected:

	void BindClientRcv();

	virtual void RecvProtocol(uint32 ProtocolNumber, FSimpleChannel* Channel);

	UFUNCTION()
	void LinkServerInfo(ESimpleNetErrorType InType, const FString& InMsg);
private:
	FDelegateHandle RecvDelegate;
};
