// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "DlgSystem/DlgDialogueParticipant.h"
#include "DlgSystem/DlgContext.h"

#include "DialogueComponent.generated.h"

class UUIManager;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ODYSSEY_API UDialogueComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UDialogueComponent();

	/***** Dialogue *****/
	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	bool StartDialogue(UDlgDialogue* Dialogue, const TArray<UObject*>& Participants);

	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	bool SelectDialogueOption(int32 Index);

	void PopulateDialogueBodyText();
	void PopulateDialogueOptionsText();

	// Getters
	UFUNCTION()
	TArray<UDlgDialogue*> GetDialogues() { return Dialogues; }

	UFUNCTION()
	TArray<UObject*> GetParticipants() { return Participants; }

	FName GetParticipantName() { return DialogueParticipantName; }

	FText GetParticipantDisplayName(FName ActiveSpeaker) { return DialogueParticipantDisplayName; }

	UMaterial* GetParticipantAvatar(FName ActiveSpeaker, FName ActiveSpeakerState) { return DialogueParticipantAvatar; }

	UFUNCTION()
	int GetNumDialogues() { return Dialogues.Num(); }

public:
	/***** Dialogue *****/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	TArray<UDlgDialogue*> Dialogues;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	TArray<UObject*> Participants;

protected:
	virtual void BeginPlay() override;

protected:
	/***** Dialogue *****/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dialogue")
	FName DialogueParticipantName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dialogue")
	FText DialogueParticipantDisplayName = NSLOCTEXT("ExampleNamespace", "ExampleCharacterName", "ExampleParticipantName");

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dialogue")
	UMaterial* DialogueParticipantAvatar;

	UPROPERTY(BlueprintReadWrite, Category = Dialogue)
	UDlgContext* DialogueContext;

	/***** Other Components *****/
	UUIManager* UIManager;

private:
	/***** Dialogue *****/
	FText GetDialogueBodyText();

	TArray<FText> GetDialogueOptionsText();


};
