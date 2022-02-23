// Fill out your copyright notice in the Description page of Project Settings.


#include "HallPlayerState.h"


FCharacterAppearances& AHallPlayerState::GetCharacterAppearances()
{
	return CharacterAppearances;
}

bool AHallPlayerState::IsCharacterExistInSlot(const int32 InPos)
{
	return CharacterAppearances.FindByPredicate(
		[InPos](const FIdNCharacterAppearance& InCA) 
		{return InPos == InCA.SlotPosition; }) != nullptr;
}

FIdNCharacterAppearance* AHallPlayerState::GetRecentlyCharacter()
{
	FDateTime MaxDateTime;
	int32 Index = INDEX_NONE;
	for (int32 i = 0;i<CharacterAppearances.Num();i++)
	{
		FDateTime DateTime;
		FDateTime::Parse(CharacterAppearances[i].Date, DateTime);
		if (DateTime > MaxDateTime)
		{
			MaxDateTime = DateTime;
			Index = i;
		}
	}
	if (Index != INDEX_NONE)
	{
		return &CharacterAppearances[Index];
	}
	return nullptr;
}
