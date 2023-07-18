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
    void EnteredInteractionZone();

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interactable")
    void LeftInteractionZone();

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interactable")
    void InteractRequest();

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interactable")
    void Highlight(bool IsHighlighted);

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interactable")
    void DisplayInputPrompt(bool IsVisible);

    UFUNCTION (BlueprintNativeEvent, BlueprintCallable, Category = "Interactable")
    bool GetIsInteractable();

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interactable")
    TArray<UObject*> Loot();
};