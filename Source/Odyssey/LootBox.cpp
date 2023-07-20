// Fill out your copyright notice in the Description page of Project Settings.


#include "LootBox.h"

// Sets default values for this component's properties
ULootBox::ULootBox()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
}


// Called when the game starts
void ULootBox::BeginPlay()
{
	Super::BeginPlay();

	// Check if the item and count arrays have the same size as we need a count for each item
	if (LootableItemRefArray.Num() != LootableItemCountArray.Num())
	{
		UE_LOG(LogTemp, Error, TEXT("Item and ItemCount arrays are not the same size!"));
		return;		
	}
}


// Called every frame
void ULootBox::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

