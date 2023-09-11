// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "DlgSystem/DlgDialogueParticipant.h"
#include "DlgSystem/DlgContext.h"
#include "OdysseyCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
class UUIManager;
class USphereComponent;
class UInputComponent;

UCLASS(config=Game)
class AOdysseyCharacter : public ACharacter, public IDlgDialogueParticipant
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
	/** MappingContexts */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* ExploreMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* InteractMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* MenuMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	/** Interact Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* InteractAction;

	/** Pause Game Input Action **/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* PauseGameAction;

	/** ResumeGame Input Action **/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ResumeGameAction;

	/** Show Inventory Input Action **/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ShowInventoryAction;

	/** Hide Inventory Input Action **/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* HideInventoryAction;


public:
	AOdysseyCharacter();

	/***** Dialogue *****/
	UFUNCTION()
	UDialogueComponent* GetDialogueComponent() const { return DialogueComponent; }

	FName GetParticipantName_Implementation() const override;

	/**** Inputs *****/
	UFUNCTION(BlueprintCallable, Category="Input")
	void ActivateExploreMappingContext();

	UFUNCTION(BlueprintCallable, Category="Input")
	void ActivateInteractMappingContext();

	UFUNCTION(BlueprintCallable, Category="Input")
	void ActivateMenuMappingContext();

	UFUNCTION(BlueprintCallable, Category = "Input")
	void HandleInteractRequest();

	UFUNCTION(BlueprintCallable, Category = "Inputs")
	void SetInputEnabled(bool bIsEnabled);

	/** Returns CameraBoom subobject **/
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inputs")
	bool bIsInputEnabled = true;

	/***** Dialogue *****/
	UPROPERTY()
	UDialogueComponent* DialogueComponent = nullptr;

	/***** Quest Variables *****/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Quests")
	bool HasBoblinsBox = false;

protected:
	virtual void Tick(float DeltaTime) override;

	void FindLookedAtInteractTarget();

	void UpdateInputPromptVisibility();

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	/** Called for interact input */
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnInteract"))
	void Interact();

	/** Called for pause game input */
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnPauseGame"))
	void PauseGame();

	/** Called for resume game input */
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnResumeGame"))
	void ResumeGame();

	/** Called for show inventory input */
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnShowInventory"))
	void ShowInventory();

	/** Called for hide inventory input */
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnHideInventory"))
	void HideInventory();

	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	
	virtual void BeginPlay();

protected:
	// Collision component for detecting interactable actors in range
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Input|InteractableDetection")
	USphereComponent* InteractableDetector;

	UPROPERTY(BlueprintReadOnly, Category = "Interact")
	AActor* InteractTarget;

	UPROPERTY(BlueprintReadOnly, Category = "Interact")
	AActor* PreviousInteractTarget;


private:
	class UUIManager* UIManager;
	TArray<struct F_InventoryItem*> AvailableLootItems;

};

