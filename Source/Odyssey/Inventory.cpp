// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory.h"
#include "F_InventorySlot.h"

// Sets default values for this component's properties
UInventory::UInventory()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	CreateInventory();
}


// Called when the game starts
void UInventory::BeginPlay()
{
	Super::BeginPlay();

	
	
}


// Called every frame
void UInventory::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
}

void UInventory::AddToInventory()
{

}

void UInventory::RemoveFromInventory()
{

}

int UInventory::GetInventorySize()
{
	return InventorySize;
}

void UInventory::CreateInventory()
{
	for (int idx = 0; idx < InventorySize; idx++)
	{
		F_InventorySlot* InventorySlot = new F_InventorySlot();
		InventorySlot->ItemName = "";
		InventorySlot->Quantity = 0;
		InventorySlots.Add(InventorySlot);
	}
}

