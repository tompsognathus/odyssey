// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatWidget.h"

void UCombatWidget::NativeConstruct()
{
	Super::NativeConstruct();

}

void UCombatWidget::HandleAttack1BtnClicked()
{
	UE_LOG(LogTemp, Warning, TEXT("Attack1BtnClicked"));
}

void UCombatWidget::HandleAttack2BtnClicked()
{
	UE_LOG(LogTemp, Warning, TEXT("Attack2BtnClicked"));
}

void UCombatWidget::HandleAttack3BtnClicked()
{
	UE_LOG(LogTemp, Warning, TEXT("Attack3BtnClicked"));
}

void UCombatWidget::HandleAttack4BtnClicked()
{
	UE_LOG(LogTemp, Warning, TEXT("Attack4BtnClicked"));
}

