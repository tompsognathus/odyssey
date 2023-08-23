// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CombatManager.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ODYSSEY_API UCombatManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCombatManager();

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void StartNewCombat(class ANPC* Enemy);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	class UUIManager* UIManager;
	class UCharSheet* PlayerCharSheet;
	class UCharSheet* EnemyCharSheet;
	class UCombatWidget* CombatWidget;

	TArray<UCharSheet*> TurnOrder;

	int CombatRound = 0;
	int CurrentTurnIdx = -1;
	void StartNewRound();
	void StartNextTurn();

	UFUNCTION()
	void PerformCombatAction(class UDA_ItemAction* Action);

	int RollD100();

public:
	UFUNCTION(BlueprintCallable, Category = "Combat")
	class UCharSheet* GetPlayerCharSheet() const { return PlayerCharSheet; }

	UFUNCTION(BlueprintCallable, Category = "Combat")
	class UCharSheet* GetEnemyCharSheet() const { return EnemyCharSheet; }
};
