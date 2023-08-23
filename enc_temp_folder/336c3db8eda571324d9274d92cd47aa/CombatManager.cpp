// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatManager.h"
#include "UIManager.h"
#include "CharSheet.h"
#include "NPC.h"

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
	}
	else
	{
		// Enemy turn
		UIManager->SetCombatActionBtnsEnabled(false);

		UE_LOG(LogTemp, Warning, TEXT("Enemy turn"));
	}
}

int UCombatManager::RollD100()
{
	return FMath::RandRange(1, 100);
}



