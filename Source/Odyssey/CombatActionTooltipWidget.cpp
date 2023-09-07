// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatActionTooltipWidget.h"
#include "Components/TextBlock.h"
#include "Components/MenuAnchor.h"

void UCombatActionTooltipWidget::NativeConstruct()
{
	Super::NativeConstruct();

}

void UCombatActionTooltipWidget::SetCombatActionName(FText NewActionName)
{
	ActionName->SetText(NewActionName);

}

