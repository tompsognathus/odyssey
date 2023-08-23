// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"

#include "ItemNames.h"

#include "DA_ItemAction.generated.h"

/**
 * 
 */
UCLASS()
class ODYSSEY_API UDA_ItemAction : public UPrimaryDataAsset
{
	GENERATED_BODY()

	public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FName ActionName;

};
