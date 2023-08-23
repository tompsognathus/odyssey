// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/ProgressBar.h"
#include "Components/UniformGridPanel.h"
#include "Blueprint/UserWidget.h"
#include "CharSheet.h"
#include "DA_Item.h"
#include "DA_ItemAction.h"
#include "WBP_AttackBtn.h"
#include "CombatManager.h"


void UCombatWidget::NativeConstruct()
{
	Super::NativeConstruct();



}

void UCombatWidget::SetEnemyAvatar(UMaterial* AvatarMaterial)
{
	EnemyAvatar->SetBrushFromMaterial(AvatarMaterial);
}

void UCombatWidget::SetEnemyName(FText EnemyName)
{
	EnemyNameTextBlock->SetText(EnemyName);
}

void UCombatWidget::SetCurrentRoundText(int CurrentRound)
{
	CurrentRoundTextBlock->SetText(FText::FromString("Round " + FString::FromInt(CurrentRound)));
}

void UCombatWidget::SetEnemyHpBarPercent(float Percent)
{
	UE_LOG(LogTemp, Warning, TEXT("SetEnemyHpBarPercent: %f"), Percent);
	EnemyHpBar->SetPercent(Percent * 0.01f);
}

void UCombatWidget::SetPlayerHpBarPercent(float Percent)
{
	UE_LOG(LogTemp, Warning, TEXT("SetPlayerHpBarPercent: %f"), Percent);
	PlayerHpBar->SetPercent(Percent * 0.01f);
}

void UCombatWidget::SetUpAttackBtns(TArray<class UDA_ItemAction*> NewAttackActions)
{
	if (!PlayerActionGrid) { UE_LOG(LogTemp, Error, TEXT("PlayerActionGrid is null in CombatWidget, SetUpAttackBtns")); return; }

	AttackActions = NewAttackActions;

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

		// And to the grid with 4 columns
		int RowIdx = idx / 4;
		int ColIdx = idx % 4;

		PlayerActionGrid->AddChildToUniformGrid(AttackBtns[idx], RowIdx, ColIdx);

		// Set button text
		FText ActionName = FText::FromName(AttackActions[idx]->ActionDisplayName);
		AttackBtns[idx]->SetActionBtnText(ActionName);

		// Bind to OnClicked
		AttackBtns[idx]->OnActionBtnClickedDelegate.AddUniqueDynamic(this, &UCombatWidget::HandleAttackBtnClicked);
	}
}

void UCombatWidget::HandleAttackBtnClicked(UWBP_AttackBtn* AttackBtn)
{
	// Get button index by comparing against buttons in grid
	int BtnIdx = AttackBtns.Find(AttackBtn);

	// Get corresponding attack action
	if (AttackActions[BtnIdx] != nullptr)
	{
		UDA_ItemAction* AttackAction = AttackActions[BtnIdx];

	} else { UE_LOG(LogTemp, Error, TEXT("AttackAction is null in CombatWidget, HandleAttackBtnClicked")); }

	HandleCombatActionRequested(AttackActions[BtnIdx]);

}

void UCombatWidget::HandleCombatActionRequested(UDA_ItemAction* ItemAction)
{
	OnCombatActionRequestedDelegate.Broadcast(ItemAction);
}

void UCombatWidget::SetActionBtnsEnabled_Implementation(bool IsEnabled)
{
	// Implement in Blueprint because we need to access the buttons
}

void UCombatWidget::SetUpCombatantBindings(UCharSheet* NewPlayerCharSheet, UCharSheet* NewEnemyCharSheet)
{
	// TODO: Remove bindings
	
	
	PlayerCharSheet = NewPlayerCharSheet;
	EnemyCharSheet = NewEnemyCharSheet;

	if (PlayerCharSheet)
	{
		PlayerCharSheet->OnHpChangedDelegate.AddUniqueDynamic(this, &UCombatWidget::SetPlayerHpBarPercent);

	} else { UE_LOG(LogTemp, Error, TEXT("PlayerCharSheet is null in CombatWidget, SetUpCombatantBindings")); }

	if (EnemyCharSheet)
	{
		EnemyCharSheet->OnHpChangedDelegate.AddUniqueDynamic(this, &UCombatWidget::SetEnemyHpBarPercent);

	} else { UE_LOG(LogTemp, Error, TEXT("EnemyCharSheet is null in CombatWidget, SetUpCombatantBindings")); }
}





