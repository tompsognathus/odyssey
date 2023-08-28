// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class UUIManager;
class UInventory;
class UEnhancedInputLocalPlayerSubsystem;

class ODYSSEY_API Utility
{
public:
	static APawn* GetPlayerPawn(UObject* Object);
	static UUIManager* GetUIManager(UObject* Object);
	static UInventory* GetInventory(UObject* Object);
	static UEnhancedInputLocalPlayerSubsystem* GetEnhancedInputLocalPlayerSubsystem(UObject* Object);

private:
	static UWorld* GetWorld(UObject* Object);



};
