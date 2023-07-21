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

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void RemoveFromInventory(UDA_Item* ItemToRemove);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	int GetInventorySize();

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	TArray<class UDA_Item*> GetItemRefArray() const { return ItemRefArray; }

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	TArray<int> GetItemStackSizes() const { return ItemCountArray; }

public:

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Inventory")
	int MaxInventorySize = 60;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory")
	TArray<class UDA_Item*> ItemRefArray;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Inventory")
	TArray<int> ItemCountArray;
};
