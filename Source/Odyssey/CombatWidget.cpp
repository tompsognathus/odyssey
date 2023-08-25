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
	if (!IsValid(EnemyAvatar))
	{
		UE_LOG(LogTemp, Error, TEXT("EnemyAvatar is null in CombatWidget, SetEnemyAvatar. Did you mess up the binding?"));
		return;
	}
	if (!IsValid(AvatarMaterial))
	{
		UE_LOG(LogTemp, Error, TEXT("AvatarMaterial is null in CombatWidget, SetEnemyAvatar. Did you forget to set the avatar material on the enemy NPC class? Make sure to also set it on the dialogue component."));
		return;
	}

	EnemyAvatar->SetBrushFromMaterial(AvatarMaterial);
}

void UCombatWidget::SetEnemyName(FText& EnemyName)
{
	if (!IsValid(EnemyNameTextBlock))
	{
		UE_LOG(LogTemp, Error, TEXT("EnemyNameTextBlock is null in CombatWidget, SetEnemyName. Did you mess up the binding?"));
		return;
	}

	EnemyNameTextBlock->SetText(EnemyName);
}

void UCombatWidget::SetCurrentRoundText(int CurrentRound)
{
	if (!IsValid(CurrentRoundTextBlock))
	{
		UE_LOG(LogTemp, Error, TEXT("CurrentRoundTextBlock is null in CombatWidget, SetCurrentRoundText. Did you mess up the binding?"));
		return;
	}

	CurrentRoundTextBlock->SetText(FText::FromString("Round " + FString::FromInt(CurrentRound)));
}

void UCombatWidget::SetEnemyHpBarPercent(float NormalizedPercent)
{
	if (!IsValid(EnemyHpBar))
	{
		UE_LOG(LogTemp, Error, TEXT("EnemyHpBar is null in CombatWidget, SetEnemyHpBarPercent. Did you mess up the binding?"));
		return;
	}

	EnemyHpBar->SetPercent(NormalizedPercent);
}

void UCombatWidget::SetPlayerHpBarPercent(float NormalizedPercent)
{
	if (!IsValid(PlayerHpBar))
	{
		UE_LOG(LogTemp, Error, TEXT("PlayerHpBar is null in CombatWidget, SetPlayerHpBarPercent. Did you mess up the binding?"));
		return;
	}

	PlayerHpBar->SetPercent(NormalizedPercent);
}

void UCombatWidget::SetUpAttackButtons(TArray<class UDA_ItemAction*> NewAttackActions)
{
	if (!PlayerActionGrid) 
	{
		UE_LOG(LogTemp, Error, TEXT("PlayerActionGrid is null in CombatWidget, SetUpAttackBtns")); 
		return; 
	}
	if (!AttackButtonAssetRef)
	{
		UE_LOG(LogTemp, Error, TEXT("AttackBtnAssetRef is null in CombatWidget, SetUpAttackBtns"));
		return;
	}

	AttackActions = NewAttackActions;

	// First remove any existing buttons
	PlayerActionGrid->ClearChildren();

	// Then create new buttons for each attack action
	for (int idx = 0; idx < AttackActions.Num(); idx++)
	{
		UUserWidget* AttackButtonWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), AttackButtonAssetRef);
		if (!AttackButtonWidgetInstance) 
		{ 
			UE_LOG(LogTemp, Error, TEXT("Cannot create AttackBtnWidgetInstance in CombatWidget, SetUpAttackBtns")); 
			return; 
		}

		UWBP_AttackBtn* AttackButton = Cast<UWBP_AttackBtn>(AttackButtonWidgetInstance);
		if (!AttackButton) 
		{ 
			UE_LOG(LogTemp, Error, TEXT("Cannot cast AttackBtnWidgetInstance to UWBP_AttackBtn in CombatWidget, SetUpAttackBtns")); 
			return; 
		} 
		
		AttackButtons.Add(AttackButton);

		// And to the grid with 4 columns
		int RowIdx = idx / NumButtonsPerRow;
		int ColIdx = idx % NumButtonsPerRow;

		PlayerActionGrid->AddChildToUniformGrid(AttackButtons[idx], RowIdx, ColIdx);

		// Set button text
		FText ActionName = FText::FromName(AttackActions[idx]->ActionDisplayName);
		AttackButtons[idx]->SetActionButtonText(ActionName);

		// Bind to OnClicked
		AttackButtons[idx]->OnActionButtonClickedDelegate.AddUniqueDynamic(this, &UCombatWidget::HandleAttackButtonClicked);
	}
}

void UCombatWidget::HandleAttackButtonClicked(UWBP_AttackBtn* AttackButton)
{
	// Get button index by comparing against buttons in grid
	int ButtonIdx = AttackButtons.Find(AttackButton);

	// Get corresponding attack action
	if (!IsValid(AttackActions[ButtonIdx]))
	{
		UE_LOG(LogTemp, Error, TEXT("AttackAction is null in CombatWidget, HandleAttackButtonClicked"));
		return;
	}

	UDA_ItemAction* AttackAction = AttackActions[ButtonIdx];
	HandleCombatActionRequested(AttackActions[ButtonIdx]);

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
	PlayerCharSheet = NewPlayerCharSheet;
	EnemyCharSheet = NewEnemyCharSheet;

	if (!IsValid(PlayerCharSheet))
	{
		UE_LOG(LogTemp, Error, TEXT("PlayerCharSheet is null in CombatWidget, SetUpCombatantBindings"));
		return;
	}
	if (!IsValid(EnemyCharSheet))
	{
		UE_LOG(LogTemp, Error, TEXT("EnemyCharSheet is null in CombatWidget, SetUpCombatantBindings"));
		return;
	}

	PlayerCharSheet->OnHpChangedDelegate.AddDynamic(this, &UCombatWidget::SetPlayerHpBarPercent);
	EnemyCharSheet->OnHpChangedDelegate.AddDynamic(this, &UCombatWidget::SetEnemyHpBarPercent);

}

void UCombatWidget::RemoveCombatantBindings()
{
	if (!IsValid(PlayerCharSheet))
	{
		UE_LOG(LogTemp, Error, TEXT("PlayerCharSheet is null in CombatWidget, RemoveCombatantBindings"));
		return;
	}
	if (!IsValid(EnemyCharSheet))
	{
		UE_LOG(LogTemp, Error, TEXT("EnemyCharSheet is null in CombatWidget, RemoveCombatantBindings"));
		return;
	}
	
	PlayerCharSheet->OnHpChangedDelegate.RemoveDynamic(this, &UCombatWidget::SetPlayerHpBarPercent);
	EnemyCharSheet->OnHpChangedDelegate.RemoveDynamic(this, &UCombatWidget::SetEnemyHpBarPercent);

}




