// Fill out your copyright notice in the Description page of Project Settings.

#include "Utility.h"
#include "UIManager.h"
#include "Inventory.h"
#include "EnhancedInputSubsystems.h"

UUIManager* Utility::GetUIManager(UObject* Object)
{
	APawn* PlayerPawn = Utility::GetPlayerPawn(Object);
	if (!IsValid(PlayerPawn))
	{
		UE_LOG(LogTemp, Error, TEXT("Utility::GetUIManager: Invalid PlayerPawn"));
		return nullptr;
	}

	UActorComponent* UIManagerComponent = PlayerPawn->GetComponentByClass(UUIManager::StaticClass());
	if (!IsValid(UIManagerComponent))
	{
		UE_LOG(LogTemp, Error, TEXT("Utility::GetUIManager: Invalid UIManagerComponent"));
		return nullptr;
	}

	UUIManager* UIManager = Cast<UUIManager>(UIManagerComponent);
	if (!IsValid(UIManager))
	{
		UE_LOG(LogTemp, Error, TEXT("Utility::GetUIManager: Invalid UIManager"));
		return nullptr;
	}

	return UIManager;
}

UInventory* Utility::GetInventory(UObject* Object)
{
	APawn* PlayerPawn = Utility::GetPlayerPawn(Object);
	if (!IsValid(PlayerPawn))
	{
		UE_LOG(LogTemp, Error, TEXT("Utility::GetInventory: Invalid PlayerPawn"));
		return nullptr;
	}

	UActorComponent* InventoryComponent = PlayerPawn->GetComponentByClass(UInventory::StaticClass());
	if (!IsValid(InventoryComponent))
	{
		UE_LOG(LogTemp, Error, TEXT("Utility::GetInventory: Invalid InventoryComponent"));
		return nullptr;
	}

	UInventory* Inventory = Cast<UInventory>(InventoryComponent);
	if (!IsValid(Inventory))
	{
		UE_LOG(LogTemp, Error, TEXT("Utility::GetInventory: Invalid Inventory"));
		return nullptr;
	}

	return Inventory;
}

UEnhancedInputLocalPlayerSubsystem* Utility::GetEnhancedInputLocalPlayerSubsystem(UObject* Object)
{
	APawn* PlayerPawn = Utility::GetPlayerPawn(Object);
	if (!IsValid(PlayerPawn))
	{
		UE_LOG(LogTemp, Error, TEXT("Utility::GetEnhancedInputLocalPlayerSubsystem: Invalid PlayerPawn"));
		return nullptr;
	}
	 
	TObjectPtr<AController> Controller = PlayerPawn->GetController();
	if (!IsValid(Controller))
	{
		UE_LOG(LogTemp, Error, TEXT("Utility::GetEnhancedInputLocalPlayerSubsystem: Invalid Controller"));
		return nullptr;
	}

	TObjectPtr<APlayerController> PlayerController = Cast<APlayerController>(Controller);
	if (!IsValid(PlayerController))
	{
		UE_LOG(LogTemp, Error, TEXT("Utility::GetEnhancedInputLocalPlayerSubsystem: Invalid PlayerController"));
		return nullptr;
	}

	ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer();
	if (!IsValid(LocalPlayer))
	{
		UE_LOG(LogTemp, Error, TEXT("Utility::GetEnhancedInputLocalPlayerSubsystem: Invalid LocalPlayer"));
		return nullptr;
	}

	UEnhancedInputLocalPlayerSubsystem* LocalPlayerSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);
	if (!IsValid(LocalPlayerSubsystem))
	{
		UE_LOG(LogTemp, Error, TEXT("Utility::GetEnhancedInputLocalPlayerSubsystem: Invalid LocalPlayerSubsystem"));
		return nullptr;
	}

	return LocalPlayerSubsystem;
}

APawn* Utility::GetPlayerPawn(UObject* Object)
{
	UWorld* World = Object->GetWorld();
	if (!IsValid(World))
	{
		UE_LOG(LogTemp, Error, TEXT("Utility::GetPlayerPawn: Invalid World"));
		return nullptr;
	}

	APlayerController* FirstPlayerController = World->GetFirstPlayerController();
	if (!IsValid(FirstPlayerController))
	{
		UE_LOG(LogTemp, Error, TEXT("Utility::GetPlayerPawn:  FirstPlayerController is not valid"));
		return nullptr;
	}

	APawn* PlayerPawn = FirstPlayerController->GetPawn();
	if (!IsValid(PlayerPawn))
	{
		UE_LOG(LogTemp, Error, TEXT("Utility::GetPlayerPawn: Invalid PlayerPawn"));
		return nullptr;
	}

	return PlayerPawn;
}