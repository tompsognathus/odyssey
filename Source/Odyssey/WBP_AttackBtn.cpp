// Fill out your copyright notice in the Description page of Project Settings.


#include "WBP_AttackBtn.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "GenericPlatform/GenericPlatformMisc.h"


void UWBP_AttackBtn::SetActionBtnText(FText NewText)
{
	if (ActionBtnText != nullptr) {
		ActionBtnText->SetText(NewText);

	} else { UE_LOG(LogTemp, Warning, TEXT("ActionBtnText is nullptr in WBP_AttackBtn, SetActionBtnText")); }


	// Bind to ActionBtn Clicked Event
	if (ActionBtn)
	{
		ActionBtn->OnClicked.AddUniqueDynamic(this, &UWBP_AttackBtn::OnActionBtnClicked);

	} else { UE_LOG(LogTemp, Warning, TEXT("ActionBtn is nullptr in WBP_AttackBtn, SetActionBtnText")); }

}

void UWBP_AttackBtn::OnActionBtnClicked()
{
	OnActionBtnClickedDelegate.Broadcast(this);
}
