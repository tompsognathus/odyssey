// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class UUIManager;

class ODYSSEY_API Utility
{
public:
	Utility();
	~Utility();

	static UUIManager* GetUIManager(UObject* Object);
	static APawn* GetPlayerPawn(UObject* Object);

private:
	static UWorld* GetWorld(UObject* Object);



};
