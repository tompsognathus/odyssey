// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Highlighter.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ODYSSEY_API UHighlighter : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHighlighter();

	void SetHighlight(bool IsHighlighted);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Highlighter")
	TArray<UStaticMeshComponent*> StaticMeshesToOutline;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Highlighter")
	TArray<USkeletalMeshComponent*> SkeletalMeshesToOutline;
};
