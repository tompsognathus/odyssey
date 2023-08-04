// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "Cannon.generated.h"

UCLASS()
class ODYSSEY_API ACannon : public AActor, public IInteractable
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	void GetInputPromptWidgetComponent();

public:	
	// Sets default values for this actor's properties
	ACannon();

	virtual void DisplayInputPrompt_Implementation(bool IsVisible) override;
	virtual bool GetIsInteractable_Implementation() override;

	UFUNCTION(BlueprintCallable, Category = "Interactable")
	void SetIsInteractable(bool NewIsInteractable);

public:
	class UWidgetComponent* InputPromptWidgetComponent;

private:
	bool IsInteractable = true;
};
