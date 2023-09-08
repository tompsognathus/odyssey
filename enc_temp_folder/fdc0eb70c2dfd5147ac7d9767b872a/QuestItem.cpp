// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestItem.h"
#include "Highlighter.h"
#include "Components/WidgetComponent.h"
#include "Inventory.h"
#include "Utility.h"
#include "OdysseyCharacter.h"
#include "Kismet/GameplayStatics.h"


AQuestItem::AQuestItem()
{
	PrimaryActorTick.bCanEverTick = false;

}

void AQuestItem::BeginPlay()
{
	Super::BeginPlay();

	CacheInputPromptWidgetComponent();

	Inventory = Utility::GetInventory(this);
}

void AQuestItem::CacheInputPromptWidgetComponent()
{
	UActorComponent* InputPromptActorComponent = GetComponentByClass(UWidgetComponent::StaticClass());
	if (!IsValid(InputPromptActorComponent))
	{
		UE_LOG(LogTemp, Error, TEXT("AQuestItem::GetInputPromptWidgetComponent: Invalid InputPromptActorComponent on %s"), *GetName());
		return;
	}

	InputPromptWidgetComponent = Cast<UWidgetComponent>(InputPromptActorComponent);
	if (!IsValid(InputPromptWidgetComponent))
	{
		UE_LOG(LogTemp, Error, TEXT("AQuestItem::GetInputPromptWidgetComponent: Invalid InputPromptWidgetComponent on %s"), *GetName());
		return;
	}
}

void AQuestItem::HandleInteractRequest()
{
	if (!IsValid(Inventory))
	{
		UE_LOG(LogTemp, Error, TEXT("AQuestItem::HandleInteractRequest: Invalid Inventory on %s"), *GetName());
		return;
	}
	AOdysseyCharacter* PlayerCharacter = Utility::GetPlayerCharacter(this);
	if (!IsValid(PlayerCharacter))
	{
		UE_LOG(LogTemp, Error, TEXT("AQuestItem::HandleInteractRequest: Invalid PlayerCharacter"));
		return;
	}

	Inventory->AddItem(ItemDataAsset, ItemCount);
	UGameplayStatics::PlaySound2D(Inventory, PickupSound, 4.f);

	// update has boblins box variable on player

	this->Destroy();
}

bool AQuestItem::GetIsInteractable_Implementation()
{
	return IsInteractable;
}

void AQuestItem::Highlight_Implementation(bool IsHighlighted)
{
	UHighlighter* HighlighterComponent = FindComponentByClass<UHighlighter>();
	if (!IsValid(HighlighterComponent))
	{
		UE_LOG(LogTemp, Error, TEXT("AQuestItem::Highlight_Implementation: Invalid HighlighterComponent on %s"), *GetName());
		return;
	}

	HighlighterComponent->SetHighlight(IsHighlighted);
}

void AQuestItem::DisplayInputPrompt_Implementation(bool IsVisible)
{
	if (!IsValid(InputPromptWidgetComponent))
	{
		UE_LOG(LogTemp, Error, TEXT("AQuestItem::DisplayInputPrompt_Implementation: Invalid InputPromptWidgetComponent on %s"), *GetName());
		return;
	}
	InputPromptWidgetComponent->SetHiddenInGame(!IsVisible);
}

