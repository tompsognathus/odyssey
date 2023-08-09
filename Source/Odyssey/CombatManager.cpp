// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatManager.h"
#include "UIManager.h"

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
	}
	else { UE_LOG(LogTemp, Error, TEXT("Cannot find PlayerPawn in CombatManager BeginPlay")); }
}

void UCombatManager::StartNewRound()
{
	UE_LOG(LogTemp, Warning, TEXT("StartNewRound() called in CombatManager"));
	CombatRound += 1;

	

}


