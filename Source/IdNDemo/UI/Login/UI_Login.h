// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Core/UI_Base.h"

#include "UI_Login.generated.h"

class UEditableTextBox;
class UButton;
/**
 * 
 */
UCLASS()
class IDNDEMO_API UUI_Login : public UUI_Base
{
	GENERATED_BODY()
		UPROPERTY(meta = (Bindwidget))
		UEditableTextBox* AccountText;

	UPROPERTY(meta = (Bindwidget))
		UEditableTextBox* PasswordText;

	UPROPERTY(meta = (Bindwidget))
		UButton* SignInButton;

	UPROPERTY(meta = (Bindwidget))
		UButton* SignUpButton;

public:
	virtual void NativeConstruct();

	virtual void NativeDestruct();

	bool EncryptionToLocal(const FString& InPath);
	bool DecryptionFromLocal(const FString& InPath);
protected:
	UFUNCTION()
		void SignIn();

	UFUNCTION()
		void SignUp();
};
