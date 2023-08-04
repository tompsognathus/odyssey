// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "Teleporter.generated.h"

UCLASS()
class ODYSSEY_API ATeleporter : public AActor, public IInteractable
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	void GetInputPromptWidgetComponent();

public:	
	ATeleporter();

	virtual void DisplayInputPrompt_Implementation(bool IsVisible) override;
	virtual bool GetIsInteractable_Implementation() override;


public:	
	class UWidgetComponent* InputPromptWidgetComponent;

private:
	bool IsInteractable = true;

};
