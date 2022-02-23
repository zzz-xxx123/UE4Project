// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_CharacterPanel.h"
#include "UI_CharacterButton.h"
#include "Components/ScrollBoxSlot.h"
#include "UI_EditData.h"
#include "../../../Core/Hall/HallPlayerState.h"
#include "../../../Core/Hall/Character/CharacterStage.h"
#include "../../../Core/Hall/HallPawn.h"

void UUI_CharacterPanel::NativeConstruct()
{
	Super::NativeConstruct();
	SlotPosition = 0;
}

void UUI_CharacterPanel::NativeDestruct()
{
	Super::NativeDestruct();
}

void UUI_CharacterPanel::CreateEditData()
{
	List->ClearChildren();
	if (UI_EditDataClass)
	{
		if (UUI_EditData* InEditData = CreateWidget<UUI_EditData>(GetWorld(), UI_EditDataClass))
		{
			if (UScrollBoxSlot* InScrollBoxSlot = Cast<UScrollBoxSlot>(List->AddChild(InEditData)))
			{
				InScrollBoxSlot->SetPadding(10.f);
			}
		}
	}
	
}

void UUI_CharacterPanel::CreateCharacterButton()
{
	if (AHallPlayerState* InState = GetPlayerState<AHallPlayerState>())
	{
		InitCharacterButtons(InState->GetCharacterAppearances());
	}
}

void UUI_CharacterPanel::InitCharacterButtons(FCharacterAppearances& InCAs)
{
	List->ClearChildren();
	if (UI_CharacterButtonClass)
	{
		for (int32 i = 0; i < 4; i++)
		{
			if (UUI_CharacterButton* InCharacterButton = CreateWidget<UUI_CharacterButton>(GetWorld(), UI_CharacterButtonClass))
			{
				if (UScrollBoxSlot* InScrollBoxSlot = Cast<UScrollBoxSlot>(List->AddChild(InCharacterButton)))
				{
					InScrollBoxSlot->SetPadding(10.f);
				}
				InCharacterButton->SetSlotPostion(i);
				InCharacterButton->SetWParent(this);
				if (const FIdNCharacterAppearance* InCharacterAppearance=
					InCAs.FindByPredicate([&](const FIdNCharacterAppearance& InCharacterAppearance)
						{
							return InCharacterAppearance.SlotPosition == i;
						}))
				{
					InCharacterButton->InitCharacterButton(*InCharacterAppearance);
				}
					
			}
		}
	}


}

ACharacterStage* UUI_CharacterPanel::CreateCharacter()
{
	if (CharacterStageClass)
	{
		if (AHallPawn* InPawn = GetPawn<AHallPawn>())
		{
			if (InPawn->CharacterStage)
			{
				InPawn->CharacterStage->Destroy();
			}
			InPawn->CharacterStage = GetWorld()->SpawnActor<ACharacterStage>(CharacterStageClass, SpawnPoint, FRotator::ZeroRotator);
			
			return InPawn->CharacterStage;
		}
	}
	return nullptr;
}

void UUI_CharacterPanel::SpawnCharacter(const int32 InSlotPos)
{
	if (AHallPlayerState* InState = GetPlayerState<AHallPlayerState>())
	{
		if (FIdNCharacterAppearance* InCAData = InState->GetCharacterAppearances().FindByPredicate(
			[&](const FIdNCharacterAppearance& InCA)
			{
				return InSlotPos == InCA.SlotPosition;
			})
			)
		{
			SpawnCharacter(InCAData);
		}
	}
}

void UUI_CharacterPanel::SpawnCharacter(const FIdNCharacterAppearance* InCAData)
{
	if (InCAData)
	{

		if (ACharacterStage* InCharacter = CreateCharacter())
		{

		}
	}
}

void UUI_CharacterPanel::SpawnCharacter()
{
	SpawnCharacter(SlotPosition);
}


void UUI_CharacterPanel::SetCurrentSlotPosition(const int32 InSlotPos)
{
	SlotPosition = InSlotPos;

	//HighLightSelection(SlotPosition);
}

void UUI_CharacterPanel::HighLightSelection(int32 InSlotPos)
{
	FindByPredicateInList<UUI_CharacterButton>([InSlotPos](UUI_CharacterButton* InBtn)->bool
		{
			if (InSlotPos == InBtn->GetSlotPostion())
			{
				InBtn->SetHighLight(true);
			}
			else
			{
				InBtn->SetHighLight(false);
			}
			return false;
		});
}
