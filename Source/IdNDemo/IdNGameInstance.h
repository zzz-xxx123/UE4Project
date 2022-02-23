// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SimpleNetManage.h"
#include "NetGameType.h"
#include "IdNGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class IDNDEMO_API UIdNGameInstance : public UGameInstance,public FTickableGameObject
{
	GENERATED_BODY()
	
public:
	virtual void Init();

	virtual void Tick(float DeltaTime);

	virtual TStatId GetStatId() const;

	virtual void Shutdown();

public:
	void CreateClient();

	void LinkServer();


	FSimpleNetManage* GetClient();

	FIdNUserData& GetUserData();
	FIdNGateStatus& GetGateStatus();

private:
	FSimpleNetManage* Client;
	FIdNUserData UserData;
	FIdNGateStatus GateStatus;
};
