// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "CharSheet.h"


void UHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UWorld* World = GetWorld();
	if (!IsValid(World))
	{
		UE_LOG(LogTemp, Error, TEXT("Cannot find World in HUDWidget, NativeConstruct"));
		return;
	}

	APlayerController* FirstPlayerController = World->GetFirstPlayerController();
	if (!IsValid(FirstPlayerController))
	{
		UE_LOG(LogTemp, Error, TEXT("Cannot find FirstPlayerController in HUDWidget, NativeConstruct"));
		return;
	}

	APawn* PlayerPawn = FirstPlayerController->GetPawn();
	if (!IsValid(PlayerPawn))
	{
		UE_LOG(LogTemp, Error, TEXT("Cannot find PlayerPawn in HUDWidget, NativeConstruct"));
		return;
	}

	UActorComponent* CharSheetComponent = PlayerPawn->GetComponentByClass(UCharSheet::StaticClass());
	if (!IsValid(CharSheetComponent))
	{
		UE_LOG(LogTemp, Error, TEXT("Cannot find CharSheetComponent in HUDWidget, NativeConstruct"));
		return;
	}

	CharSheet = Cast<UCharSheet>(CharSheetComponent);
	if (!IsValid(CharSheet))
	{
		UE_LOG(LogTemp, Error, TEXT("Cannot cast CharSheetComponent to CharSheet in HUDWidget, NativeConstruct"));
		return;
	}

	// Bind to CharSheet Delegates to update HUD
	CharSheet->OnGoldChangedDelegate.AddDynamic(this, &UHUDWidget::SetGpText);
	CharSheet->OnHpChangedDelegate.AddDynamic(this, &UHUDWidget::SetHpBar);
}

void UHUDWidget::SetHpBar(float Percent)
{
	if (!IsValid(HpBar))
	{
		UE_LOG(LogTemp, Error, TEXT("Cannot find HpBar in HUDWidget, SetHpBar. Did you set up the binding correctly?"));
		return;
	}
	HpBar->SetPercent(Percent);

	UE_LOG(LogTemp, Display, TEXT("HpBar set to %f"), Percent);
}

void UHUDWidget::SetGpText(int32 Gp)
{
	if (!IsValid(GpText))
	{
		UE_LOG(LogTemp, Error, TEXT("Cannot find GpText in HUDWidget, SetGpText. Did you set up the binding correctly?"));
		return;
	}
	GpText->SetText(FText::FromString(FString::FromInt(Gp)));

	UE_LOG(LogTemp, Display, TEXT("GpText set to %i"), Gp);
}
