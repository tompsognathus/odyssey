// Fill out your copyright notice in the Description page of Project Settings.


#include "WBP_AttackBtn.h"
#include "Components/TextBlock.h"

void UWBP_AttackBtn::SetActionBtnText(FText NewText)
{
	// Print text
	UE_LOG(LogTemp, Warning, TEXT("WBP_AttackBtn, SetActionBtnText: %s"), *NewText.ToString());

	if (ActionBtnText == nullptr) { UE_LOG(LogTemp, Warning, TEXT("ActionBtnText is nullptr in WBP_AttackBtn, SetActionBtnText")); return; }

	ActionBtnText->Text = NewText;

	// Print Action Button Text
	UE_LOG(LogTemp, Warning, TEXT("New ActionBtnText: %s"), *ActionBtnText->Text.ToString());
}
