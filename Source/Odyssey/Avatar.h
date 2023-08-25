// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Avatar.generated.h"

class USkeletalMeshComponent;
class USpringArmComponent;
class USceneCaptureComponent2D;
class USpotLightComponent;

UCLASS()
class ODYSSEY_API AAvatar : public AActor
{
	GENERATED_BODY()
	
public:	
	AAvatar();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Avatar")
	USkeletalMeshComponent* SkeletalMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Avatar")
	USpringArmComponent* FullBodySpringArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Avatar")
	USceneCaptureComponent2D* FullBodyRenderTarget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Avatar")
	USpringArmComponent* HeadSpringArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Avatar")
	USceneCaptureComponent2D* HeadRenderTarget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Avatar")
	USpotLightComponent* SpotLight;

};
