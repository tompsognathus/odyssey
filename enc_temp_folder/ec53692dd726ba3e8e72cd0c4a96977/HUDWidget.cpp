// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "CharSheet.h"


void UHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// Get player pawn
	APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (PlayerPawn)
	{
		// Get CharSheet component
		CharSheet = Cast<UCharSheet>(PlayerPawn->GetComponentByClass(UCharSheet::StaticClass()));

		if (!CharSheet) { UE_LOG(LogTemp, Error, TEXT("Cannot find CharSheet in HUDWidget, NativeConstruct")); }
	}

	// Bind to CharSheet Delegates to update HUD
	if (CharSheet)
	{
		CharSheet->OnGoldChangedDelegate.AddDynamic(this, &UHUDWidget::SetGpText);
		CharSheet->OnHpChangedDelegate.AddDynamic(this, &UHUDWidget::SetHpBar);

	} else { UE_LOG(LogTemp, Error, TEXT("Cannot bind to CharSheet Delegates in HUDWidget, NativeConstruct")); }

}

void UHUDWidget::SetHpBar(float Percent)
{
	HpBar->SetPercent(Percent);

	UE_LOG(LogTemp, Display, TEXT("HpBar set to %f"), Percent);
}

void UHUDWidget::SetGpText(int32 Gp)
{
	GpText->SetText(FText::FromString(FString::FromInt(Gp)));

	UE_LOG(LogTemp, Display, TEXT("GpText set to %i"), Gp);
}
