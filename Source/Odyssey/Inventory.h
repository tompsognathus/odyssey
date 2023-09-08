// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "ItemNames.h"

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "ItemNames.h"

#include "Inventory.generated.h"

class UDA_Item;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ODYSSEY_API UInventory : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInventory();

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	int GetNumItems();

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void AddItem(UDA_Item* ItemToAdd, int NumToAdd);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void RemoveItem(UDA_Item* ItemToRemove, int AmountToRemove);

	// Getters
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	TArray<class UDA_Item*> GetItemRefArray() const { return ItemRefArray; }

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	TArray<int> GetItemCountArray() const { return ItemCountArray; }

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Inventory")
	int MaxInventorySize = 60;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory")
	TArray<UDA_Item*> ItemRefArray = TArray<UDA_Item*>();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Inventory")
	TArray<int> ItemCountArray = TArray<int>();

};
