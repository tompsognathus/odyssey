#pragma once

#include "CoreMinimal.h"
#include "ItemType.generated.h"

UENUM(BlueprintType)
enum class EItemType : uint8 {
    VE_None         UMETA(DisplayName = "None"),
    VE_Weapon       UMETA(DisplayName = "Weapon"),
    VE_QuestItem    UMETA(DisplayName = "Quest Item"),
};