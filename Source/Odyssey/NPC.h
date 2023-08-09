// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Interactable.h"
#include "DlgSystem/DlgDialogueParticipant.h"
#include "DlgSystem/DlgContext.h"

#include "NPC.generated.h"

UCLASS()
class ODYSSEY_API ANPC : public AActor, public IInteractable, public IDlgDialogueParticipant
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANPC();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void GetInputPromptWidgetComponent();

protected:
	class UUIManager* UIManager;

public:
	class UWidgetComponent* InputPromptWidgetComponent;


	/*
	 * Dialogue
	 */
	UPROPERTY()
	class UDialogueComponent* DialogueComponent = nullptr;

	UFUNCTION()
	UDialogueComponent* GetDialogueComponent() { return DialogueComponent; }

	FName GetParticipantName_Implementation() const override;
	FText GetParticipantDisplayName_Implementation(FName ActiveSpeaker) const override;
	UTexture2D* GetParticipantIcon_Implementation(FName ActiveSpeaker, FName ActiveSpeakerState) const override;

	/*
	 * Interactable
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "NPC")
	bool IsInteractable = true;

	UFUNCTION(BlueprintCallable, Category = "NPC")
	void SetIsInteractable(bool NewInteractable);

	// Interface function overrides
	//virtual void EnteredInteractionZone_Implementation() override;
	//virtual void LeftInteractionZone_Implementation() override;
	//virtual void InteractRequest_Implementation(UObject* CallerParticipant) override; // Implemented in Blueprint
	virtual void Highlight_Implementation(bool IsHighlighted) override;
	virtual void DisplayInputPrompt_Implementation(bool IsVisible) override;
	virtual bool GetIsInteractable_Implementation() override;

private:
	TArray<UStaticMeshComponent*> StaticMeshesToOutline;
	TArray<USkeletalMeshComponent*> SkeletalMeshesToOutline;

	void GetMeshesToOutline(TArray<UStaticMeshComponent*>& StaticMeshesToOutlineOUT, TArray<USkeletalMeshComponent*>& SkeletalMeshesToOutlineOUT);

	void CheckIfIsInteractable();

};
