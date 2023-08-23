// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "Blueprint/UserWidget.h"

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

void UCombatWidget::SetEnemyAvatar(UMaterial* AvatarMaterial)
{
	EnemyAvatar->SetBrushFromMaterial(AvatarMaterial);
}

void UCombatWidget::SetEnemyName(FText EnemyName)
{
	EnemyNameTextBlock->SetText(EnemyName);
	// print enemy name
	UE_LOG(LogTemp, Warning, TEXT("Enemy name: %s"), *EnemyName.ToString());
}

void UCombatWidget::SetCurrentRoundText(int CurrentRound)
{
	CurrentRoundTextBlock->SetText(FText::FromString("Round " + FString::FromInt(CurrentRound)));
}

void UCombatWidget::SetEnemyHpBarPercent(float NormalizedPercent)
{
	EnemyHpBar->SetPercent(NormalizedPercent);
}

void UCombatWidget::SetPlayerHpBarPercent(float NormalizedPercent)
{
	PlayerHpBar->SetPercent(NormalizedPercent);
}

void UCombatWidget::SetActionBtnsEnabled_Implementation(bool IsEnabled)
{
	// Implement in Blueprint because we need to access the buttons
}






