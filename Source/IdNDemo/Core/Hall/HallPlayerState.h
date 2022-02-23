// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "NetGameType.h"
#include "HallPlayerState.generated.h"


/**
 * 
 */
UCLASS()
class IDNDEMO_API AHallPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	FCharacterAppearances& GetCharacterAppearances();

	bool IsCharacterExistInSlot(const int32 InPos);

	FIdNCharacterAppearance* GetRecentlyCharacter();
private:
	FCharacterAppearances CharacterAppearances;
	
};
