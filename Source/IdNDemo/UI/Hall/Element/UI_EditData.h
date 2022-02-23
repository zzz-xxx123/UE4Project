// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../Core/UI_Base.h"
#include "UI_EditData.generated.h"

/**
 * 
 */
UCLASS()
class IDNDEMO_API UUI_EditData : public UUI_Base
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct();

	virtual void NativeDestruct();
};
