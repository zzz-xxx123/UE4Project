// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Core/UI_Base.h"
#include "SimpleNetChannelType.h"
#include "NetGameType.h"
#include "UI_LoginMain.generated.h"

class UUI_Login;
class UTextBlock;
struct FIdNGateStatus;
class UUI_Print;
class UUI_Register;
/**
 * 
 */
UCLASS()
class IDNDEMO_API UUI_LoginMain : public UUI_Base
{
	GENERATED_BODY()
		UPROPERTY(meta = (BindWidget))
		UUserWidget* UI_LinkWidget;

	UPROPERTY(meta = (BindWidget))
		UUI_Login* UI_LoginWidget;

	UPROPERTY(meta = (BindWidget))
		UUI_Print* UI_PrintBlock;

	UPROPERTY(meta = (BindWidget))
		UUI_Register* UI_Register;

public:
	virtual void NativeConstruct();

	virtual void NativeDestruct();
public:
	UFUNCTION()
		void SignIn(FString& InAccount,FString& InPassword);

	UFUNCTION()
		void SignUp();
		void SignUp(FString InRegisterInfo);

	void PrintLog(const FString& InMsg);
	void PrintLog(const FText& InMsg);
protected:
	void BindClientRecv();

	virtual void RecvProtocol(uint32 ProtocolNumber, FSimpleChannel* Channel)override;

	UFUNCTION()
	void LinkServerInfo(ESimpleNetErrorType InType, const FString& InMsg);
private:
	FDelegateHandle RecvDelegate;

};
