// Copyright Epic Games, Inc. All Rights Reserved.

#include "IdNDemoGameMode.h"
#include "IdNDemoCharacter.h"
#include "UObject/ConstructorHelpers.h"

AIdNDemoGameMode::AIdNDemoGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
