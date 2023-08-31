// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMenuWidget.h"
#include "Utility.h"
#include "UIManager.h"
#include "Components/WidgetSwitcher.h"
#include "WidgetSwitchable.h"


void UGameMenuWidget::PrepareToDisplay_Implementation()
{
	DisplayWidget(0);
}

void UGameMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UIManager = Utility::GetUIManager(this);

	SetUpUIWidgets();
	AddWidgetsToWidgetSwitcher();

}

void UGameMenuWidget::SetUpUIWidgets()
{
	for (TSubclassOf<UUserWidget> WidgetAssetRef : WidgetsRefsArray)
	{
		UUserWidget* WidgetInstance = CreateWidget<UUserWidget>(this, WidgetAssetRef);
		if (!IsValid(WidgetInstance))
		{
			UE_LOG(LogTemp, Error, TEXT("UGameMenuWidget::SetUpUIWidgets(): Invalid WidgetInstance"));
			continue;
		}

		WidgetsArray.Add(WidgetInstance);
	}

	if (WidgetsArray.Num() == 0)
	{
		UE_LOG(LogTemp, Error, TEXT("UGameMenuWidget::SetUpUIWidgets(): No Widgets in WidgetsArray. Did you assign them in blueprints?"));
		return;
	}
}

void UGameMenuWidget::AddWidgetsToWidgetSwitcher()
{
	// Checks that everything exists done in AddWidgetToWidgetSwitcher()
	for (UUserWidget* WidgetInstance : WidgetsArray)
	{
		AddWidgetToWidgetSwitcher(WidgetInstance);
	}
}

void UGameMenuWidget::AddWidgetToWidgetSwitcher(UUserWidget* WidgetInstanceToAdd)
{
	if (!WidgetSwitcher)
	{
		UE_LOG(LogTemp, Error, TEXT("UGameMenuWidget::AddWidgetToWidgetSwitcher(): Invalid WidgetSwitcher"));
		return;
	}
	if (!IsValid(WidgetInstanceToAdd))
	{
		UE_LOG(LogTemp, Error, TEXT("UGameMenuWidget::AddWidgetToWidgetSwitcher(): Invalid WidgetInstanceToAdd"));
		return;
	}

	WidgetSwitcher->AddChild(WidgetInstanceToAdd);
}

void UGameMenuWidget::DisplayWidget(int Index)
{
	if (!WidgetSwitcher)
	{
		UE_LOG(LogTemp, Error, TEXT("UGameMenuWidget::DisplayWidget(): Invalid WidgetSwitcher"));
		return;
	}
	if (Index > WidgetsArray.Num() - 1)
	{
		UE_LOG(LogTemp, Error, TEXT("UGameMenuWidget::DisplayWidget(): Invalid Index"));
		return;
	}

	UUserWidget* WidgetToDisplay = WidgetsArray[Index];
	if (!IsValid(WidgetToDisplay))
	{
		UE_LOG(LogTemp, Error, TEXT("UGameMenuWidget::DisplayWidget(): Invalid WidgetToDisplay"));
		return;
	}

	if (WidgetToDisplay->Implements<UWidgetSwitchable>())
	{
		IWidgetSwitchable::Execute_PrepareToDisplay(WidgetToDisplay);
	}
	else 
	{ 
		UE_LOG(LogTemp, Warning, TEXT("UGameMenuWidget::DisplayWidget: Couldn't find interface on widget.")); 
	}

	WidgetSwitcher->SetActiveWidget(WidgetToDisplay);
}