// Fill out your copyright notice in the Description page of Project Settings.


#include "AudioOptionsMenuWidget.h"
#include "Components/Button.h"
#include "UIManager.h"

void UAudioOptionsMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UWorld* World = GetWorld();
	if (!IsValid(World)) 
	{ 
		UE_LOG(LogTemp, Error, TEXT("Cannot find world in MainMenuWidget, NativeConstruct")); 
		return; 
	}

	APlayerController* FirstPlayerController = World->GetFirstPlayerController();
	if (!IsValid(FirstPlayerController)) 
	{ 
		UE_LOG(LogTemp, Error, TEXT("Cannot find player controller in MainMenuWidget, NativeConstruct")); 
		return; 
	}

	APawn* PlayerPawn = FirstPlayerController->GetPawn();
	if (!IsValid(PlayerPawn)) 
	{ 
		UE_LOG(LogTemp, Error, TEXT("Cannot find player pawn in MainMenuWidget, NativeConstruct")); 
		return; 
	}

	UIManager = Cast<UUIManager>(PlayerPawn->GetComponentByClass(UUIManager::StaticClass()));
	if (!IsValid(UIManager)) 
	{ 
		UE_LOG(LogTemp, Error, TEXT("Cannot find UIManager in MainMenuWidget, NativeConstruct")); 
		return; 
	}

}

void UAudioOptionsMenuWidget::HandleBackBtnClicked()
{
	if (!IsValid(UIManager)) { 
		UE_LOG(LogTemp, Error, TEXT("Cannot find UIManager in MainMenuWidget, HandleBackBtnClicked")); 
		return; 
	}

	UIManager->DisplayOptionsMenuWidget();
}
