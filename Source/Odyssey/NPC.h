// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Interactable.h"
#include "DlgSystem/DlgDialogueParticipant.h"
#include "DlgSystem/DlgContext.h"

#include "NPC.generated.h"

class UMaterial;
class UDialogueComponent;
class UUIManager;

UCLASS()
class ODYSSEY_API ANPC : public AActor, public IInteractable, public IDlgDialogueParticipant
{
	GENERATED_BODY()

public:
	ANPC();

public:
	class UWidgetComponent* InputPromptWidgetComponent;

	/***** NPC Info *****/
	UFUNCTION(BlueprintCallable, Category = "NPC|Info")
	FText GetDisplayName() const { return UIDisplayName; }

	/***** Avatar *****/
	UFUNCTION(BlueprintCallable, Category = "NPC|Avatar")
	AAvatar* GetAvatar() const { return Avatar; }

	UFUNCTION(BlueprintCallable, Category = "NPC|Avatar")
	UMaterial* GetAvatarMaterial() const { return AvatarMaterial; }

	UFUNCTION(BlueprintCallable, Category = "NPC|Avatar")
	UMaterial* GetPortraitAvatarMaterial() const { return PortraitAvatarMaterial; }

	/***** Dialogue *****/
	UFUNCTION()
	UDialogueComponent* GetDialogueComponent() const { return DialogueComponent; }

	FName GetParticipantName_Implementation() const override;
	FText GetParticipantDisplayName_Implementation(FName ActiveSpeaker) const override;

	/***** Interactable *****/
	UFUNCTION(BlueprintCallable, Category = "NPC|Interactable")
	void SetIsInteractable(bool NewInteractable);

	virtual void Highlight_Implementation(bool IsHighlighted) override;
	virtual void DisplayInputPrompt_Implementation(bool IsVisible) override;
	virtual bool GetIsInteractable_Implementation() override;

public:
	/***** Dialogue *****/
	UPROPERTY()
	UDialogueComponent* DialogueComponent = nullptr;

	/***** Interactable *****/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "NPC|Avatar")
	bool IsInteractable = true;


protected:
	virtual void BeginPlay() override;

	void GetInputPromptWidgetComponent();

protected:
	/***** NPC Info *****/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|Info")
	FText UIDisplayName;

	/***** Avatar *****/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|Avatar")
	AAvatar* Avatar = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|Avatar")
	UMaterial* AvatarMaterial = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|Avatar")
	UMaterial* PortraitAvatarMaterial = nullptr;

	UUIManager* UIManager;


private:
	void CheckIfIsInteractable();

};
