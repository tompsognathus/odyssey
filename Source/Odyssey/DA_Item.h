// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"

#include "ItemNames.h"

#include "DA_Item.generated.h"

/**
 * 
 */
UCLASS()
class ODYSSEY_API UDA_Item : public UPrimaryDataAsset
{
	GENERATED_BODY()

	public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	TSubclassOf<AActor> ItemActorRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	EItemNames ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FString ItemDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int MaxStackSize;

};
