// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "ItemNames.h"

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "ItemNames.h"

#include "Inventory.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ODYSSEY_API UInventory : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventory();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool AddToInventory(class UDA_Item* ItemToAdd);

	void RemoveFromInventory(UDA_Item* ItemToRemove);

	int GetInventorySize();

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory")
	TArray<AActor*> InventoryItemActors;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int MaxInventorySize = 60;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<struct FInventorySlot> InventorySlots;


};
