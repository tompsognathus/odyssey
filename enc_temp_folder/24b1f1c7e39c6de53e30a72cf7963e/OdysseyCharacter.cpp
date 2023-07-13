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

#include "Interactable.h"


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

void AOdysseyCharacter::ActivateExploreMappingContext()
{
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			if (ExploreMappingContext)
			{
				Subsystem->ClearAllMappings();
				Subsystem->AddMappingContext(ExploreMappingContext, 0);

			}
			else { UE_LOG(LogTemp, Warning, TEXT("ExploreMappingContext is null (not set in blueprint?)")); }
		}
	}
}

void AOdysseyCharacter::ActivateInteractMappingContext()
{
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			if (InteractMappingContext)
			{
				Subsystem->ClearAllMappings();
				Subsystem->AddMappingContext(InteractMappingContext, 0);

			} else { UE_LOG(LogTemp, Warning, TEXT("InteractMappingContext is null (not set in blueprint?)")); }
		}
	}
}

void AOdysseyCharacter::ActivateMenuMappingContext()
{
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			if (MenuMappingContext)
			{
				Subsystem->ClearAllMappings();
				Subsystem->AddMappingContext(MenuMappingContext, 0);

			}
			else { UE_LOG(LogTemp, Warning, TEXT("<InteractMenuMappingContext is null (not set in blueprint?)")); }
		}
	}
}

void AOdysseyCharacter::HandleInteractRequest()
{
	UE_LOG(LogTemp, Warning, TEXT("Interact Requested"));

	if (InteractTarget)
	{
		if (InteractTarget->Implements<UInteractable>())
		{
			IInteractable::Execute_InteractRequest(InteractTarget);
		}
	}
}

void AOdysseyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FindLookedAtInteractTarget();

	if (PreviousInteractTarget)
	{
		// We check if the interface is implemented in FindLookedAtInteractTarget() so no need
		// to check again here
		IInteractable::Execute_DisplayInputPrompt(PreviousInteractTarget, false);
	}
	if (InteractTarget)
	{
		// We check if the interface is implemented in FindLookedAtInteractTarget() so no need
		// to check again here
		IInteractable::Execute_EnteredInteractionZone(InteractTarget);
		IInteractable::Execute_DisplayInputPrompt(InteractTarget, true);
		ActivateInteractMappingContext();
	}
	else
	{
		ActivateExploreMappingContext();
		UE_LOG(LogTemp, Warning, TEXT("InteractTarget is null in else"));
	}
	
}

void AOdysseyCharacter::FindLookedAtInteractTarget()
{
	// Check for interactable objects inside the detector sphere
	TArray<AActor*> ActorsInInteractionDetector;
	InteractableDetector->GetOverlappingActors(ActorsInInteractionDetector, AActor::StaticClass());

	float MinAngularDistance = 360.f;
	// Reset interact target
	PreviousInteractTarget = InteractTarget;
	InteractTarget = nullptr;

	for (AActor* CandidateTargetActor : ActorsInInteractionDetector)
	{
		if (CandidateTargetActor->Implements<UInteractable>())
		{
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


void AOdysseyCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	ActivateExploreMappingContext();

	// Get reference to interactable detector sphere
	InteractableDetector = FindComponentByClass<USphereComponent>();

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
		else { UE_LOG(LogTemp, Warning, TEXT("Jump Action is null. Not set in the Character Blueprint?")); }

		//Moving
		if (MoveAction)
		{
			EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AOdysseyCharacter::Move);

		}
		else { UE_LOG(LogTemp, Warning, TEXT("Move Action is null. Not set in the Character Blueprint?")); }

		//Looking
		if (LookAction)
		{
			EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AOdysseyCharacter::Look);

		}
		else { UE_LOG(LogTemp, Warning, TEXT("Look Action is null. Not set in the Character Blueprint?")); }

		//Interacting
		if (InteractAction)
		{
			EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &AOdysseyCharacter::Interact);

		}
		else { UE_LOG(LogTemp, Warning, TEXT("Interact Action is null. Not set in the Character Blueprint?")); }

		//Pause Game
		if (PauseGameAction)
		{
			EnhancedInputComponent->BindAction(PauseGameAction, ETriggerEvent::Triggered, this, &AOdysseyCharacter::PauseGame);

		}
		else { UE_LOG(LogTemp, Warning, TEXT("Pause Game Action is null. Not set in the Character Blueprint?")); }

		//Resume Game
		if (ResumeGameAction)
		{
			EnhancedInputComponent->BindAction(ResumeGameAction, ETriggerEvent::Triggered, this, &AOdysseyCharacter::ResumeGame);

		}
		else { UE_LOG(LogTemp, Warning, TEXT("Resume Game Action is null. Not set in the Character Blueprint?")); }
	}
}

void AOdysseyCharacter::Move(const FInputActionValue& Value)
{
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
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}





