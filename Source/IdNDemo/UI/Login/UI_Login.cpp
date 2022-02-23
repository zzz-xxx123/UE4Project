// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_Login.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "UI_LoginMain.h"
#include "Stream/SimpleIOStream.h"

void UUI_Login::NativeConstruct()
{
	Super::NativeConstruct();

	SignInButton->OnReleased.AddDynamic(this,&UUI_Login::SignIn);
	SignUpButton->OnReleased.AddDynamic(this,&UUI_Login::SignUp);
}

void UUI_Login::NativeDestruct()
{
	Super::NativeDestruct();
}

bool UUI_Login::EncryptionToLocal(const FString& InPath)
{
	FString AccountString = AccountText->GetText().ToString();
	FString PasswordString = PasswordText->GetText().ToString();

	//路径纠正
	FString InCopyPath = InPath;
	FPaths::NormalizeFilename(InCopyPath);// "\\" -> "/"
	InCopyPath.RemoveFromEnd(TEXT("/"));

	if (!AccountString.IsEmpty() && !PasswordString.IsEmpty() && !InCopyPath.IsEmpty())
	{
		TArray<uint8> PasswordBuff;
		FSimpleIOStream Stream(PasswordBuff);

		Stream << PasswordString; //将密码序列化

		FString HashKey = FMD5::HashAnsiString(*AccountString);

		for (int32 i = 0; i < 32; i++)
		{
			HashKey = FMD5::HashAnsiString(*HashKey);
		}
		if (!HashKey.IsEmpty())
		{
			int32 Remain = 0;
			int32 Total = PasswordBuff.Num();
			if (Total % 16)
			{
				float Value = (float)Total / 16.f;
				int32 Ceil = FMath::CeilToInt(Value);

				int32 CeilTotal = Ceil * 16;
				Remain = CeilTotal - Total;
			}
			for (int32 i = 0; i < Remain; i++)
			{
				uint8 Tmp = 0;
				Stream << Tmp;
			}
			ANSICHAR* InKey = TCHAR_TO_UTF8(*HashKey);
			FAES::EncryptData(PasswordBuff.GetData(), PasswordBuff.Num(), InKey);

			//删除保存用户
			IFileManager::Get().DeleteDirectory(*InCopyPath);

			//储存新用户
			FFileHelper::SaveArrayToFile(PasswordBuff, *(InCopyPath / AccountString + TEXT(".idn")));
			return true;
		}
	}
	return false;
}

bool UUI_Login::DecryptionFromLocal(const FString& InPath)
{
	//路径纠正
	FString InCopyPath = InPath;
	FPaths::NormalizeFilename(InCopyPath);// "\\" -> "/"
	InCopyPath.RemoveFromEnd(TEXT("/"));

	TArray<FString> FileNames;
	IFileManager::Get().FindFilesRecursive(FileNames, *InCopyPath, TEXT("*.*"), true, false);

	for (auto& Tmp : FileNames)
	{
		FString FileNameHead = FPaths::GetCleanFilename(Tmp);
		if (FileNameHead.Contains(TEXT(".idn")))
		{
			TArray<uint8> InByte;
			FFileHelper::LoadFileToArray(InByte, *Tmp);
			FileNameHead.RemoveFromEnd(TEXT(".idn"));
			if (InByte.Num()>0)
			{
				FString HashKey = FMD5::HashAnsiString(*FileNameHead);

				for (int32 i = 0; i < 32; i++)
				{
					HashKey = FMD5::HashAnsiString(*HashKey);
				}
				if (!HashKey.IsEmpty())
				{
					FSimpleIOStream Stream(InByte);
					ANSICHAR* InKey = TCHAR_TO_UTF8(*HashKey);

					FAES::DecryptData(InByte.GetData(), InByte.Num(), InKey);

					FString PasswordString;
					Stream >> PasswordString;
					
					AccountText->SetText(FText::FromString(FileNameHead));
					PasswordText->SetText(FText::FromString(PasswordString));
					return true;
				}
			}
		}
	}
	return false;
}

void UUI_Login::SignIn()
{
	if (UUI_LoginMain* InLoginMain = GetWParent<UUI_LoginMain>())
	{
		FString AccountString = AccountText->GetText().ToString();
		FString PasswordString = PasswordText->GetText().ToString();
		InLoginMain->SignIn(AccountString, PasswordString);
	}
}

void UUI_Login::SignUp()
{
	if (UUI_LoginMain* InLoginMain = GetWParent<UUI_LoginMain>())
	{
		InLoginMain->SignUp();
	}
}
