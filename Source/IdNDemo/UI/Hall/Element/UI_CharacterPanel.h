// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../Core/UI_Base.h"
#include "NetGameType.h"
#include "Components/ScrollBox.h"
#include "UI_CharacterPanel.generated.h"

class UTextBlock;
class UScrollBox;
class UUI_CharacterButton;
class UUI_EditData;
class ACharacterStage;
/**
 * 
 */
UCLASS()
class IDNDEMO_API UUI_CharacterPanel : public UUI_Base
{
	GENERATED_BODY()
		UPROPERTY(meta = (BindWidget))
		UTextBlock* PanelName;

	UPROPERTY(meta = (BindWidget))
		UScrollBox* List;

	UPROPERTY(EditDefaultsOnly,Category = UI)
	TSubclassOf<UUI_CharacterButton> UI_CharacterButtonClass;

	UPROPERTY(EditDefaultsOnly, Category = UI)
		TSubclassOf<UUI_EditData> UI_EditDataClass;

	UPROPERTY(EditDefaultsOnly, Category = Character)
		TSubclassOf<ACharacterStage> CharacterStageClass;

	UPROPERTY(EditDefaultsOnly, Category = Character)
		FVector SpawnPoint;
public:
	virtual void NativeConstruct();

	virtual void NativeDestruct();

	void CreateEditData();

	void CreateCharacterButton();

	void InitCharacterButtons(FCharacterAppearances& InCAs);

	ACharacterStage* CreateCharacter();
	void SpawnCharacter(const int32 InSlotPos);
	void SpawnCharacter(const FIdNCharacterAppearance* InCAData);
	void SpawnCharacter();

	void SetCurrentSlotPosition(const int32 InSlotPos);
	void HighLightSelection(int32 InSlotPos);

	//boolean 代表是否继续循环遍历
	template<class T>
	void FindByPredicateInList(TFunction<bool(T*)> Func)
	{
		for (auto& Tmp : List->GetAllChildren())
		{
			if (T* InBtn = Cast<T>(Tmp))
			{
				if (Func(InBtn))
				{
					break;
				}
			}
		}
	}
protected:
	int32 SlotPosition;//记录当前选择的角色
};
