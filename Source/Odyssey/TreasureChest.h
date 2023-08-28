// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "TreasureChest.generated.h"

class UWidgetComponent;

UCLASS()
class ODYSSEY_API ATreasureChest : public AActor, public IInteractable
{
	GENERATED_BODY()

public:
	ATreasureChest();

	// Interactable Interface function overrides
	virtual void Highlight_Implementation(bool IsHighlighted) override;
	virtual void DisplayInputPrompt_Implementation(bool IsVisible) override;
	virtual bool GetIsInteractable_Implementation() override;

public:
	UWidgetComponent* InputPromptWidgetComponent;
	
	UPROPERTY(EditAnywhere)
	float LidOpenAngle = 90.0f;

	UPROPERTY(EditAnywhere)
	float LidClosedAngle = 0.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "TreasureChest")
	bool IsInteractable = true;


protected:
	virtual void BeginPlay() override;


private:
	void CacheInputPromptWidgetComponent();

private:
	bool IsRotating = false;
	float TargetLidAngle = LidOpenAngle;

};
