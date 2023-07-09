#pragma once

#include "Interactable.generated.h"

UINTERFACE(MinimalApi)
class UInteractable : public UInterface
{
    GENERATED_BODY()
};

class ODYSSEY_API IInteractable
{
    GENERATED_BODY()

public:
    // interface declaration for OnActorClicked function
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interactable")
    void EnteredInteractionZone(AActor* InteractableActor);

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interactable")
    void LeftInteractionZone(AActor* InteractableActor);

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interactable")
    void InteractRequest(AActor* InteractableActor);
};