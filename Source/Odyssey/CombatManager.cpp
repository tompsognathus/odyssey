// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatManager.h"
#include "UIManager.h"
#include "CharSheet.h"
#include "NPC.h"
#include "DA_Item.h"
#include "CombatWidget.h"

UCombatManager::UCombatManager()
{

}

void UCombatManager::BeginPlay()
{
	Super::BeginPlay();
	
	UWorld* World = GetWorld();
	if (!IsValid(World)) 
	{ 
		UE_LOG(LogTemp, Error, TEXT("Cannot find World in CombatManager, BeginPlay")); 
		return; 
	}

	APlayerController* FirstPlayerController = World->GetFirstPlayerController();
	if (!IsValid(FirstPlayerController))
	{
		UE_LOG(LogTemp, Error, TEXT("Cannot find PlayerController in CombatManager, BeginPlay"));
		return;
	}

	APawn* PlayerPawn = FirstPlayerController->GetPawn();
	if (!IsValid(PlayerPawn))
	{
		UE_LOG(LogTemp, Error, TEXT("Cannot find PlayerPawn in CombatManager, BeginPlay"));
		return;
	}

	UActorComponent* UIManagerActorComponent = PlayerPawn->GetComponentByClass(UUIManager::StaticClass());
	if (!IsValid(UIManagerActorComponent)) 
	{ 
		UE_LOG(LogTemp, Error, TEXT("Cannot find UIManagerActorComponent in CombatManager BeginPlay")); 
		return;
	}

	UIManager = Cast<UUIManager>(UIManagerActorComponent);
	if (!IsValid(UIManager)) 
	{ 
		UE_LOG(LogTemp, Error, TEXT("Cannot cast UIManagerActorComponent to UIManager in CombatManager BeginPlay")); 
		return;
	}

	UActorComponent* PlayerCharSheetActorComponent = PlayerPawn->GetComponentByClass(UCharSheet::StaticClass());
	if (!IsValid(PlayerCharSheetActorComponent)) 
	{ 
		UE_LOG(LogTemp, Error, TEXT("Cannot find PlayerCharSheetActorComponent in CombatManager BeginPlay")); 
		return;
	}

	PlayerCharSheet = Cast<UCharSheet>(PlayerCharSheetActorComponent);
	if (!IsValid(PlayerCharSheet)) 
	{ 
		UE_LOG(LogTemp, Error, TEXT("Cannot find PlayerCharSheet in CombatManager BeginPlay")); 
		return;
	}

	UUserWidget* CombatUserWidget = UIManager->GetCombatWidgetInstance();
	if (!IsValid(CombatUserWidget))
	{
		UE_LOG(LogTemp, Error, TEXT("Cannot find CombatUserWidget in CombatManager BeginPlay"));
		return;
	}

	CombatWidget = Cast<UCombatWidget>(CombatUserWidget);
	if (!IsValid(CombatWidget))
	{
		UE_LOG(LogTemp, Error, TEXT("Cannot cast CombatUserWidget to CombatWidget in CombatManager BeginPlay"));
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
		UE_LOG(LogTemp, Error, TEXT("Cannot find EnemyCharSheetActorComponent in CombatManager, StartNewCombat")); 
		return;
	}

	EnemyCharSheet = Cast<UCharSheet>(EnemyCharSheetActorComponent);
	if (!IsValid(EnemyCharSheet)) 
	{ 
		UE_LOG(LogTemp, Error, TEXT("Cannot find EnemyCharSheet in CombatManager, StartNewCombat"));
		return;
	}

	// PlayerCharSheet doesn't change, so we only set it in BeginPlay and only need to make sure it's valid here
	if (!IsValid(PlayerCharSheet))
	{
		UE_LOG(LogTemp, Error, TEXT("Cannot find PlayerCharSheet in CombatManager, StartNewCombat"));
		return;
	}

	// Set up player action buttons
	TObjectPtr<UDA_Item> ActiveWeapon = PlayerCharSheet->GetActiveWeapon();
	if (!IsValid(ActiveWeapon)) { 
		UE_LOG(LogTemp, Error, TEXT("Cannot find ActiveWeapon in CombatManager, StartNewCombat")); 
		return;
	}

	TArray<UDA_ItemAction*> ActiveWeaponActions = ActiveWeapon->ItemActions;
	UIManager->UpdatePlayerCombatActionButtons(ActiveWeaponActions);

	if (!IsValid(CombatWidget))
	{
		UE_LOG(LogTemp, Error, TEXT("Cannot find CombatWidget in CombatManager, StartNewCombat"));
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
		UE_LOG(LogTemp, Error, TEXT("Cannot find UIManager in CombatManager, StartNewRound"));
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
		UE_LOG(LogTemp, Error, TEXT("Cannot find PlayerCharSheet in CombatManager, StartNextTurn"));
		return;
	}
	if (!IsValid(EnemyCharSheet))
	{
		UE_LOG(LogTemp, Error, TEXT("Cannot find EnemyCharSheet in CombatManager, StartNextTurn"));
		return;
	}
	if (!IsValid(UIManager))
	{
		UE_LOG(LogTemp, Error, TEXT("Cannot find UIManager in CombatManager, StartNextTurn"));
		return;
	}
	if (!IsValid(CombatWidget))
	{
		UE_LOG(LogTemp, Error, TEXT("Cannot find CombatWidget in CombatManager, StartNextTurn"));
		return;
	}
	
	CurrentTurnIdx += 1;
	int NumTurns = TurnOrder.Num();
	if (NumTurns <= 0)
	{
		UE_LOG(LogTemp, Error, TEXT("TurnOrder contains no turns in CombatManager, StartNextTurn"));
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

		UIManager->SetCombatActionBtnsEnabled(true);
		
		// We've activated the buttons and are now waitng for the player to select an action,
		// which will end up triggering this function again unless we reach the end of the combat
		return;
	}
	else
	{
		// Enemy turn
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
		UE_LOG(LogTemp, Error, TEXT("Cannot find PlayerCharSheet in CombatManager, PerformCombatAction"));
		return;
	}
	if (!IsValid(EnemyCharSheet))
	{
		UE_LOG(LogTemp, Error, TEXT("Cannot find EnemyCharSheet in CombatManager, PerformCombatAction"));
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



