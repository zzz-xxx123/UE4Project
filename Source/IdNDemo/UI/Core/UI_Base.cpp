// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_Base.h"

UWidgetAnimation* UUI_Base::GetNameWidgetAnimation(const FString& InWidgetAnimName)
{
	if (UWidgetBlueprintGeneratedClass* WidgetBlueprintGenerated = Cast<UWidgetBlueprintGeneratedClass>(GetClass()))
	{
		TArray<UWidgetAnimation*> Anims = WidgetBlueprintGenerated->Animations;
		UWidgetAnimation** MyTmpAnim = Anims.FindByPredicate(
			[&](const UWidgetAnimation* OurAnimation)
			{
				return OurAnimation->GetFName().ToString() == (InWidgetAnimName + FString("_INST"));
			});
		return *MyTmpAnim;
	}
	return NULL;
}

void UUI_Base::PlayWidgetAnim(const FString& InWidgetAnimName)
{
	if (UWidgetAnimation* MyTmpAnim = GetNameWidgetAnimation(InWidgetAnimName))
	{
		PlayAnimation(MyTmpAnim);
	}
}
