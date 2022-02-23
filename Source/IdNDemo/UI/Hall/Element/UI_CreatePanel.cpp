// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_CreatePanel.h"
#include "Components/Button.h"
#include "../UI_HallMain.h"
#include "../../../Core/Hall/HallPawn.h"
#include "../../../Core/Hall/Character/CharacterStage.h"

void UUI_CreatePanel::NativeConstruct()
{
	Super::NativeConstruct();

	CheckButton->OnReleased.AddDynamic(this, &UUI_CreatePanel::CheckName);

	CreateButton->OnReleased.AddDynamic(this, &UUI_CreatePanel::CreateCharacter);

	CancelButton->OnReleased.AddDynamic(this, & UUI_CreatePanel::Cancel);

}

void UUI_CreatePanel::NativeDestruct()
{
	Super::NativeDestruct();
}

void UUI_CreatePanel::CheckName()
{

}

void UUI_CreatePanel::CreateCharacter()
{
	if (UUI_HallMain* InHallMain=GetWParent<UUI_HallMain>())
	{
		InHallMain->PlayCreateOut();
		InHallMain->ResetCharacterPanel();
	}
}

void UUI_CreatePanel::Cancel()
{
	if (UUI_HallMain* InHallMain = GetWParent<UUI_HallMain>())
	{
		InHallMain->PlayCreateOut();
		InHallMain->ResetCharacterPanel();
	}
}
