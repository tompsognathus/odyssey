// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "LooseFloorboard.generated.h"

class UWidgetComponent;

UCLASS()
class ODYSSEY_API ALooseFloorboard : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALooseFloorboard();

	virtual void Highlight_Implementation(bool IsHighlighted) override;
	virtual void DisplayInputPrompt_Implementation(bool IsVisible) override;
	virtual bool GetIsInteractable_Implementation() override;

public:	
	UFUNCTION(BlueprintCallable, Category = "Interactable")
	void SetIsInteractable(bool NewIsInteractable);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "TreasureChest")
	bool IsInteractable = true;


protected:
	virtual void BeginPlay() override;

	void GetInputPromptWidgetComponent();


private:
	UWidgetComponent* InputPromptWidgetComponent;
	

	// I think the following is unnecessary because it's now done by the highlighter component, but keeping it here for now just in case. TODO: Remove if not needed.
	//TArray<UStaticMeshComponent*> StaticMeshesToOutline = TArray<UStaticMeshComponent*>();
	//TArray<USkeletalMeshComponent*> SkeletalMeshesToOutline = TArray<USkeletalMeshComponent*>();
	//void GetMeshesToOutline(TArray<UStaticMeshComponent*>& StaticMeshesToOutlineOUT, TArray<USkeletalMeshComponent*>& SkeletalMeshesToOutlineOUT);


};
