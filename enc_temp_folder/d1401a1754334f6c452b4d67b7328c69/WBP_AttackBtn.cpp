// Fill out your copyright notice in the Description page of Project Settings.


#include "WBP_AttackBtn.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/Border.h"
#include "Components/MenuAnchor.h"
#include "GenericPlatform/GenericPlatformMisc.h"
#include "CombatActionTooltipWidget.h"


void UWBP_AttackBtn::NativeConstruct()
{
	Super::NativeConstruct();

	if (!IsValid(ActionBtnText))
	{
		UE_LOG(LogTemp, Error, TEXT("UWBP_AttackBtn::NativeConstruct: Invalid ActionBtnText"));
		return;
	}
	if (!IsValid(ActionBtn))
	{
		UE_LOG(LogTemp, Error, TEXT("UWBP_AttackBtn::NativeConstruct: Invalid ActionBtn"));
		return;
	}
}

void UWBP_AttackBtn::SetActionButtonText(FText NewText)
{
	if (!IsValid(ActionBtnText))
	{
		UE_LOG(LogTemp, Error, TEXT("UWBP_AttackBtn::SetActionButtonText: Invalid ActionBtnText"));
		return;
	}
	ActionBtnText->SetText(NewText);

	if (!IsValid(ActionBtn))
	{
		UE_LOG(LogTemp, Error, TEXT("UWBP_AttackBtn::SetActionButtonText: Invalid ActionBtn"));
		return;
	}
	ActionBtn->OnClicked.AddUniqueDynamic(this, &UWBP_AttackBtn::OnActionBtnClicked);
	ActionBtn->OnHovered.AddUniqueDynamic(this, &UWBP_AttackBtn::OnActionBtnHovered);
	ActionBtn->OnUnhovered.AddUniqueDynamic(this, &UWBP_AttackBtn::OnActionBtnUnhovered);

	ActionName = NewText;

}

void UWBP_AttackBtn::OnActionBtnClicked()
{
	OnActionButtonClickedDelegate.Broadcast(this);
}

void UWBP_AttackBtn::OnActionBtnHovered()
{
	OnActionButtonHoveredDelegate.Broadcast(this);
}

void UWBP_AttackBtn::OnActionBtnUnhovered()
{
	OnActionButtonUnhoveredDelegate.Broadcast(this);
}

void UWBP_AttackBtn::HandleTooltipUpdateRequested(UCombatActionTooltipWidget* ActionTooltip)
{
	if (!IsValid(ActionTooltip))
	{
		UE_LOG(LogTemp, Error, TEXT("UWBP_AttackBtn::HandleTooltipUpdateRequested: Invalid ActionTooltip"));
		return;
	}
	if (ActionName.IsEmptyOrWhitespace())
	{
		UE_LOG(LogTemp, Error, TEXT("UWBP_AttackBtn::HandleTooltipUpdateRequested: Empty ActionName"));
		return;
	}

	ActionTooltip->SetCombatActionName(ActionName);
}