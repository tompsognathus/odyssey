// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatManager.h"
#include "UIManager.h"
#include "CharSheet.h"
#include "NPC.h"
#include "DA_Item.h"
#include "CombatWidget.h"

// Sets default values for this component's properties
UCombatManager::UCombatManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}

// Called when the game starts
void UCombatManager::BeginPlay()
{
	Super::BeginPlay();
	
	APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (PlayerPawn)
	{
		// Get UI Manager component
		UIManager = Cast<UUIManager>(PlayerPawn->GetComponentByClass(UUIManager::StaticClass()));

		if (!UIManager) { UE_LOG(LogTemp, Error, TEXT("Cannot find UIManager in CombatManager BeginPlay")); }
	
		// Get reference to player CharSheet
		PlayerCharSheet = Cast<UCharSheet>(PlayerPawn->GetComponentByClass(UCharSheet::StaticClass()));

		if (!PlayerCharSheet) { UE_LOG(LogTemp, Error, TEXT("Cannot find PlayerCharSheet in CombatManager BeginPlay")); }

		// Bind to combat widget's combat action request delegate
		UUserWidget* CombatUserWidget = UIManager->GetCombatWidgetInstance();
		if (CombatUserWidget)
		{
			CombatWidget = Cast<UCombatWidget>(CombatUserWidget);
			if (CombatWidget)
			{
				CombatWidget->OnCombatActionRequestedDelegate.AddUniqueDynamic(this, &UCombatManager::PerformCombatAction);

			} else { UE_LOG(LogTemp, Error, TEXT("Cannot cast CombatUserWidget to CombatWidget in CombatManager BeginPlay")); }
		} else { UE_LOG(LogTemp, Error, TEXT("Cannot find CombatWidget in CombatManager BeginPlay")); }
	} else { UE_LOG(LogTemp, Error, TEXT("Cannot find PlayerPawn in CombatManager BeginPlay")); }
}

void UCombatManager::StartNewCombat(class ANPC* Enemy)
{
	CombatRound = 0;

	// Get reference to enemy CharSheet
	EnemyCharSheet = Cast<UCharSheet>(Enemy->GetComponentByClass(UCharSheet::StaticClass()));

	if (!EnemyCharSheet) 
	{ 
		UE_LOG(LogTemp, Error, TEXT("Cannot find EnemyCharSheet in CombatManager StartNewCombat"));
		return;
	}
	if (!PlayerCharSheet)
	{
		UE_LOG(LogTemp, Error, TEXT("Cannot find PlayerCharSheet in CombatManager StartNewCombat"));
		return;
	}

	// Set up player action buttons
	UDA_Item* ActiveWeapon = PlayerCharSheet->GetActiveWeapon();
	if (!ActiveWeapon) { UE_LOG(LogTemp, Error, TEXT("Cannot find ActiveWeapon in CombatManager, StartNewCombat")); }

	UIManager->UpdatePlayerCombatActionBtns(ActiveWeapon->ItemActions);

	// Set up Bindings
	if (CombatWidget)
	{
		CombatWidget->SetUpCombatantBindings(PlayerCharSheet, EnemyCharSheet);
	
	} else { UE_LOG(LogTemp, Error, TEXT("Cannot find CombatWidget in CombatManager, StartNewCombat")); }

	// Roll initiative
	int PlayerInitiative = RollD100() + PlayerCharSheet->GetInitiativeBase();
	int EnemyInitiative = RollD100() + EnemyCharSheet->GetInitiativeBase();

	// Check for initiative
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

	// Set enemy info
	UIManager->SetEnemyInfo(Enemy->GetAvatarMaterial(), Enemy->GetDisplayName());
	UIManager->SetPlayerHpPercent(PlayerCharSheet->GetHpNormalizedPercent());
	UIManager->SetEnemyHpPercent(EnemyCharSheet->GetHpNormalizedPercent());

	// Start combat
	StartNextTurn();
}

void UCombatManager::StartNewRound()
{
	UE_LOG(LogTemp, Warning, TEXT("StartNewRound() called in CombatManager"));
	CombatRound += 1;

	UIManager->SetCurrentRoundText(CombatRound);

	// Disable buttons. We enable them again if/when it's the player's turn
	UIManager->SetCombatActionBtnsEnabled(false);
}

void UCombatManager::StartNextTurn()
{
	CurrentTurnIdx += 1;
	CurrentTurnIdx = CurrentTurnIdx % TurnOrder.Num();

	if (CurrentTurnIdx == 0)
	{
		// Start new round
		StartNewRound();
	}

	// Take turn
	UCharSheet* CurrentTurnCharSheet = TurnOrder[CurrentTurnIdx];

	if (CurrentTurnCharSheet == PlayerCharSheet)
	{
		// Enable buttons
		UIManager->SetCombatActionBtnsEnabled(true);
		
		UE_LOG(LogTemp, Warning, TEXT("Player turn"));

		// We've activated the buttons and are now waitng for the player to select an action,
		// which will end up triggering this function again unless we reach the end of the combat
		return;
	}
	else
	{
		// Enemy turn
		UIManager->SetCombatActionBtnsEnabled(false);

		UE_LOG(LogTemp, Warning, TEXT("Enemy turn"));

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
		
		UE_LOG(LogTemp, Warning, TEXT("Combat over"));
		return;
	}
}

void UCombatManager::PerformCombatAction(UDA_ItemAction* CombatAction)
{
	// Deal damage to enemy
	int DamageBase = CombatAction->ActionDamageBase;
	float DamageMultiplier = PlayerCharSheet->GetDamageMultiplier();

	float Damage = DamageBase * DamageMultiplier;

	EnemyCharSheet->TakeDamage(Damage);

	// Finally move on to the next turn
	StartNextTurn();
}

int UCombatManager::RollD100()
{
	return FMath::RandRange(1, 100);
}



