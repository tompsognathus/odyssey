// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "F_InventorySlot.generated.h"

USTRUCT(BlueprintType)
struct F_InventorySlot
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, Category = "InventorySlot")
	FString ItemName;

	UPROPERTY(BlueprintReadWrite, Category = "InventorySlot")
	int Quantity;
};
