// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_HallMain.h"
#include "../../IdNGameInstance.h"
#include "ThreadManage.h"
#include "UObject/SimpleController.h"
#include "../../IdNMiscType.h"
#include "../Common/UI_Print.h"
#include "Kismet/GameplayStatics.h"
#include "Element/UI_CreatePanel.h"
#include "Element/UI_CharacterPanel.h"
#include "Protocol/HallProtocol.h"
#include "../../Core/Hall/HallPlayerState.h"


void UUI_HallMain::NativeConstruct()
{
	Super::NativeConstruct();

	UI_CreatePanel->SetWParent(this);
	UI_CharacterPanel->SetWParent(this);
	//创建客户端
	if (UIdNGameInstance* InGameInstance = GetGameInstance<UIdNGameInstance>())
	{
		if (InGameInstance->GetClient())
		{
			InGameInstance->GetClient()->NetManageMsgDelegate.BindUObject(this, &UUI_HallMain::LinkServerInfo);
			InGameInstance->GetClient()->Init(InGameInstance->GetGateStatus().GateServerAddrInfo.Addr);

			BindClientRcv();
		}
	}
}

void UUI_HallMain::NativeDestruct()
{
	Super::NativeDestruct();

	if (UIdNGameInstance* InGameInstance = GetGameInstance<UIdNGameInstance>())
	{
		if (InGameInstance->GetClient() && InGameInstance->GetClient()->GetController())
		{
			InGameInstance->GetClient()->GetController()->RecvDelegate.Remove(RecvDelegate);
		}
	}
}

void UUI_HallMain::PrintLog(const FString& InMsg)
{
	PrintLog(FText::FromString(InMsg));
}

void UUI_HallMain::PrintLog(const FText& InMsg)
{
	//播放动画
	UI_Print->PlayTextAnim();

	UI_Print->SetText(InMsg);
}

void UUI_HallMain::PlayCreateIn()
{
	UI_CreatePanel->PlayWidgetAnim(TEXT("CreateIn"));
}

void UUI_HallMain::PlayCreateOut()
{
	UI_CreatePanel->PlayWidgetAnim(TEXT("CreateOut"));
}

void UUI_HallMain::ResetCharacterPanel()
{
	UI_CharacterPanel->CreateCharacterButton();

	//生成最近的角色
	SpawnRecentlyCharacter();

	HighLightDefaultSelection();
}

void UUI_HallMain::SpawnRecentlyCharacter()
{
	if (AHallPlayerState* InState = GetPlayerState<AHallPlayerState>())
	{
		if (FIdNCharacterAppearance* InCAData = InState->GetRecentlyCharacter())
		{
			UI_CharacterPanel->SpawnCharacter(InCAData);
		}
	}
}

void UUI_HallMain::HighLightDefaultSelection()
{
	if (AHallPlayerState* InState = GetPlayerState<AHallPlayerState>())
	{
		if (FIdNCharacterAppearance* InCAData = InState->GetRecentlyCharacter())
		{
			UI_CharacterPanel->HighLightSelection(InCAData->SlotPosition);
		}
	}
}

void UUI_HallMain::BindClientRcv()
{
	if (UIdNGameInstance* InGameInstance = GetGameInstance<UIdNGameInstance>())
	{
		if (InGameInstance->GetClient() && InGameInstance->GetClient()->GetController())
		{
			RecvDelegate = InGameInstance->GetClient()->GetController()->RecvDelegate.AddLambda(
				[&](uint32 ProtocolNumber, FSimpleChannel* Channel)
				{
					this->RecvProtocol(ProtocolNumber, Channel);
				});
		}
		else
		{
			GThread::Get()->GetCoroutines().BindLambda(0.5f, [&]() { BindClientRcv(); });
		}
	}
	else
	{
		GThread::Get()->GetCoroutines().BindLambda(0.5f, [&]() { BindClientRcv(); });
	}
}

void UUI_HallMain::RecvProtocol(uint32 ProtocolNumber, FSimpleChannel* Channel)
{
	switch (ProtocolNumber)
	{
	case SP_CharacterAppearanceResponses:
	{
		FString CharacterJson;
		//获取角色json数据
		SIMPLE_PROTOCOLS_RECEIVE(SP_CharacterAppearanceResponses, CharacterJson);
		if (!CharacterJson.IsEmpty())
		{
			if (AHallPlayerState* InState = GetPlayerState<AHallPlayerState>())
			{
				NetDataAnalysis::StringToCharacterAppearances(CharacterJson,InState->GetCharacterAppearances());
				UI_CharacterPanel->InitCharacterButtons(InState->GetCharacterAppearances());
				//生成最近使用的角色
				SpawnRecentlyCharacter();

				//对应Slot高亮
				HighLightDefaultSelection();
			}
		}
		break;
	}
	}
}

void UUI_HallMain::LinkServerInfo(ESimpleNetErrorType InType, const FString& InMsg)
{
	if (InType == ESimpleNetErrorType::HAND_SHAKE_SUCCESS)
	{
		
		if (UIdNGameInstance* InGameInstance = GetGameInstance<UIdNGameInstance>())
		{
			//发送获取角色信息请求
			SEND_DATA(SP_CharacterAppearanceRequests, InGameInstance->GetUserData().ID);
		}
		

	}
}
