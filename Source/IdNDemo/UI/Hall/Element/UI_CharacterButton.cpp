// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_CharacterButton.h"
#include "UI_CharacterPanel.h"
#include "../UI_HallMain.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/VerticalBox.h"

#include "../../../Core/Hall/HallPlayerState.h"
#include "Kismet/GameplayStatics.h"

void UUI_CharacterButton::NativeConstruct()
{
	Super::NativeConstruct();
	SlotPosition = INDEX_NONE;
	CharacterButton->OnReleased.AddDynamic(this, &UUI_CharacterButton::ClickedCharacter);
	CreateShowIcon->SetVisibility(ESlateVisibility::Visible);
	CharacterInfo->SetVisibility(ESlateVisibility::Collapsed);

	DefaultColor = CharacterButton->WidgetStyle.Normal.TintColor.GetSpecifiedColor();
}

void UUI_CharacterButton::NativeDestruct()
{
	Super::NativeDestruct();
}

void UUI_CharacterButton::SetSlotPostion(const int32 InNewPos)
{
	SlotPosition = InNewPos;
}

void UUI_CharacterButton::InitCharacterButton(const FIdNCharacterAppearance& InCA)
{
	if (InCA.SlotPosition != INDEX_NONE)
	{
		CreateShowIcon->SetVisibility(ESlateVisibility::Collapsed);
		CharacterInfo->SetVisibility(ESlateVisibility::Visible);

		CharacterName->SetText(FText::FromString(InCA.Name));
		Date->SetText(FText::FromString(InCA.Date));
	}
}

void UUI_CharacterButton::SetHighLight(bool bHighLight)
{
	if (bHighLight)
	{
		CharacterButton->WidgetStyle.Normal.TintColor = HighLightColor;
		CharacterButton->SetStyle(CharacterButton->WidgetStyle);

	}
	else
	{
		CharacterButton->WidgetStyle.Normal.TintColor = DefaultColor;
		CharacterButton->SetStyle(CharacterButton->WidgetStyle);
	}
}

void UUI_CharacterButton::ClickedCharacter()
{
	if (AHallPlayerState* InState = GetPlayerState<AHallPlayerState>())
	{

		if (UUI_CharacterPanel* InUI_CharacterPanel = GetWParent<UUI_CharacterPanel>())
		{


			if (!InState->IsCharacterExistInSlot(SlotPosition))
			{
				InUI_CharacterPanel->CreateCharacter();
				InUI_CharacterPanel->CreateEditData();

				if (UUI_HallMain* InHallMain = InUI_CharacterPanel->GetWParent<UUI_HallMain>())
				{
					InHallMain->PlayCreateIn();
				}
			}
			else
			{
				//进入DS服务器
				UGameplayStatics::OpenLevel(GetWorld(), TEXT("MainMap"));
			}
			InUI_CharacterPanel->SetCurrentSlotPosition(SlotPosition);
		}
		

		
	}
}
