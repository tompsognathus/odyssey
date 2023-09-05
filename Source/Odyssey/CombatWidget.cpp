// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/ProgressBar.h"
#include "Components/UniformGridPanel.h"
#include "Components/Border.h"
#include "Blueprint/UserWidget.h"
#include "CharSheet.h"
#include "DA_Item.h"
#include "DA_ItemAction.h"
#include "WBP_AttackBtn.h"
#include "CombatManager.h"
#include "Math/Color.h"


void UCombatWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (!IsValid(PlayerBorder))
	{
		UE_LOG(LogTemp, Error, TEXT("UCombatWidget::NativeConstruct: Invalid PlayerBorder"));
		return;
	}
	DefaultBorderBrushColor = PlayerBorder->GetBrushColor();
}

void UCombatWidget::SetEnemyAvatar(UMaterial* AvatarMaterial)
{
	if (!IsValid(EnemyAvatar))
	{
		UE_LOG(LogTemp, Error, TEXT("UCombatWidget::SetEnemyAvatar: Invalid EnemyAvatar. Did you mess up the binding?"));
		return;
	}
	if (!IsValid(AvatarMaterial))
	{
		UE_LOG(LogTemp, Error, TEXT("UCombatWidget::SetEnemyAvatar: Invalid AvatarMaterial. Did you forget to set the avatar material on the enemy NPC class? Make sure to also set it on the dialogue component."));
		return;
	}

	EnemyAvatar->SetBrushFromMaterial(AvatarMaterial);
}

void UCombatWidget::SetEnemyName(FText& EnemyName)
{
	if (!IsValid(EnemyNameTextBlock))
	{
		UE_LOG(LogTemp, Error, TEXT("UCombatWidget::SetEnemyName: Invalid EnemyNameTextBlock. Did you mess up the binding?"));
		return;
	}

	EnemyNameTextBlock->SetText(EnemyName);
}

void UCombatWidget::SetCurrentRoundText(int CurrentRound)
{
	if (!IsValid(CurrentRoundTextBlock))
	{
		UE_LOG(LogTemp, Error, TEXT("UCombatWidget::SetCurrentRoundText: Invalid CurrentRoundTextBlock. Did you mess up the binding?"));
		return;
	}

	CurrentRoundTextBlock->SetText(FText::FromString("Round " + FString::FromInt(CurrentRound)));
}

void UCombatWidget::SetEnemyHpBarPercent(float NormalizedPercent)
{
	if (!IsValid(EnemyHpBar))
	{
		UE_LOG(LogTemp, Error, TEXT("UCombatWidget::SetEnemyHpBarPercent: Invalid EnemyHpBar. Did you mess up the binding?"));
		return;
	}

	EnemyHpBar->SetPercent(NormalizedPercent);
}

void UCombatWidget::SetPlayerHpBarPercent(float NormalizedPercent)
{
	if (!IsValid(PlayerHpBar))
	{
		UE_LOG(LogTemp, Error, TEXT("UCombatWidget::SetPlayerHpBarPercent: PlayerHpBar is null. Did you mess up the binding?"));
		return;
	}

	PlayerHpBar->SetPercent(NormalizedPercent);
}

void UCombatWidget::SetUpAttackButtons(TArray<class UDA_ItemAction*> NewAttackActions)
{
	if (!IsValid(PlayerActionGrid)) 
	{
		UE_LOG(LogTemp, Error, TEXT("UCombatWidget::SetUpAttackButtons: Invalid PlayerActionGrid")); 
		return; 
	}
	if (!IsValid(AttackButtonAssetRef))
	{
		UE_LOG(LogTemp, Error, TEXT("UCombatWidget::SetUpAttackButtons: Invalid AttackBtnAssetRef"));
		return;
	}

	AttackActions = NewAttackActions;

	// First remove any existing buttons
	PlayerActionGrid->ClearChildren();

	// Then create new buttons for each attack action
	for (int idx = 0; idx < AttackActions.Num(); idx++)
	{
		UUserWidget* AttackButtonWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), AttackButtonAssetRef);
		if (!IsValid(AttackButtonWidgetInstance)) 
		{ 
			UE_LOG(LogTemp, Error, TEXT("UCombatWidget::SetUpAttackButtons: Cannot create AttackBtnWidgetInstance")); 
			return; 
		}

		UWBP_AttackBtn* AttackButton = Cast<UWBP_AttackBtn>(AttackButtonWidgetInstance);
		if (!IsValid(AttackButton)) 
		{ 
			UE_LOG(LogTemp, Error, TEXT("UCombatWidget::SetUpAttackButtons: Cannot cast AttackBtnWidgetInstance to UWBP_AttackBtn")); 
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

		// Set up bindings
		AttackButtons[idx]->OnActionButtonClickedDelegate.AddUniqueDynamic(this, &UCombatWidget::HandleAttackButtonClicked);
		AttackButtons[idx]->OnActionButtonHoveredDelegate.AddUniqueDynamic(this, &UCombatWidget::HandleAttackButtonHovered);
		AttackButtons[idx]->OnActionButtonUnhoveredDelegate.AddUniqueDynamic(this, &UCombatWidget::HandleAttackButtonUnhovered);

	}
}

void UCombatWidget::HighlightPlayerBorder()
{
	HighlightBorder(PlayerBorder, EnemyBorder);
}

void UCombatWidget::HighlightEnemyBorder()
{
	HighlightBorder(EnemyBorder, PlayerBorder);
}

void UCombatWidget::HandleAttackButtonClicked(UWBP_AttackBtn* AttackButton)
{
	// Get button index by comparing against buttons in grid
	int ButtonIdx = AttackButtons.Find(AttackButton);

	// Get corresponding attack action
	if (!IsValid(AttackActions[ButtonIdx]))
	{
		UE_LOG(LogTemp, Error, TEXT("UCombatWidget::HandleAttackButtonClicked: Invalid AttackAction"));
		return;
	}

	UDA_ItemAction* AttackAction = AttackActions[ButtonIdx];
	HandleCombatActionRequested(AttackActions[ButtonIdx]);

}

void UCombatWidget::HandleAttackButtonHovered(UWBP_AttackBtn* AttackButton)
{

}

void UCombatWidget::HandleAttackButtonUnhovered(UWBP_AttackBtn* AttackButton)
{

}


void UCombatWidget::HandleCombatActionRequested(UDA_ItemAction* ItemAction)
{
	OnCombatActionRequestedDelegate.Broadcast(ItemAction);
}

void UCombatWidget::HighlightBorder(UBorder* BorderToHighlight, UBorder* BorderToUnhighlight)
{
	if (!IsValid(BorderToHighlight))
	{
		UE_LOG(LogTemp, Error, TEXT("UCombatWidget::HighlightBorder: Invalid BorderToHighlight"));
		return;
	}
	if (!IsValid(BorderToUnhighlight))
	{
		UE_LOG(LogTemp, Error, TEXT("UCombatWidget::HighlightBorder: Invalid BorderToUnhighlight"));
		return;
	}

	BorderToHighlight->SetBrushColor(HighlightedBorderBrushColor);
	BorderToUnhighlight->SetBrushColor(DefaultBorderBrushColor);
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
		UE_LOG(LogTemp, Error, TEXT("UCombatWidget::SetUpCombatantBindings: Invalid PlayerCharSheet"));
		return;
	}
	if (!IsValid(EnemyCharSheet))
	{
		UE_LOG(LogTemp, Error, TEXT("UCombatWidget::SetUpCombatantBindings: Invalid EnemyCharSheet"));
		return;
	}

	PlayerCharSheet->OnHpChangedDelegate.AddDynamic(this, &UCombatWidget::SetPlayerHpBarPercent);
	EnemyCharSheet->OnHpChangedDelegate.AddDynamic(this, &UCombatWidget::SetEnemyHpBarPercent);

}

void UCombatWidget::RemoveCombatantBindings()
{
	if (!IsValid(PlayerCharSheet))
	{
		UE_LOG(LogTemp, Error, TEXT("UCombatWidget::RemoveCombatantBindings: Invalid PlayerCharSheet"));
		return;
	}
	if (!IsValid(EnemyCharSheet))
	{
		UE_LOG(LogTemp, Error, TEXT("UCombatWidget::RemoveCombatantBindings: Invalid EnemyCharSheet"));
		return;
	}
	
	PlayerCharSheet->OnHpChangedDelegate.RemoveDynamic(this, &UCombatWidget::SetPlayerHpBarPercent);
	EnemyCharSheet->OnHpChangedDelegate.RemoveDynamic(this, &UCombatWidget::SetEnemyHpBarPercent);

}




