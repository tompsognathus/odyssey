// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatActionTooltipWidget.h"
#include "Components/TextBlock.h"

void UCombatActionTooltipWidget::SetCombatActionName(FText NewActionName)
{
	ActionName->SetText(NewActionName);
}
