// Fill out your copyright notice in the Description page of Project Settings.


#include "CharSheet.h"

UCharSheet::UCharSheet()
{

}

void UCharSheet::BeginPlay()
{
	Super::BeginPlay();

	// Request HUD update
	OnGoldChangedDelegate.Broadcast(Gold);
	OnHpChangedDelegate.Broadcast(100);

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

	float NormalizedHpPercentage = (float)Hp / (float)MaxHp;

	// Request HUD update
	OnHpChangedDelegate.Broadcast(NormalizedHpPercentage);
}


void UCharSheet::TakeDamage(int DamageAmount)
{
	AddHp(-DamageAmount);
}

