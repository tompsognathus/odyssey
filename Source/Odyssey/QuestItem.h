// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "QuestItem.generated.h"

class UWidgetComponent;

UCLASS()
class ODYSSEY_API AQuestItem : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	AQuestItem();

	UFUNCTION(BlueprintCallable, Category = "QuestItem")
	void HandleInteractRequest();

	virtual bool GetIsInteractable_Implementation() override;
	virtual void Highlight_Implementation(bool IsHighlighted) override;
	virtual void DisplayInputPrompt_Implementation(bool IsVisible) override;

public:
	UWidgetComponent* InputPromptWidgetComponent;

protected:
	virtual void BeginPlay() override;

private:
	void CacheInputPromptWidgetComponent();

private:
	bool IsInteractable = true;
};
