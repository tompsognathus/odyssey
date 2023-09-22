// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharSheet.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGoldChangedSignature, int32, NewGoldAmount);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHpChangedSignature, float, NewHpPercent);

class UDA_Item;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ODYSSEY_API UCharSheet : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCharSheet();

	UFUNCTION(BlueprintCallable, Category = "CharSheet")
	void AddGold(int GoldAmount);

	UFUNCTION(BlueprintCallable, Category = "CharSheet")
	void AddHp(int HpAmount);

	UFUNCTION(BlueprintCallable, Category = "CharSheet")
	int GetHpNormalizedPercent() const { return Hp / MaxHp; }

	UFUNCTION(BlueprintCallable, Category = "CharSheet")
	void TakeDamage(int DamageAmount);

	// Getters
	int GetInitiativeBase() const { return InitiativeBase; }
	float GetDamageMultiplier() const { return DamageMultiplier; }
	int GetHp() const { return Hp; }
	UDA_Item* GetActiveWeapon() const { return ActiveWeapon; }

public:
	// Delegates
	UPROPERTY(BlueprintAssignable, Category = "CharSheet")
	FOnGoldChangedSignature OnGoldChangedDelegate;

	UPROPERTY(BlueprintAssignable, Category = "CharSheet")
	FOnHpChangedSignature OnHpChangedDelegate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharSheet")
	UDA_Item* ActiveWeapon;


protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharSheet")
	int MaxHp = 100;

	// Stats
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Charsheet")
	float DamageMultiplier = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharSheet")
	int InitiativeBase = 50;

private:
	int Gold = 50;
	int Hp = 100;
	

};
