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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Variables
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UWidgetComponent* InputPromptWidgetComponent;
	
	UPROPERTY(EditAnywhere)
	float LidOpenAngle = 90.0f;

	UPROPERTY(EditAnywhere)
	float LidClosedAngle = 0.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool IsOpen = false;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "NPC")
	bool IsInteractable = true;

	UFUNCTION(BlueprintCallable, Category = "NPC")
	void SetIsInteractable(bool NewInteractable);

	// Interface function overrides
	//virtual void EnteredInteractionZone_Implementation() override;
	//virtual void LeftInteractionZone_Implementation() override;
	//virtual void InteractRequest_Implementation() override;
	virtual void Highlight_Implementation(bool IsHighlighted) override;
	virtual void DisplayInputPrompt_Implementation(bool IsVisible) override;

private:
	bool IsRotating = false;
	float TargetLidAngle = LidOpenAngle;

	TArray<UStaticMeshComponent*> StaticMeshesToOutline;
	TArray<USkeletalMeshComponent*> SkeletalMeshesToOutline;

	void GetMeshesToOutline(TArray<UStaticMeshComponent*>& StaticMeshesToOutlineOUT, TArray<USkeletalMeshComponent*>& SkeletalMeshesToOutlineOUT);
};
