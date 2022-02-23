// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_LoginMain.h"

#include "ThreadManage.h"
#include "UObject/SimpleController.h"

#include "UI_Login.h"
#include <Protocol/LoginProtocol.h>
#include <SimpleProtocolsDefinition.h>
#include "../../IdNMiscType.h"
#include "../Common/UI_Print.h"
#include "Kismet/GameplayStatics.h"
#include "UI_Register.h"

#define LOCTEXT_NAMESPACE "UUI_LoginMain"
void UUI_LoginMain::NativeConstruct()
{
	Super::NativeConstruct();

	UI_LoginWidget->SetWParent(this);
	UI_Register->SetWParent(this);


	//创建客户端
	if (UIdNGameInstance* InGameInstance = GetGameInstance<UIdNGameInstance>())
	{
		InGameInstance->CreateClient();
		if (InGameInstance->GetClient())
		{
			InGameInstance->GetClient()->NetManageMsgDelegate.BindUObject(this, &UUI_LoginMain::LinkServerInfo);
			
			InGameInstance->LinkServer();
			
			BindClientRecv();
		}
	}
	//读取账号
	if (!UI_LoginWidget->DecryptionFromLocal(FPaths::ProjectDir() / TEXT("User")))
	{
		PrintLog(TEXT("No account detected."));
	}
	
	
}

void UUI_LoginMain::NativeDestruct()
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

void UUI_LoginMain::SignIn(FString& InAccount, FString& InPassword)
{
	SEND_DATA(SP_LoginRequests,InAccount,InPassword);
}

void UUI_LoginMain::SignUp()
{
	UI_Register->RegisterIn();
}

void UUI_LoginMain::SignUp(FString InRegisterInfo)
{
	SEND_DATA(SP_RegisterRequests, InRegisterInfo);
}

void UUI_LoginMain::PrintLog(const FString& InMsg)
{
	PrintLog(FText::FromString(InMsg));
}

void UUI_LoginMain::PrintLog(const FText& InMsg)
{
	UI_PrintBlock->SetText(InMsg);

	//播放动画
	
	UI_PrintBlock->PlayTextAnim();

}

void UUI_LoginMain::BindClientRecv()
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
			GThread::Get()->GetCoroutines().BindLambda(0.5f,
				[&]()
				{
					BindClientRecv();
				});
		}
	}
	else
	{
		GThread::Get()->GetCoroutines().BindLambda(0.5f,
			[&]()
			{
				BindClientRecv();
			});
	}
}

void UUI_LoginMain::RecvProtocol(uint32 ProtocolNumber, FSimpleChannel* Channel)
{
	switch (ProtocolNumber)
	{
		case SP_LoginResponses:
		{
			FString String;
			ELoginType Type = ELoginType::LOGIN_ACCOUNT_WRONG;
			FIdNGateStatus GateStatus;
			//获取客户端发送数据
			SIMPLE_PROTOCOLS_RECEIVE(SP_LoginResponses, Type, String, GateStatus);

			switch (Type)
			{
			case LOGIN_DBSERVER_ERROR:
			
				PrintLog(TEXT("Server error"));
				break;
			
			case LOGIN_SUCCESS:
			{
				
				if (UIdNGameInstance* InGameInstance = GetGameInstance<UIdNGameInstance>())
				{
					NetDataAnalysis::StringToUserData(String, InGameInstance->GetUserData());
					if (GateStatus.GateConnetionNum == INDEX_NONE)
					{
						//排队等待
						PrintLog(TEXT("Server is full, We will try to link again."));
					}
					else
					{
						InGameInstance->GetGateStatus() = GateStatus;


						if (!UI_LoginWidget->EncryptionToLocal(FPaths::ProjectDir() / TEXT("User")))
						{
							PrintLog(TEXT("Storage password failed."));
						}
						else
						{
							PrintLog(TEXT("LOGIN SUCCESS"));
						}
						PlayWidgetAnim(TEXT("LoginOut"));

						//切换服务器
						if (InGameInstance->GetClient() && InGameInstance->GetClient()->GetChannel())
						{
							InGameInstance->GetClient()->GetChannel()->DestroySelf();//断开与登录服务器的连接
						}
						//延迟3s跳转
						GThread::Get()->GetCoroutines().BindLambda(3.f,
							[&]()
							{
								UGameplayStatics::OpenLevel(GetWorld(), TEXT("HallMap"));
							});

					}

				}
				break;
			}
			case LOGIN_ACCOUNT_WRONG:
			
				PrintLog(TEXT("Account does not exist"));
				break;
			
			case LOGIN_PASSWORD_WRONG:
			
				PrintLog(TEXT("Password is wrong"));
				break;
			
			}
			
			

 			break;
		}
		case SP_RegisterResponses:
		{
			ERegistrationType Type = ERegistrationType::SERVER_BUG_WRONG;

			//拿到客户端发送的账号
			SIMPLE_PROTOCOLS_RECEIVE(SP_RegisterResponses, Type);

			switch (Type)
			{
			case ACCOUNT_AND_EMAIL_REPETITION_ERROR:
			{
				PrintLog(LOCTEXT("ACCOUNT_AND_EMAIL_REPETITION_ERROR", "Duplicate account or email."));

				//协程
				GThread::Get()->GetCoroutines().BindLambda(0.5f, [&]()
					{
						SignUp();
					});

				break;
			}
			case PLAYER_REGISTRATION_SUCCESS:
				PrintLog(LOCTEXT("REGISTRATION_SUCCESS", "Registration was successful."));
				break;
			case SERVER_BUG_WRONG:
				PrintLog(LOCTEXT("SERVER_BUG_WRONG", "Server unknown error."));
				break;
			default:
				break;
			}
		}
	}
}

void UUI_LoginMain::LinkServerInfo(ESimpleNetErrorType InType, const FString& InMsg)
{
	if (InType==ESimpleNetErrorType::HAND_SHAKE_SUCCESS)
	{
		UI_LinkWidget->SetVisibility(ESlateVisibility::Collapsed);
		PlayWidgetAnim(TEXT("LoginIn"));
	}
}
#undef LOCTEXT_NAMESPACE