// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "DlgSystem/DlgDialogueParticipant.h"
#include "DlgSystem/DlgContext.h"

#include "DialogueComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ODYSSEY_API UDialogueComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDialogueComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	class UUIManager* UIManager;

public:	
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

	UFUNCTION()
	TArray<UDlgDialogue*> GetDialogues() { return Dialogues; }

	// Character's dialogue participants
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	TArray<UObject*> Participants;

	UFUNCTION()
	TArray<UObject*> GetParticipants() { return Participants; }


	FName GetParticipantName()
	{
		return DialogueParticipantName;
	}

	FText GetParticipantDisplayName(FName ActiveSpeaker) 
	{
		return DialogueParticipantDisplayName;
	}

	UTexture2D* GetParticipantIcon(FName ActiveSpeaker, FName ActiveSpeakerState) 
	{ 
		return DialogueParticipantIcon; 
	}

	UFUNCTION()
	int GetNumDialogues() { return Dialogues.Num(); }

private:
	/*
	 * Dialogue
	 */
	UFUNCTION(BlueprintCallable, Category = Dialogue)
	FText GetDialogueBodyText();

	UFUNCTION(BlueprintCallable, Category = Dialogue)
	TArray<FText> GetDialogueOptionsText();
};
