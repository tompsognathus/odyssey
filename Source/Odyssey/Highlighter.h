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
	UHighlighter();

	void SetHighlight(bool IsHighlighted);

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Highlighter")
	bool bOutlineOnlyTaggedMeshes = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Highlighter")
	FName OutlineMeshTag = "Outline";

private:
	void GetMeshesToOutline();

private:
	TArray<UStaticMeshComponent*> StaticMeshesToOutline;
	TArray<USkeletalMeshComponent*> SkeletalMeshesToOutline;

};
