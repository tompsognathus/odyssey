// Fill out your copyright notice in the Description page of Project Settings.


#include "CharSheet.h"
#include "Weapon.h"

// Sets default values for this component's properties
UCharSheet::UCharSheet()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UCharSheet::BeginPlay()
{
	Super::BeginPlay();

	// Request HUD update
	OnGoldChangedDelegate.Broadcast(Gold);
	OnHpChangedDelegate.Broadcast(100);

	// Get active weapon
	ActiveWeapon = GetOwner()->FindComponentByClass<UWeapon>();
}


void UCharSheet::AddGold(int GoldAmount)
{
	Gold += GoldAmount;

	// Request HUD update 
	OnGoldChangedDelegate.Broadcast(Gold);
}

void UCharSheet::AddHp(int HpAmount)
{
	Hp += HpAmount;

	Hp = std::min(Hp, MaxHp);
	Hp = std::max(Hp, 0);

	float HpPercentage =  (int32)((float)Hp / (float)MaxHp * 100.0f);
	// Request HUD update
	OnHpChangedDelegate.Broadcast(HpPercentage);
}


void UCharSheet::TakeDamage(int DamageAmount)
{
	AddHp(-DamageAmount);
}

