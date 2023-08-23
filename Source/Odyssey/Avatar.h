// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Avatar.generated.h"

UCLASS()
class ODYSSEY_API AAvatar : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAvatar();

public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Avatar")
	class USkeletalMeshComponent* SkeletalMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Avatar")
	class USpringArmComponent* FullBodySpringArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Avatar")
	class USceneCaptureComponent2D* FullBodyRenderTarget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Avatar")
	class USpringArmComponent* HeadSpringArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Avatar")
	class USceneCaptureComponent2D* HeadRenderTarget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Avatar")
	class USpotLightComponent* SpotLight;

};
