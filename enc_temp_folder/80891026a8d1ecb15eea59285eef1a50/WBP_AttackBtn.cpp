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
	if (!IsValid(TooltipMenuAnchor))
	{
		UE_LOG(LogTemp, Error, TEXT("UWBP_AttackBtn::NativeConstruct: Invalid MenuAnchor"));
		return;
	}

	TooltipMenuAnchor->OnGetUserMenuContentEvent.BindUFunction(this, FName("GetUserMenuContent"));
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

	TooltipMenuAnchor->Open(true);
}

void UWBP_AttackBtn::OnActionBtnUnhovered()
{
	OnActionButtonUnhoveredDelegate.Broadcast(this);

	TooltipMenuAnchor->Close();
}

UUserWidget* UWBP_AttackBtn::GetUserMenuContent()
{
	if (!IsValid(TooltipMenuAnchor))
	{
		UE_LOG(LogTemp, Error, TEXT("UWBP_AttackBtn::HandleTooltipUpdateRequested: Invalid MenuAnchor"));
		return nullptr;
	}
	if (!IsValid(ActionTooltipWidget))
	{
		ActionTooltipWidget = CreateWidget<UCombatActionTooltipWidget>(GetWorld(), TooltipMenuAnchor->MenuClass);
	}

	UpdateTooltipWidget();

	return ActionTooltipWidget;
}


void UWBP_AttackBtn::UpdateTooltipWidget()
{
	if (!IsValid(ActionTooltipWidget))
	{
		UE_LOG(LogTemp, Error, TEXT("UWBP_AttackBtn::HandleTooltipUpdateRequested: Invalid ActionTooltipWidget"));
		return;
	}
	if (ActionName.IsEmptyOrWhitespace())
	{
		UE_LOG(LogTemp, Error, TEXT("UWBP_AttackBtn::HandleTooltipUpdateRequested: Empty ActionName"));
		return;
	}

	ActionTooltipWidget->SetCombatActionName(ActionName);

}