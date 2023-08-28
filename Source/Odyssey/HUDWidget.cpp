// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "CharSheet.h"
#include "Utility.h"

void UHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	APawn* PlayerPawn = Utility::GetPlayerPawn(this);
	if (!IsValid(PlayerPawn))
	{
		UE_LOG(LogTemp, Error, TEXT("UHUDWidget::NativeConstruct: Invalid PlayerPawn"));
		return;
	}

	UActorComponent* CharSheetComponent = PlayerPawn->GetComponentByClass(UCharSheet::StaticClass());
	if (!IsValid(CharSheetComponent))
	{
		UE_LOG(LogTemp, Error, TEXT("UHUDWidget::NativeConstruct: Invalid CharSheetComponent"));
		return;
	}

	CharSheet = Cast<UCharSheet>(CharSheetComponent);
	if (!IsValid(CharSheet))
	{
		UE_LOG(LogTemp, Error, TEXT("UHUDWidget::NativeConstruct: Invalid CharSheetComponent"));
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
		UE_LOG(LogTemp, Error, TEXT("UHUDWidget::SetHpBar: Invalid HpBar. Did you set up the binding correctly?"));
		return;
	}
	HpBar->SetPercent(Percent);

	UE_LOG(LogTemp, Display, TEXT("HpBar set to %f"), Percent);
}

void UHUDWidget::SetGpText(int32 Gp)
{
	if (!IsValid(GpText))
	{
		UE_LOG(LogTemp, Error, TEXT("UHUDWidget::SetGpText: Invalid GpText. Did you set up the binding correctly?"));
		return;
	}
	GpText->SetText(FText::FromString(FString::FromInt(Gp)));

	UE_LOG(LogTemp, Display, TEXT("GpText set to %i"), Gp);
}
