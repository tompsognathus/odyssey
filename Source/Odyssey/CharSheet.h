// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharSheet.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGoldChangedSignature, int32, NewGoldAmount);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHpChangedSignature, float, NewHpPercent);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ODYSSEY_API UCharSheet : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCharSheet();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	UFUNCTION(BlueprintCallable, Category = "CharSheet")
	void AddGold(int GoldAmount);

	UFUNCTION(BlueprintCallable, Category = "CharSheet")
	void AddHp(int HpAmount);

	UFUNCTION(BlueprintCallable, Category = "CharSheet")
	int GetHpNormalizedPercent() const { return Hp / MaxHp; }

	UFUNCTION(BlueprintCallable, Category = "CharSheet")
	void TakeDamage(int DamageAmount);

	// Delegates
	UPROPERTY(BlueprintAssignable, Category = "CharSheet")
	FOnGoldChangedSignature OnGoldChangedDelegate;

	UPROPERTY(BlueprintAssignable, Category = "CharSheet")
	FOnHpChangedSignature OnHpChangedDelegate;

	// Getters
	int GetInitiativeBase() const { return InitiativeBase; }
	float GetDamageMultiplier() const { return DamageMultiplier; }
	int GetHp() const { return Hp; }
	class UDA_Item* GetActiveWeapon() const { return ActiveWeapon; }

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharSheet")
	class UDA_Item* ActiveWeapon;

	// Stats
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Charsheet")
	float DamageMultiplier = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharSheet")
	int InitiativeBase = 50;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharSheet")
	int MaxHp = 100;

private:
	int Gold = 50;
	int Hp = 100;
	
	int Agility = 0;

};
