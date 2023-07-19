#pragma once

#include "CoreMinimal.h"

#include "ItemNames.h"

#include "InventorySlot.generated.h"

USTRUCT(BlueprintType)
struct FInventorySlot
{
    GENERATED_BODY()

    // Blueprint reference to actor
    AActor* ItemActorRef;

    // Item name. To create a new name, you'll have to add an entry to the EItemNames enum in ItemNames.h
    EItemNames ItemName;

    // Item description
    FString ItemDescription;

    // The amount of this item in the inventory
    int CurrentStackSize;

    // The maximum amount of this item in the inventory
    int MaxStackSize;
};