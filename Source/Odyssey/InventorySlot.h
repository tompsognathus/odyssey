#pragma once

#include "CoreMinimal.h"

#include "ItemNames.h"
#include "DA_Item.h"

#include "InventorySlot.generated.h"

USTRUCT(BlueprintType)
struct FInventorySlot
{
    GENERATED_BODY()

public:
    // Reference to Item data asset
    UDA_Item* DA_ItemRef;

    // The amount of this item in the inventory
    int Quantity;

};