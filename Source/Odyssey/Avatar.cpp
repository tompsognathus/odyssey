// Fill out your copyright notice in the Description page of Project Settings.


#include "Avatar.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Components/SpotLightComponent.h"


// Sets default values
AAvatar::AAvatar()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("AvatarMesh"));
	SkeletalMesh->SetupAttachment(RootComponent);

	FullBodySpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("FullBodySpringArm"));
	FullBodySpringArm->SetupAttachment(SkeletalMesh);

	FullBodyRenderTarget = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("FullBodyRenderTarget"));
	FullBodyRenderTarget->SetupAttachment(FullBodySpringArm);

	HeadSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("HeadSpringArm"));
	HeadSpringArm->SetupAttachment(SkeletalMesh);

	HeadRenderTarget = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("HeadRenderTarget"));
	HeadRenderTarget->SetupAttachment(HeadSpringArm);

	SpotLight = CreateDefaultSubobject<USpotLightComponent>(TEXT("SpotLight"));
	SpotLight->SetupAttachment(SkeletalMesh);
}




