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

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	class UUIManager* UIManager;

public:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UWidgetComponent* InputPromptWidgetComponent;

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
	//virtual void InteractRequest_Implementation() override;
	virtual void Highlight_Implementation(bool IsHighlighted) override;
	virtual void DisplayInputPrompt_Implementation(bool IsVisible) override;
	virtual bool GetIsInteractable_Implementation() override;

	/*
	 * Dialogue
	 */
	 // Name of this participant, used for GetParticipantName
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dialogue")
		FName DialogueParticipantName;

	// UI name of this participant, what is displayed inside the UI
	// Used for GetParticipantDisplayName
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dialogue")
		FText DialogueParticipantDisplayName = NSLOCTEXT("ExampleNamespace", "ExampleCharacterName", "ExampleParticipantName");

	// Used for GetParticipantIcon
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dialogue")
		UTexture2D* DialogueParticipantIcon;

	// Context used to control the Dialogue follow
	UPROPERTY(BlueprintReadWrite, Category = Dialogue)
		UDlgContext* DialogueContext = nullptr;

	// Function to start the dialogue
	UFUNCTION(BlueprintCallable, Category = Dialogue)
		bool StartDialogue(UDlgDialogue* Dialogue, const TArray<UObject*>& Participants);

	// Functionto advance through the dialogue
	UFUNCTION(BlueprintCallable, Category = Dialogue)
		bool SelectDialogueOption(int32 Index);

	void PopulateDialogueBodyText();
	void PopulateDialogueOptionsText();

	// Character's dialogue assets
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
		TArray<UDlgDialogue*> Dialogues;

	// Character's dialogue participants
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
		TArray<UObject*> Participants;


	FName GetParticipantName_Implementation() const override
	{
		UE_LOG(LogTemp, Display, TEXT("Participant Name: %s"), *DialogueParticipantName.ToString());
		return DialogueParticipantName;
	}

	FText GetParticipantDisplayName_Implementation(FName ActiveSpeaker) const override
	{
		UE_LOG(LogTemp, Display, TEXT("Participant Display Name: %s"), *DialogueParticipantDisplayName.ToString());
		return DialogueParticipantDisplayName;
	}

	UTexture2D* GetParticipantIcon_Implementation(FName ActiveSpeaker, FName ActiveSpeakerState) const override { return DialogueParticipantIcon; }

private:
	TArray<UStaticMeshComponent*> StaticMeshesToOutline;
	TArray<USkeletalMeshComponent*> SkeletalMeshesToOutline;

	void GetMeshesToOutline(TArray<UStaticMeshComponent*>& StaticMeshesToOutlineOUT, TArray<USkeletalMeshComponent*>& SkeletalMeshesToOutlineOUT);

	/*
	 * Dialogue
	 */
	UFUNCTION(BlueprintCallable, Category = Dialogue)
		FText GetDialogueBodyText();

	UFUNCTION(BlueprintCallable, Category = Dialogue)
		TArray<FText> GetDialogueOptionsText();
};
