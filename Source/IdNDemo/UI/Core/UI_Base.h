// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI_Base.generated.h"

class FSimpleChannel;
/**
 * 
 */
UCLASS()
class IDNDEMO_API UUI_Base : public UUserWidget
{
	GENERATED_BODY()
public:
	template<class T>
	T* GetPlayerController() 
	{
		return GetWorld() != nullptr ? GetWorld()->GetFirstPlayerController<T>() : nullptr;
	}

	template<class T>
	T* GetPawn()
	{
		return GetWorld() != nullptr ? 
				GetWorld()->GetFirstPlayerController() != nullptr ? 
			GetWorld()->GetFirstPlayerController()->GetPawn<T>() : nullptr 
			:nullptr;
	}

	template<class T>
	T* GetGameInstance() 
	{
		return GetWorld() != nullptr ? GetWorld()->GetGameInstance<T>() : nullptr;
	}
	template<class T>
	T* GetPlayerState()
	{
		return GetWorld() != nullptr ?
			GetWorld()->GetFirstPlayerController() != nullptr ?
			GetWorld()->GetFirstPlayerController()->GetPlayerState<T>() : nullptr
			: nullptr;
	}
public:
	void SetWParent(UWidget * InWidget)
	{
		ParentWidget = InWidget;
	}
	template<class T>
	T* GetWParent()
	{
		return Cast<T>(ParentWidget);
	}


	void PlayWidgetAnim(const FString& InWidgetAnimName);
protected:
	virtual void RecvProtocol(uint32 ProtocolNumber, FSimpleChannel* Channel){}

	UWidgetAnimation* GetNameWidgetAnimation(const FString& InWidgetAnimName);

protected:
	UPROPERTY()
	UWidget* ParentWidget;


};
