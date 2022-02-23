// Fill out your copyright notice in the Description page of Project Settings.


#include "IdNGameInstance.h"
#include "Global/SimpleNetGlobalInfo.h"
#include "ThreadManage.h"


void UIdNGameInstance::Init()
{
	Super::Init();
}

void UIdNGameInstance::Tick(float DeltaTime)
{
	if (Client)
	{
		Client->Tick(DeltaTime);
		GThread::Get()->Tick(DeltaTime);
	}
}

TStatId UIdNGameInstance::GetStatId() const
{
	return TStatId();
}

void UIdNGameInstance::Shutdown()
{
	Super::Shutdown();
	if (Client)
	{
		FSimpleNetManage::Destroy(Client);
		GThread::Destroy();
	}
}

void UIdNGameInstance::CreateClient()
{
	FSimpleNetGlobalInfo::Get()->Init();
	Client = FSimpleNetManage::CreateManage(
		ESimpleNetLinkState::LINKSTATE_CONNET,
		ESimpleSocketType::SIMPLESOCKETTYPE_TCP
	);
}

void UIdNGameInstance::LinkServer()
{
	if (Client)
	{
		if (!Client->Init())
		{
			delete Client;
			Client = nullptr;
		}
	}
}

FSimpleNetManage* UIdNGameInstance::GetClient()
{
	return Client;
}

FIdNUserData& UIdNGameInstance::GetUserData()
{
	return UserData;
}

FIdNGateStatus& UIdNGameInstance::GetGateStatus()
{
	return GateStatus;
}
