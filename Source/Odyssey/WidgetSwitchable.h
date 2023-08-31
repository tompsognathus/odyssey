#pragma once

#include "WidgetSwitchable.generated.h"

UINTERFACE(MinimalApi)
class UWidgetSwitchable : public UInterface
{
    GENERATED_BODY()
};

class ODYSSEY_API IWidgetSwitchable
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interactable")
    void PrepareToDisplay();

};