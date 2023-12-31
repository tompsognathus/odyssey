// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "Teleporter.generated.h"

class UWidgetComponent;

UCLASS()
class ODYSSEY_API ATeleporter : public AActor, public IInteractable
{
	GENERATED_BODY()


public:	
	ATeleporter();

	virtual void DisplayInputPrompt_Implementation(bool IsVisible) override;
	virtual bool GetIsInteractable_Implementation() override;

	UFUNCTION(BlueprintCallable, Category = "Interactable")
	void SetIsInteractable(bool NewIsInteractable);


protected:
	virtual void BeginPlay() override;
	void GetInputPromptWidgetComponent();


private:
	bool IsInteractable = true;
	UWidgetComponent* InputPromptWidgetComponent;
};
