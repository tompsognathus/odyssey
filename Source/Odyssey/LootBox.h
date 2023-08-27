// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LootBox.generated.h"

class UDA_Item;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ODYSSEY_API ULootBox : public UActorComponent
{
	GENERATED_BODY()

public:	
	ULootBox();

	TArray<UDA_Item*> GetItemRefArray() const { return ItemRefArray; }
	TArray<int> GetItemCountArray() const { return ItemCountArray; }

	void RemoveItem(UDA_Item* ItemToRemove, int AmountToRemove);
	void AddItem(UDA_Item* ItemToAdd, int NumToAdd);

public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LootBox")
	int GoldAmount = 0;


protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LootBox")
	TArray<UDA_Item*> ItemRefArray = TArray<UDA_Item*>();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LootBox")
	TArray<int> ItemCountArray = TArray<int>();



};
