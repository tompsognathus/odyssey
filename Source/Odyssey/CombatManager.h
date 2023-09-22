// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CombatManager.generated.h"

class UUIManager;
class UCharSheet;
class UCombatWidget;
class UDA_ItemAction;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ODYSSEY_API UCombatManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCombatManager();

	// Getters
	UFUNCTION(BlueprintCallable, Category = "Combat")
	UCharSheet* GetPlayerCharSheet() const { return PlayerCharSheet; }

	UFUNCTION(BlueprintCallable, Category = "Combat")
	UCharSheet* GetEnemyCharSheet() const { return EnemyCharSheet; }

	UFUNCTION(BlueprintCallable, Category = "Combat")
	TArray<UCharSheet*> GetTurnOrder() const { return TurnOrder; }

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void StartNewCombat(class ANPC* Enemy);

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void StartNewRound();
	
	UFUNCTION(BlueprintCallable, Category = "Combat")
	int RollD100();

protected:
	virtual void BeginPlay() override;


private:

	UFUNCTION()
	void PerformCombatAction(UDA_ItemAction* Action);

private:
	UUIManager* UIManager;
	UCharSheet* PlayerCharSheet;
	UCharSheet* EnemyCharSheet;
	UCombatWidget* CombatWidget;

	TArray<UCharSheet*> TurnOrder = TArray<UCharSheet*>();

	int CombatRound = 0;
	int CurrentTurnIdx = -1;

};
