// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "MorphTargetData.h"
#include "SingleMorphTarget.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class CHARISMAPLUGNPLAY_API USingleMorphTarget : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FMorphTargetData MorphTarget;
};
