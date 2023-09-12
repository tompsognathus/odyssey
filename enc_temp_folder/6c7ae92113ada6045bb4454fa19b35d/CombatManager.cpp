// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatManager.h"
#include "UIManager.h"
#include "CharSheet.h"
#include "NPC.h"
#include "DA_Item.h"
#include "CombatWidget.h"
#include "Utility.h"

UCombatManager::UCombatManager()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UCombatManager::BeginPlay()
{
	Super::BeginPlay();
	
	UIManager = Utility::GetUIManager(this);
	if (!IsValid(UIManager)) 
	{ 
		UE_LOG(LogTemp, Error, TEXT("UCombatManager::BeginPlay: Cannot get UIManager")); 
		return;
	}

	APawn* PlayerPawn = Utility::GetPlayerPawn(this);
	if (!IsValid(PlayerPawn))
	{
		UE_LOG(LogTemp, Error, TEXT("UCombatManager::BeginPlay: Cannot get PlayerPawn"));
		return;
	}

	UActorComponent* PlayerCharSheetActorComponent = PlayerPawn->GetComponentByClass(UCharSheet::StaticClass());
	if (!IsValid(PlayerCharSheetActorComponent)) 
	{ 
		UE_LOG(LogTemp, Error, TEXT("UCombatManager::BeginPlay: Cannot find PlayerCharSheetActorComponent")); 
		return;
	}

	PlayerCharSheet = Cast<UCharSheet>(PlayerCharSheetActorComponent);
	if (!IsValid(PlayerCharSheet)) 
	{ 
		UE_LOG(LogTemp, Error, TEXT("UCombatManager::BeginPlay: Cannot find PlayerCharSheet")); 
		return;
	}

	UUserWidget* CombatUserWidget = UIManager->GetCombatWidgetInstance();
	if (!IsValid(CombatUserWidget))
	{
		UE_LOG(LogTemp, Error, TEXT("UCombatManager::BeginPlay: Cannot find CombatUserWidget"));
		return;
	}

	CombatWidget = Cast<UCombatWidget>(CombatUserWidget);
	if (!IsValid(CombatWidget))
	{
		UE_LOG(LogTemp, Error, TEXT("UCombatManager::BeginPlay: Cannot cast CombatUserWidget to CombatWidget"));
		return;
	}

	CombatWidget->OnCombatActionRequestedDelegate.AddUniqueDynamic(this, &UCombatManager::PerformCombatAction);
	
}

void UCombatManager::StartNewCombat(ANPC* Enemy)
{
	CombatRound = 0;

	UActorComponent* EnemyCharSheetActorComponent = Enemy->GetComponentByClass(UCharSheet::StaticClass());
	if (!IsValid(EnemyCharSheetActorComponent)) 
	{ 
		UE_LOG(LogTemp, Error, TEXT("UCombatManager::StartNewCombat: Cannot find EnemyCharSheetActorComponent")); 
		return;
	}

	EnemyCharSheet = Cast<UCharSheet>(EnemyCharSheetActorComponent);
	if (!IsValid(EnemyCharSheet)) 
	{ 
		UE_LOG(LogTemp, Error, TEXT("UCombatManager::StartNewCombat: Cannot find EnemyCharSheet"));
		return;
	}

	// PlayerCharSheet doesn't change, so we only set it in BeginPlay and only need to make sure it's valid here
	if (!IsValid(PlayerCharSheet))
	{
		UE_LOG(LogTemp, Error, TEXT("UCombatManager::StartNewCombat: Cannot find PlayerCharSheet"));
		return;
	}

	// Set up player action buttons
	TObjectPtr<UDA_Item> ActiveWeapon = PlayerCharSheet->GetActiveWeapon();
	if (!IsValid(ActiveWeapon)) { 
		UE_LOG(LogTemp, Error, TEXT("UCombatManager::StartNewCombat: Cannot find ActiveWeapon")); 
		return;
	}

	TArray<UDA_ItemAction*> ActiveWeaponActions = ActiveWeapon->ItemActions;
	UIManager->UpdatePlayerCombatActionButtons(ActiveWeaponActions);

	if (!IsValid(CombatWidget))
	{
		UE_LOG(LogTemp, Error, TEXT("UCombatManager::StartNewCombat: Cannot find CombatWidget"));
		return;
	}
	CombatWidget->SetUpCombatantBindings(PlayerCharSheet, EnemyCharSheet);
	
	// Figure out initiative order
	int PlayerInitiative = RollD100() + PlayerCharSheet->GetInitiativeBase();
	int EnemyInitiative = RollD100() + EnemyCharSheet->GetInitiativeBase();

	if (PlayerInitiative >= EnemyInitiative)
	{
		TurnOrder.Add(PlayerCharSheet);
		TurnOrder.Add(EnemyCharSheet);
	}
	else
	{
		TurnOrder.Add(EnemyCharSheet);
		TurnOrder.Add(PlayerCharSheet);
	}

	// Update UI with player and enemy details
	UIManager->SetEnemyInfo(Enemy->GetAvatarMaterial(), Enemy->GetDisplayName());
	UIManager->SetPlayerHpPercent(PlayerCharSheet->GetHpNormalizedPercent());
	UIManager->SetEnemyHpPercent(EnemyCharSheet->GetHpNormalizedPercent());

	// Start combat
	StartNextTurn();
}

void UCombatManager::StartNewRound()
{
	CombatRound += 1;

	if (!IsValid(UIManager))
	{
		UE_LOG(LogTemp, Error, TEXT("UCombatManager::StartNewRound: Cannot find UIManager"));
		return;
	}
	UIManager->SetCurrentRoundText(CombatRound);

	// Disable buttons. We enable them again if/when it's the player's turn
	UIManager->SetCombatActionBtnsEnabled(false);
}

void UCombatManager::StartNextTurn()
{
	if (!IsValid(PlayerCharSheet))
	{
		UE_LOG(LogTemp, Error, TEXT("UCombatManager::StartNextTurn: Cannot find PlayerCharSheet"));
		return;
	}
	if (!IsValid(EnemyCharSheet))
	{
		UE_LOG(LogTemp, Error, TEXT("UCombatManager::StartNextTurnCannot find EnemyCharSheet"));
		return;
	}
	if (!IsValid(UIManager))
	{
		UE_LOG(LogTemp, Error, TEXT("UCombatManager::StartNextTurn: Cannot find UIManager"));
		return;
	}
	if (!IsValid(CombatWidget))
	{
		UE_LOG(LogTemp, Error, TEXT("UCombatManager::StartNextTurn: Cannot find CombatWidget"));
		return;
	}
	
	CurrentTurnIdx += 1;
	int NumTurns = TurnOrder.Num();
	if (NumTurns <= 0)
	{
		UE_LOG(LogTemp, Error, TEXT("UCombatManager::StartNextTurn: TurnOrder contains no turns"));
		return;
	}

	CurrentTurnIdx = CurrentTurnIdx % TurnOrder.Num();

	if (CurrentTurnIdx == 0)
	{
		StartNewRound();
	}

	// Take either a player or enemy turn
	UCharSheet* CurrentTurnCharSheet = TurnOrder[CurrentTurnIdx];

	if (CurrentTurnCharSheet == PlayerCharSheet)
	{
		CombatWidget->HighlightPlayerBorder();
		UIManager->SetCombatActionBtnsEnabled(true);
		
		// We've activated the buttons and are now waitng for the player to select an action,
		// which will end up triggering this function again unless we reach the end of the combat
		return;
	}
	else
	{
		// Enemy turn
		CombatWidget->HighlightEnemyBorder();
		UIManager->SetCombatActionBtnsEnabled(false);

		int EnemyDamageBase = RollD100();
		float EnemyDamageMultiplier = CurrentTurnCharSheet->GetDamageMultiplier();

		float EnemyDamage = EnemyDamageBase * EnemyDamageMultiplier;

		// Deal damage to player
		PlayerCharSheet->TakeDamage(EnemyDamage);
	}

	if (PlayerCharSheet->GetHp() > 0 && EnemyCharSheet->GetHp() > 0)
	{
		StartNextTurn();
	}
	else
	{
		CombatWidget->RemoveCombatantBindings();
		// Return to game
		UIManager->DisplayHUDWidgetOnly();
		return;
	}
}

void UCombatManager::PerformCombatAction(UDA_ItemAction* CombatAction)
{
	if (!IsValid(PlayerCharSheet))
	{
		UE_LOG(LogTemp, Error, TEXT("UCombatManager::StartNextTurn: Cannot find PlayerCharSheet"));
		return;
	}
	if (!IsValid(EnemyCharSheet))
	{
		UE_LOG(LogTemp, Error, TEXT("UCombatManager::StartNextTurn: Cannot find EnemyCharSheet"));
		return;
	}

	// Deal damage to enemy
	int DamageBase = CombatAction->ActionDamageBase;
	float DamageMultiplier = PlayerCharSheet->GetDamageMultiplier();
	float Damage = DamageBase * DamageMultiplier;
	EnemyCharSheet->TakeDamage(Damage);

	StartNextTurn();
}

int UCombatManager::RollD100()
{
	return FMath::RandRange(1, 100);
}



