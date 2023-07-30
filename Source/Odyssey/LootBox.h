// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LootBox.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ODYSSEY_API ULootBox : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULootBox();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	TArray<class UDA_Item*> GetItemRefArray() const { return LootableItemRefArray; }

	TArray<int> GetItemCountArray() const { return LootableItemCountArray; }

	void RemoveItem(class UDA_Item* ItemToRemove, int AmountToRemove);

	int AddSlotContentsToLootBoxGrid(class UWBP_InventorySlot* InventorySlot);

	int GetMaxInventorySize() const { return MaxLootBoxSize; }

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LootBox")
	int GoldAmount = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LootBox")
	int MaxLootBoxSize = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LootBox")
	int NumSlotColumns = 5;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LootBox")
	TArray<class UDA_Item*> LootableItemRefArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LootBox")
	TArray<int> LootableItemCountArray;



};
