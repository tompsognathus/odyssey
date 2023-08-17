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

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	void SetHighlight(bool IsHighlighted);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Highlighter")
	TArray<UStaticMeshComponent*> StaticMeshesToOutline;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Highlighter")
	TArray<USkeletalMeshComponent*> SkeletalMeshesToOutline;

	// Idk how to actually override this, so instead if I only want a subset of the meshes, I set them in BeginPlay
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Highlighter")
	void GetMeshesToOutline();
};
