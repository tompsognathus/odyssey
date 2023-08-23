// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "Components/UniformGridPanel.h"
#include "Blueprint/UserWidget.h"
#include "CharSheet.h"
#include "DA_Item.h"
#include "DA_ItemAction.h"
#include "WBP_AttackBtn.h"


void UCombatWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// Get player pawn
	APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (PlayerPawn)
	{
		// Get CharSheet component
		CharSheet = Cast<UCharSheet>(PlayerPawn->GetComponentByClass(UCharSheet::StaticClass()));

		if (!CharSheet) { UE_LOG(LogTemp, Error, TEXT("Cannot find CharSheet in HUDWidget, NativeConstruct")); }
	}

	// Bind to CharSheet Delegates to update HUD
	if (CharSheet)
	{
		CharSheet->OnHpChangedDelegate.AddDynamic(this, &UCombatWidget::SetPlayerHpBarPercent);

	} else { UE_LOG(LogTemp, Error, TEXT("Cannot bind to CharSheet Delegates in HUDWidget, NativeConstruct")); }
}

//void UCombatWidget::HandleAttack1BtnClicked()
//{
//	UE_LOG(LogTemp, Warning, TEXT("Attack1BtnClicked"));
//}
//
//void UCombatWidget::HandleAttack2BtnClicked()
//{
//	UE_LOG(LogTemp, Warning, TEXT("Attack2BtnClicked"));
//}
//
//void UCombatWidget::HandleAttack3BtnClicked()
//{
//	UE_LOG(LogTemp, Warning, TEXT("Attack3BtnClicked"));
//}
//
//void UCombatWidget::HandleAttack4BtnClicked()
//{
//	UE_LOG(LogTemp, Warning, TEXT("Attack4BtnClicked"));
//}

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

void UCombatWidget::SetUpAttackBtns(TArray<class UDA_ItemAction*> AttackActions)
{
	if (!PlayerActionGrid) { UE_LOG(LogTemp, Error, TEXT("PlayerActionGrid is null in CombatWidget, SetUpAttackBtns")); return; }

	// First remove any existing buttons
	PlayerActionGrid->ClearChildren();

	for (int idx = 0; idx < AttackActions.Num(); idx++)
	{
		// Create the button widget
		UUserWidget* AttackBtnWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), AttackBtnAssetRef);
		if (!AttackBtnWidgetInstance) { UE_LOG(LogTemp, Error, TEXT("Cannot create AttackBtnWidgetInstance in CombatWidget, SetUpAttackBtns")); return; }

		UWBP_AttackBtn* AttackBtn = Cast<UWBP_AttackBtn>(AttackBtnWidgetInstance);
		if (!AttackBtn) { UE_LOG(LogTemp, Error, TEXT("Cannot cast AttackBtnWidgetInstance to UWBP_AttackBtn in CombatWidget, SetUpAttackBtns")); return; } 
		
		// Add it to the attack button array
		AttackBtns.Add(AttackBtn);

		// And to the grid
		PlayerActionGrid->AddChildToUniformGrid(AttackBtns[idx], 0, idx);

		// Set button text
		FText ActionName = FText::FromName(AttackActions[idx]->ActionName);
		AttackBtns[idx]->SetActionBtnText(ActionName);
	}
}

void UCombatWidget::SetActionBtnsEnabled_Implementation(bool IsEnabled)
{
	// Implement in Blueprint because we need to access the buttons
}






