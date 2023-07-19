#pragma once

#include "CoreMinimal.h"
#include "ItemNames.generated.h"

UENUM(BlueprintType)
enum class EItemNames : uint8 {
    VE_None       UMETA(DisplayName = "None"),
    VE_Sword       UMETA(DisplayName = "Sword"),
    VE_Bow        UMETA(DisplayName = "Bow"),
    VE_Axe        UMETA(DisplayName = "Axe"),
};