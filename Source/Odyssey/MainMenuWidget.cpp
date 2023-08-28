// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuWidget.h"
#include "UIManager.h"
#include "Kismet/GameplayStatics.h"


void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UWorld* World = GetWorld();
	if (!IsValid(World))
	{
		UE_LOG(LogTemp, Error, TEXT("Cannot find World in MainMenuWidget, NativeConstruct"));
		return;
	}

	APlayerController* FirstPlayerController = World->GetFirstPlayerController();
	if (!IsValid(FirstPlayerController))
	{
		UE_LOG(LogTemp, Error, TEXT("Cannot find FirstPlayerController in MainMenuWidget, NativeConstruct"));
		return;
	}

	APawn* PlayerPawn = FirstPlayerController->GetPawn();
	if (!IsValid(PlayerPawn))
	{
		UE_LOG(LogTemp, Error, TEXT("Cannot find PlayerPawn in MainMenuWidget, NativeConstruct"));
		return;
	}

	UActorComponent* UIManagerComponent = PlayerPawn->GetComponentByClass(UUIManager::StaticClass());
	if (!IsValid(UIManagerComponent))
	{
		UE_LOG(LogTemp, Error, TEXT("Cannot find UIManagerComponent in MainMenuWidget, NativeConstruct"));
		return;
	}

	UIManager = Cast<UUIManager>(UIManagerComponent);
	if (!IsValid(UIManager))
	{
		UE_LOG(LogTemp, Error, TEXT("Cannot cast UIManagerComponent to UIManager in MainMenuWidget, NativeConstruct"));
		return;
	}
}

void UMainMenuWidget::HandleContinueGameBtnClicked()
{
	if (!IsValid(UIManager))
	{
		UE_LOG(LogTemp, Error, TEXT("Cannot find UIManager in MainMenuWidget, HandleContinueGameBtnClicked"));
		return;
	}
	UIManager->DisplayHUDWidgetOnly();
}

void UMainMenuWidget::HandleNewGameBtnClicked()
{
	if (!IsValid(UIManager))
	{
		UE_LOG(LogTemp, Error, TEXT("Cannot find UIManager in MainMenuWidget, HandleNewGameBtnClicked"));
		return;
	}
	UIManager->OverlayNewGameAlertWidget();
}

void UMainMenuWidget::HandleOptionsBtnClicked()
{
	if (!IsValid(UIManager))
	{
		UE_LOG(LogTemp, Error, TEXT("Cannot find UIManager in MainMenuWidget, HandleOptionsBtnClicked"));
		return;
	}
	UIManager->DisplayOptionsMenuWidget();
}

void UMainMenuWidget::HandleQuitGameBtnClicked()
{
	if (!IsValid(UIManager))
	{
		UE_LOG(LogTemp, Error, TEXT("Cannot find UIManager in MainMenuWidget, HandleQuitGameBtnClicked"));
		return;
	}
	UIManager->OverlayQuitGameAlertWidget();
}
