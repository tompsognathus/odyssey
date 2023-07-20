// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "OdysseyCharacter.generated.h"


UCLASS(config=Game)
class AOdysseyCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
	
	/** MappingContexts */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* ExploreMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* InteractMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* MenuMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	/** Interact Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* InteractAction;

	/** Pause Game Input Action **/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* PauseGameAction;

	/** ResumeGame Input Action **/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* ResumeGameAction;

	/** Show Inventory Input Action **/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* ShowInventoryAction;

	/** Hide Inventory Input Action **/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* HideInventoryAction;

private:
	class UUIManager* UIManager;

	TArray<struct F_InventoryItem*> AvailableLootItems;

public:
	AOdysseyCharacter();
	
	UFUNCTION(BlueprintCallable, Category="Input")
	void ActivateExploreMappingContext();

	UFUNCTION(BlueprintCallable, Category="Input")
	void ActivateInteractMappingContext();

	UFUNCTION(BlueprintCallable, Category="Input")
	void ActivateMenuMappingContext();

	UFUNCTION(BlueprintCallable, Category = "Input")
	void HandleInteractRequest();

protected:
	/** Tick Function **/
	virtual void Tick(float DeltaTime) override;

	void FindLookedAtInteractTarget();

	void UpdateInputPromptVisibility();
	
	// Collision component for detecting interactable actors in range
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Input|InteractableDetection")
	class USphereComponent* InteractableDetector;

	UPROPERTY(BlueprintReadOnly, Category = "Interact")
	AActor* InteractTarget;

	UPROPERTY(BlueprintReadOnly, Category = "Interact")
	AActor* PreviousInteractTarget;

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

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay();

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

