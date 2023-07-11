// Fill out your copyright notice in the Description page of Project Settings.


#include "UIManager.h"

#include "Blueprint/UserWidget.h"
#include "Components/WidgetSwitcher.h"
#include "OdysseyCharacter.h"
#include <Kismet/GameplayStatics.h>


// Sets default values for this component's properties
UUIManager::UUIManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UUIManager::BeginPlay()
{
	Super::BeginPlay();

	// First create a parent widget that only contains a widget switcher and is used to hold 
	// all other widgets and add it to viewport
	CreateParentUIWidget();

	// Get a reference to the widget switcher we just created inside the parent
	WidgetSwitcher = Cast<UWidgetSwitcher>(ParentUIWidgetInstance->GetWidgetFromName("WidgetSwitcher"));

	// Create all widgets and add them to the widget switcher
	SetUpUIWidgets();

	// Bind to events in widgets - things like button presses
	BindToWidgets();

	// Start in the Main Menu
	DisplayWidget(MainMenuWidgetInstance);

}

/*
 * Create a parent widget that only contains a widget switcher and is used to hold all other widgets
 * and add it to viewport
 */
void UUIManager::CreateParentUIWidget()
{
	ParentUIWidgetInstance = CreateWidget(GetWorld(), ParentUIWidgetAssetRef);
	ParentUIWidgetInstance->AddToViewport();
}

void UUIManager::DisplayHUDWidgetOnly()
{
	DisplayWidget(HUDWidgetInstance);
}

/*
 * Create all UI widgets and add them to the widget switcher
 */
void UUIManager::SetUpUIWidgets()
{
	CreateUIWidgets();
	AddWidgetsToWidgetSwitcher();
}

/*
 * Create all the different UI widgets. Make sure to always also update the AddWidgetsToWidgetSwitcher
 * function when you add a widget here!!!
 */
void UUIManager::CreateUIWidgets()
{
	MainMenuWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), MainMenuWidgetAssetRef);
	PauseMenuWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), PauseMenuWidgetAssetRef);
	HUDWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), HUDWidgetAssetRef);

}

/*
 * Add all the created widgets to the widget switcher. If you add something here,
 * make sure you also created it in CreateUIWidgets!!!
 */
void UUIManager::AddWidgetsToWidgetSwitcher()
{
	AddWidgetToWidgetSwitcher(MainMenuWidgetInstance);
	AddWidgetToWidgetSwitcher(PauseMenuWidgetInstance);
	AddWidgetToWidgetSwitcher(HUDWidgetInstance);
}

/*
 * Add a widget to the widget switcher.
 *
 * INPUT: UUserWidget* WidgetInstanceToAdd: The widget to be added to the WidgetSwitcher
 */
void UUIManager::AddWidgetToWidgetSwitcher(UUserWidget* WidgetInstanceToAdd)
{
	if (WidgetInstanceToAdd)
	{
		if (WidgetSwitcher)
		{
			WidgetSwitcher->AddChild(WidgetInstanceToAdd);

		} else { UE_LOG(LogTemp, Error, TEXT("WidgetSwitcher not found in UIManager, AddWidgetToWidgetSwitcher")); }
	} else { UE_LOG(LogTemp, Error, TEXT("%s not found in UIManager, AddWidgetToWidgetSwitcher"), *WidgetInstanceToAdd->GetName()); }
}

/*
 *
 */
void UUIManager::BindToWidgets()
{

}

/*
 * Use the widget switcher to display a widget on screen
 *
 * INPUT: UUserWidget* WidgetInstanceToDisplay: The widget to be displayed
 */
void UUIManager::DisplayWidget(UUserWidget* WidgetInstanceToDisplay)
{
	PreviousWidget = Cast<UUserWidget>(WidgetSwitcher->GetActiveWidget());

	if (WidgetSwitcher)
	{
		WidgetSwitcher->SetActiveWidget(WidgetInstanceToDisplay);
		
		// Show mouse cursor
		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
		if (PlayerController)
		{
			PlayerController->bShowMouseCursor = true;
	
		} else { UE_LOG(LogTemp, Error, TEXT("PlayerController not found in UIManager, DisplayWidget")); }

		// Switch to menu action mapping context
		AOdysseyCharacter* PlayerCharacter = Cast<AOdysseyCharacter>(GetOwner());
		if (PlayerCharacter)
		{
			if (WidgetInstanceToDisplay == HUDWidgetInstance)
			{
				PlayerCharacter->ActivateExploreMappingContext();

			}
			else
			{
				PlayerCharacter->ActivateMenuMappingContext();
			}
		
		} else { UE_LOG(LogTemp, Error, TEXT("PlayerCharacter not found in UIManager, DisplayWidget")); }

		if (WidgetInstanceToDisplay == HUDWidgetInstance)
		{
			// Resume game
			UGameplayStatics::SetGamePaused(GetWorld(), false);
		}
		else
		{
			// Pause game
			UGameplayStatics::SetGamePaused(GetWorld(), true);
		}
		
	} else { UE_LOG(LogTemp, Error, TEXT("WidgetSwitcher not found in UIManager, DisplayWidget")); }
}

