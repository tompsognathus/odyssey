// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"

#include "ItemNames.h"
#include "ItemType.h"
#include "DA_ItemAction.h"

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
	TSubclassOf<AActor> ActorRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	EItemType Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	EItemNames Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FString DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FString Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	UTexture2D* Icon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	TArray<UDA_ItemAction*> ItemActions;
};
