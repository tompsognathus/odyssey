// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Interactable.h"

#include "NPC.generated.h"

UCLASS()
class ODYSSEY_API ANPC : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANPC();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void GetInputPromptWidgetComponent();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UWidgetComponent* InputPromptWidgetComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "NPC")
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
	TArray<UStaticMeshComponent*> StaticMeshesToOutline;
	TArray<USkeletalMeshComponent*> SkeletalMeshesToOutline;

	void GetMeshesToOutline(TArray<UStaticMeshComponent*>& StaticMeshesToOutlineOUT, TArray<USkeletalMeshComponent*>& SkeletalMeshesToOutlineOUT);

};
