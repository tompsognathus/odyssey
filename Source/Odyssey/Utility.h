// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class UUIManager;
class UInventory;
class UEnhancedInputLocalPlayerSubsystem;
class UCombatManager;
class AOdysseyCharacter;

class ODYSSEY_API Utility
{
public:
	static APawn* GetPlayerPawn(UObject* Object);
	static AOdysseyCharacter* GetPlayerCharacter(UObject* Object);
	static UUIManager* GetUIManager(UObject* Object);
	static UInventory* GetInventory(UObject* Object);
	static UEnhancedInputLocalPlayerSubsystem* GetEnhancedInputLocalPlayerSubsystem(UObject* Object);
	static UCombatManager* GetCombatManager(UObject* Object);
	static APlayerController* GetFirstPlayerController(UObject* Object);
};
