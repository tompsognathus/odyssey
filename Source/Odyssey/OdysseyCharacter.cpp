// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "OdysseyCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "UIManager.h"
#include "Interactable.h"
#include "Utility.h"
#include "DialogueComponent.h"
#include "DlgSystem/DlgManager.h"


//////////////////////////////////////////////////////////////////////////
// AOdysseyCharacter

AOdysseyCharacter::AOdysseyCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}

void AOdysseyCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Default mapping context is Explore
	ActivateExploreMappingContext();

	InteractableDetector = FindComponentByClass<USphereComponent>();
	if (!IsValid(InteractableDetector))
	{
		UE_LOG(LogTemp, Error, TEXT("AOdysseyCharacter::BeginPlay: Invalid InteractableDetector"));
		return;
	}

	UIManager = FindComponentByClass<UUIManager>();
	if (!IsValid(UIManager))
	{
		UE_LOG(LogTemp, Error, TEXT("AOdysseyCharacter::BeginPlay: Invalid UIManager"));
		return;
	}

	DialogueComponent = FindComponentByClass<UDialogueComponent>();
	if (!IsValid(DialogueComponent))
	{
		UE_LOG(LogTemp, Warning, TEXT("AOdysseyCharacter::BeginPlay: Invalid DialogueComponent on %s"), *GetName());
		return;
	}
}

FName AOdysseyCharacter::GetParticipantName_Implementation() const
{
	if (!IsValid(DialogueComponent))
	{
		UE_LOG(LogTemp, Warning, TEXT("AOdysseyCharacter::GetParticipantName_Implementation: Invalid DialogueComponent on %s"), *GetName());
		return FName();
	}

	return DialogueComponent->GetParticipantName();
}

void AOdysseyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Check for and handle interactable objects inside the detector sphere
	FindLookedAtInteractTarget();
	UpdateInputPromptVisibility();
}

void AOdysseyCharacter::ActivateExploreMappingContext()
{
	UEnhancedInputLocalPlayerSubsystem* LocalPlayerSubsystem = Utility::GetEnhancedInputLocalPlayerSubsystem(this);
	if (!IsValid(LocalPlayerSubsystem))
	{
		UE_LOG(LogTemp, Error, TEXT("AOdysseyCharacter::ActivateExploreMappingContext: Invalid LocalPlayerSubsystem"));
		return;
	}
	if (ExploreMappingContext == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("AOdysseyCharacter::ActivateExploreMappingContext: ExploreMappingContext is null (not set in blueprint?)"));
		return;
	}

	LocalPlayerSubsystem->ClearAllMappings();
	LocalPlayerSubsystem->AddMappingContext(ExploreMappingContext, 0);
}

void AOdysseyCharacter::ActivateInteractMappingContext()
{
	UEnhancedInputLocalPlayerSubsystem* LocalPlayerSubsystem = Utility::GetEnhancedInputLocalPlayerSubsystem(this);
	if (!IsValid(LocalPlayerSubsystem))
	{
		UE_LOG(LogTemp, Error, TEXT("AOdysseyCharacter::ActivateInteractMappingContext: Invalid LocalPlayerSubsystem"));
		return;
	}
	if (InteractMappingContext == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("AOdysseyCharacter::ActivateInteractMappingContext: InteractMappingContext is null (not set in blueprint?)"));
		return;
	}

	LocalPlayerSubsystem->ClearAllMappings();
	LocalPlayerSubsystem->AddMappingContext(InteractMappingContext, 0);
}

void AOdysseyCharacter::ActivateMenuMappingContext()
{
	UEnhancedInputLocalPlayerSubsystem* LocalPlayerSubsystem = Utility::GetEnhancedInputLocalPlayerSubsystem(this);
	if (!IsValid(LocalPlayerSubsystem))
	{
		UE_LOG(LogTemp, Error, TEXT("AOdysseyCharacter::ActivateMenuMappingContext: Invalid LocalPlayerSubsystem"));
		return;
	}
	if (MenuMappingContext == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("AOdysseyCharacter::ActivateMenuMappingContext: MenuMappingContext is null (not set in blueprint?)"));
		return;
	}

	LocalPlayerSubsystem->ClearAllMappings();
	LocalPlayerSubsystem->AddMappingContext(MenuMappingContext, 0);
}

// Triggered from the BP_ThirdPersonCharacter blueprint when the player presses the interact button
void AOdysseyCharacter::HandleInteractRequest()
{
	if (!IsValid(InteractTarget))
	{
		UE_LOG(LogTemp, Warning, TEXT("AOdysseyCharacter::HandleInteractRequest: Invalid InteractTarget"));
		return;
	}

	if (InteractTarget->Implements<UInteractable>())
	{
		IInteractable::Execute_InteractRequest(InteractTarget);
	}
	else 
	{ 
		UE_LOG(LogTemp, Warning, TEXT("AOdysseyCharacter::HandleInteractRequest: InteractTarget does not implement UInteractable"));
	}
}

void AOdysseyCharacter::FindLookedAtInteractTarget()
{
	// Check for interactable objects inside the detector sphere
	TArray<AActor*> ActorsInInteractionDetector;

	if (!IsValid(InteractableDetector))
	{
		UE_LOG(LogTemp, Error, TEXT("AOdysseyCharacter::FindLookedAtInteractTarget: Invalid InteractableDetector"));
		return;
	}
	InteractableDetector->GetOverlappingActors(ActorsInInteractionDetector, AActor::StaticClass());

	float MinAngularDistance = 360.f;
	// Reset interact target
	PreviousInteractTarget = InteractTarget;
	InteractTarget = nullptr;

	for (AActor* CandidateTargetActor : ActorsInInteractionDetector)
	{
		if (CandidateTargetActor->Implements<UInteractable>())
		{
			bool TargetIsInteractable = IInteractable::Execute_GetIsInteractable(CandidateTargetActor);
			if (TargetIsInteractable) {
				// Calculate angular distance between OddysseyCharacter's forward vector and the actor
				FVector CharacterForwardVector = GetActorForwardVector();
				FVector CharacterToActorVector = CandidateTargetActor->GetActorLocation() - GetActorLocation();
				float AngularDistance = FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(CharacterForwardVector, CharacterToActorVector.GetSafeNormal())));
				if (AngularDistance < MinAngularDistance)
				{
					MinAngularDistance = AngularDistance;
					InteractTarget = CandidateTargetActor;
				}
			}
		}
	}
}

void AOdysseyCharacter::UpdateInputPromptVisibility()
{
	// If the current interact target is the same as the previous one, there's nothing to do
	if (InteractTarget == PreviousInteractTarget) 
	{ 
		return; 
	}

    // If we have an interact target now and it's different from the previous interact target, we need to display the new input prompt and hide the old one
	if (InteractTarget)
	{
		// Hide the old prompt
		if (PreviousInteractTarget)
		{
			IInteractable::Execute_DisplayInputPrompt(PreviousInteractTarget, false);
		}

		// Display the new prompt
		bool TargetIsInteractable = IInteractable::Execute_GetIsInteractable(InteractTarget);
		if (TargetIsInteractable)
		{
			// We check if the interface is implemented in FindLookedAtInteractTarget() so no need
			// to check again here
			IInteractable::Execute_EnteredInteractionZone(InteractTarget);
			IInteractable::Execute_DisplayInputPrompt(InteractTarget, true);
			ActivateInteractMappingContext();
		}
	}
	// Now the case when we've left the area of the last interact target
	else
	{
		// If there is no current interact target, but there is a previous interact target, hide the old prompt and activate the explore mapping context
		if (PreviousInteractTarget)
		{
			IInteractable::Execute_DisplayInputPrompt(PreviousInteractTarget, false);
		}
		ActivateExploreMappingContext();
	}
}



void AOdysseyCharacter::SetInputEnabled(bool bIsEnabled)
{
	bIsInputEnabled = bIsEnabled;
}

//////////////////////////////////////////////////////////////////////////
// Input

void AOdysseyCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {

		//Jumping
		if (JumpAction)
		{
			EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
			EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		}
		else { UE_LOG(LogTemp, Warning, TEXT("AOdysseyCharacter::SetupPlayerInputComponent: Jump Action is null. Not set in the Character Blueprint?")); }

		//Moving
		if (MoveAction)
		{
			EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AOdysseyCharacter::Move);

		}
		else { UE_LOG(LogTemp, Warning, TEXT("AOdysseyCharacter::SetupPlayerInputComponent: Move Action is null. Not set in the Character Blueprint?")); }

		//Looking
		if (LookAction)
		{
			EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AOdysseyCharacter::Look);

		}
		else { UE_LOG(LogTemp, Warning, TEXT("AOdysseyCharacter::SetupPlayerInputComponent: Look Action is null. Not set in the Character Blueprint?")); }

		//Interacting
		if (InteractAction)
		{
			EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &AOdysseyCharacter::Interact);

		}
		else { UE_LOG(LogTemp, Warning, TEXT("AOdysseyCharacter::SetupPlayerInputComponent: Interact Action is null. Not set in the Character Blueprint?")); }

		//Pause Game
		if (PauseGameAction)
		{
			EnhancedInputComponent->BindAction(PauseGameAction, ETriggerEvent::Triggered, this, &AOdysseyCharacter::PauseGame);

		}
		else { UE_LOG(LogTemp, Warning, TEXT("AOdysseyCharacter::SetupPlayerInputComponent: Pause Game Action is null. Not set in the Character Blueprint?")); }

		//Resume Game
		if (ResumeGameAction)
		{
			EnhancedInputComponent->BindAction(ResumeGameAction, ETriggerEvent::Triggered, this, &AOdysseyCharacter::ResumeGame);

		}
		else { UE_LOG(LogTemp, Warning, TEXT("AOdysseyCharacter::SetupPlayerInputComponent: Resume Game Action is null. Not set in the Character Blueprint?")); }

		// Show Inventory
		if (ShowInventoryAction)
		{
			EnhancedInputComponent->BindAction(ShowInventoryAction, ETriggerEvent::Triggered, this, &AOdysseyCharacter::ShowInventory);
		} else { UE_LOG(LogTemp, Warning, TEXT("AOdysseyCharacter::SetupPlayerInputComponent: Show Inventory Action is null. Not set in the Character Blueprint?")); }

		// Hide Inventory
		if (HideInventoryAction)
		{
			EnhancedInputComponent->BindAction(HideInventoryAction, ETriggerEvent::Triggered, this, &AOdysseyCharacter::HideInventory);
		}
		else { UE_LOG(LogTemp, Warning, TEXT("AOdysseyCharacter::SetupPlayerInputComponent: Hide Inventory Action is null. Not set in the Character Blueprint?")); }
	}
}

void AOdysseyCharacter::Move(const FInputActionValue& Value)
{
	if (!bIsInputEnabled) { return; }

	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AOdysseyCharacter::Look(const FInputActionValue& Value)
{
	if (!bIsInputEnabled) { return; }
	
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}





