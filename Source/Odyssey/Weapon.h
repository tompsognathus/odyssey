// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Weapon.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ODYSSEY_API UWeapon : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWeapon();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	float GetWeaponDamage() const { return WeaponDamage; }

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	float WeaponDamage = 1.0f;


		
};
