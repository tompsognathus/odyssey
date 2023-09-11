// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Memories.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ODYSSEY_API UMemories : public UActorComponent
{
	GENERATED_BODY()

public:	
	UMemories();

protected:
	virtual void BeginPlay() override;

//private:
	//Tarray<Memory*> Memories;

		
};
