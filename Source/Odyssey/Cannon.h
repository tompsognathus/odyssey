// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "Cannon.generated.h"

class UWidgetComponent;

UCLASS()
class ODYSSEY_API ACannon : public AActor, public IInteractable
{
	GENERATED_BODY()


public:	
	ACannon();

	/***** Interactable Interface Functions *****/
	virtual void DisplayInputPrompt_Implementation(bool IsVisible) override;
	virtual bool GetIsInteractable_Implementation() override;

	UFUNCTION(BlueprintCallable, Category = "Interactable")
	void SetIsInteractable(bool NewIsInteractable);

public:
	UWidgetComponent* InputPromptWidgetComponent;


protected:
	virtual void BeginPlay() override;


private:
	void GetInputPromptWidgetComponent();

private:
	bool IsInteractable = true;
};
