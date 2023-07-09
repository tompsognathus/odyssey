// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "TreasureChest.generated.h"

UCLASS()
class ODYSSEY_API ATreasureChest : public AActor, public IInteractable
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATreasureChest();

	// Variables
	UPROPERTY(EditAnywhere)
	float LidOpenAngle = 90.0f;

	UPROPERTY(EditAnywhere)
	float LidClosedAngle = 0.0f;

	UPROPERTY(EditAnywhere)
	class UArrowComponent* LidHingeArrow;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool IsOpen = false;


	// Interactable interface
	virtual void EnteredInteractionZone_Implementation(AActor* InteractableActor) override;

	virtual void InteractRequest_Implementation(AActor* InteractableActor) override;

private:
	bool IsRotating = false;
	float TargetLidAngle = LidOpenAngle;
};
