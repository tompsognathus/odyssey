// Fill out your copyright notice in the Description page of Project Settings.

#include "Utility.h"
#include "UIManager.h"


Utility::Utility()
{
}

Utility::~Utility()
{
}



UUIManager* Utility::GetUIManager(UObject* Object)
{
	APawn* PlayerPawn = GetPlayerPawn(Object);
	if (!IsValid(PlayerPawn))
	{
		UE_LOG(LogTemp, Error, TEXT("Utility::GetUIManager() PlayerPawn is not valid"));
		return nullptr;
	}

	UActorComponent* UIManagerComponent = PlayerPawn->GetComponentByClass(UUIManager::StaticClass());
	if (!IsValid(UIManagerComponent))
	{
		UE_LOG(LogTemp, Error, TEXT("Utility::GetUIManager() UIManagerComponent is not valid"));
		return nullptr;
	}

	UUIManager* UIManager = Cast<UUIManager>(UIManagerComponent);
	if (!IsValid(UIManager))
	{
		UE_LOG(LogTemp, Error, TEXT("Utility::GetUIManager() UIManager is not valid"));
		return nullptr;
	}

	return UIManager;
}

APawn* Utility::GetPlayerPawn(UObject* Object)
{
	UWorld* World = Object->GetWorld();
	if (!IsValid(World))
	{
		UE_LOG(LogTemp, Error, TEXT("Utility::GetPlayerPawn() World is not valid"));
		return nullptr;
	}

	APlayerController* FirstPlayerController = World->GetFirstPlayerController();
	if (!IsValid(FirstPlayerController))
	{
		UE_LOG(LogTemp, Error, TEXT("Utility::GetPlayerPawn() FirstPlayerController is not valid"));
		return nullptr;
	}

	APawn* PlayerPawn = FirstPlayerController->GetPawn();
	if (!IsValid(PlayerPawn))
	{
		UE_LOG(LogTemp, Error, TEXT("Utility::GetPlayerPawn() PlayerPawn is not valid"));
		return nullptr;
	}

	return PlayerPawn;
}