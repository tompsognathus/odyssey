// Fill out your copyright notice in the Description page of Project Settings.


#include "WBP_OptionsMenu.h"

#include "UIManager.h"
#include "Utility.h"

void UWBP_OptionsMenu::NativeConstruct()
{
	Super::NativeConstruct();

	UIManager = Utility::GetUIManager(this);
	if (!IsValid(UIManager))
	{
		UE_LOG(LogTemp, Error, TEXT("UWBP_OptionsMenu::NativeConstruct: Invalid UIManager"));
		return;
	}
}

void UWBP_OptionsMenu::HandleAudioBtnClicked()
{
	if (!IsValid(UIManager))
	{
		UE_LOG(LogTemp, Error, TEXT("UWBP_OptionsMenu::HandleAudioBtnClicked: Invalid UIManager"));
		return;
	}
	UIManager->DisplayAudioOptionsMenuWidget();
}

void UWBP_OptionsMenu::HandleVideoBtnClicked()
{
	UE_LOG(LogTemp, Display, TEXT("Video button clicked"));

}

void UWBP_OptionsMenu::HandleGameplayBtnClicked()
{
	UE_LOG(LogTemp, Display, TEXT("Options button clicked"));
}

void UWBP_OptionsMenu::HandleBackBtnClicked()
{
	if (!IsValid(UIManager))
	{
		UE_LOG(LogTemp, Error, TEXT("UWBP_OptionsMenu::HandleBackBtnClicked: Invalid UIManager"));
		return;
	}
	UIManager->DisplayPreviousWidget();
}
