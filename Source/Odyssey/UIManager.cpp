// Fill out your copyright notice in the Description page of Project Settings.


#include "UIManager.h"

#include "Blueprint/UserWidget.h"
#include "Components/WidgetSwitcher.h"
#include "OdysseyCharacter.h"
#include <Kismet/GameplayStatics.h>
#include "RPEncounterWidget.h"
#include "TradingInventoryWidget.h"
#include "InventoryWidget.h"
#include "LootBox.h"
#include "DialogueComponent.h"
#include "NPC.h"
#include "CombatWidget.h"
#include "CombatManager.h"

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
	SetUpUIWidgets();

	// Start in the Main Menu
	DisplayWidget(MainMenuWidgetInstance);

	// Get a reference to the combat manager on the player character
	CombatManager = GetOwner()->FindComponentByClass<UCombatManager>();
	if (!CombatManager) { UE_LOG(LogTemp, Error, TEXT("CombatManager not found in UIManager, BeginPlay")); }
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

void UUIManager::DisplayMainMenuWidget()
{
	DisplayWidget(MainMenuWidgetInstance);
}

void UUIManager::DisplayPauseMenuWidget()
{
	DisplayWidget(PauseMenuWidgetInstance);
}

void UUIManager::DisplayOptionsMenuWidget()
{
	DisplayWidget(OptionsMenuWidgetInstance);
}

void UUIManager::DisplayAudioOptionsMenuWidget()
{
	DisplayWidget(AudioOptionsMenuWidgetInstance);
}

void UUIManager::DisplayRPEncounterWidget(UDialogueComponent* DialogueOwnerComponent)
{
	DisplayWidget(RPEncounterWidgetInstance);

	// Cast to RPEncounterWidget and set the owner of the dialogue
	URPEncounterWidget* RPEncounterWidget = Cast<URPEncounterWidget>(RPEncounterWidgetInstance);
	if (RPEncounterWidget)
	{
		RPEncounterWidget->SetDialogueOwner(DialogueOwnerComponent);
	}
	else { UE_LOG(LogTemp, Error, TEXT("RPEncounterWidget not found in UIManager, DisplayRPEncounterWidget")); }
}

void UUIManager::DisplayCombatWidget(class ANPC* Enemy)
{
	DisplayWidget(CombatWidgetInstance);

	if (CombatManager)
	{
		CombatManager->StartNewCombat(Enemy);
	}
}

void UUIManager::DisplayInventoryWidget()
{
	DisplayWidget(InventoryWidgetInstance);
	LoadPlayerInventoryWidgetContent();
	
}

void UUIManager::DisplayTradingInventoryWidget(ULootBox* LootBox)
{
	DisplayWidget(TradingInventoryWidgetInstance);
	LoadTradingInventoryWidgetContent(LootBox);
}

void UUIManager::OverlayQuitGameAlertWidget()
{
	if (QuitGameAlertWidgetInstance)
	{
		QuitGameAlertWidgetInstance->AddToViewport();

	} else { UE_LOG(LogTemp, Warning, TEXT("QuitGameAlertWidgetInstance is null in UIManager, OverlayQuitGameAlertWidget")); }
}

void UUIManager::OverlayNewGameAlertWidget()
{
	if (NewGameAlertWidgetInstance)
	{
		NewGameAlertWidgetInstance->AddToViewport();

	}
	else { UE_LOG(LogTemp, Warning, TEXT("QuitGameAlertWidgetInstance is null in UIManager, OverlayNewGameAlertWidget")); }
}

void UUIManager::HideAllAlerts()
{
	if (QuitGameAlertWidgetInstance)
	{
		QuitGameAlertWidgetInstance->RemoveFromParent();
	}

	if (NewGameAlertWidgetInstance)
	{
		NewGameAlertWidgetInstance->RemoveFromParent();
	}
}

/*
 * Update the main encounter text on the RP Encounter widget
 *
 * INPUT: FText MainText: The text to be displayed
 */
void UUIManager::SetRPEncounterBodyText(FText BodyText)
{
	URPEncounterWidget* RPEncounterWidget = Cast<URPEncounterWidget>(RPEncounterWidgetInstance);

	if (RPEncounterWidget)
	{
		RPEncounterWidget->SetBodyText(BodyText);
	}
	else { UE_LOG(LogTemp, Error, TEXT("RPEncounterWidget not found")); }
}

/*
 * Update the option text on the RP Encounter widget
 *
 * INPUT: int OptionNumber: The option number to be updated
 * INPUT: FText NewOptionText: The text to be displayed
 */
void UUIManager::SetRPEncounterOptionText(int OptionNumber, FText NewOptionText)
{
	URPEncounterWidget* RPEncounterWidget = Cast<URPEncounterWidget>(RPEncounterWidgetInstance);

	if (RPEncounterWidget)
	{
		switch (OptionNumber)
		{
		case 1:
			RPEncounterWidget->SetOptionText(1, NewOptionText);
			break;
		case 2:
			RPEncounterWidget->SetOptionText(2, NewOptionText);
			break;
		case 3:
			RPEncounterWidget->SetOptionText(3, NewOptionText);
			break;
		case 4:
			RPEncounterWidget->SetOptionText(4, NewOptionText);
			break;
		default:
			UE_LOG(LogTemp, Error, TEXT("Invalid option number in UIManager, SetRPEncounterOptionText"));
			break;
		}
	}
	else { UE_LOG(LogTemp, Error, TEXT("RPEncounterWidget not found in UIManager, SetRPEncounterOptionText")); }
}

void UUIManager::StartPrologue()
{
	if (GM)
	{
		// Get dialogue component
		UDialogueComponent* GMDialogueComponent = GM->GetDialogueComponent();

		if (GMDialogueComponent)
		{
			TArray<UDlgDialogue*> Dialogues = GMDialogueComponent->GetDialogues();
			TArray<UObject*> Participants = GMDialogueComponent->GetParticipants();

			if (Dialogues.Num() > 0)
			{
				// Start the dialogue
				GMDialogueComponent->StartDialogue(Dialogues[0], Participants);

			} else { UE_LOG(LogTemp, Error, TEXT("No dialogues found on DialogueComponent in UIManager, StartPrologue")); }
		} else { UE_LOG(LogTemp, Error, TEXT("DialogueComponent is null in UIManager, StartPrologue")); }
	} else { UE_LOG(LogTemp, Error, TEXT("GM is null in UIManager, StartPrologue")); }
}

void UUIManager::SetRPEncounterAvatar(UMaterial* AvatarMaterial, FText AvatarName)
{
	URPEncounterWidget* RPEncounterWidget = Cast<URPEncounterWidget>(RPEncounterWidgetInstance);

	if (RPEncounterWidget)
	{
		RPEncounterWidget->SetAvatar(AvatarMaterial, AvatarName);
	
	} else { UE_LOG(LogTemp, Error, TEXT("RPEncounterWidget not found in UIManager, SetRPEncounterAvatar")); }
}

/*
 * Select one of the available dialogue options and display the next portion of the dialogue
 *
 * INPUT: int OptionNumber: Index of the selected option (1-4)
 */

void UUIManager::SelectDialogueOption(int OptionNumber, UDialogueComponent* DialogueOwnerComponent)
{
	if (OptionNumber < 0 || OptionNumber > 3)
	{
		UE_LOG(LogTemp, Error, TEXT("Invalid option number, must be between 1 and 4 in UIManager, SelectDialogueOption"));
		return;
	}

	if (DialogueOwnerComponent)
	{
		bool HasReachedEndOfDialogue = !(DialogueOwnerComponent->SelectDialogueOption(OptionNumber));
		UE_LOG(LogTemp, Display, TEXT("HasReachedEndOfDialogue: %s"), HasReachedEndOfDialogue ? TEXT("true") : TEXT("false"));
		if (!HasReachedEndOfDialogue)
		{
			DialogueOwnerComponent->PopulateDialogueBodyText();
			DialogueOwnerComponent->PopulateDialogueOptionsText();
		}
		else
		{
			UE_LOG(LogTemp, Display, TEXT("Reached end of dialogue in UIManager, SelectDialogueOption"));
			DisplayWidget(HUDWidgetInstance);
		}

	} else { UE_LOG(LogTemp, Error, TEXT("NPC not found in UIManager, SelectDialogueOption")); }
}


void UUIManager::LoadTradingInventoryWidgetContent(ULootBox* LootBox)
{
	if (TradingInventoryWidgetInstance)
	{
		// Cast to TradingInventoryWidget and update the content
		UTradingInventoryWidget* TradingInventoryWidget = Cast<UTradingInventoryWidget>(TradingInventoryWidgetInstance);

		if (TradingInventoryWidget)
		{
			TradingInventoryWidget->LoadLootBoxInventoryUIContents(LootBox);
			TradingInventoryWidget->LoadPlayerInventoryUIContents();

		} else { UE_LOG(LogTemp, Error, TEXT("TradingInventoryWidget not found in UIManager, UpdateTradingInventoryWidgetContent")); }
	} else { UE_LOG(LogTemp, Error, TEXT("TradingInventoryWidgetInstance is null in UIManager, UpdateTradingInventoryWidgetContent")); }
}

void UUIManager::LoadPlayerInventoryWidgetContent()
{
	if (InventoryWidgetInstance)
	{
		// Cast to InventoryWidget and update the content
		UInventoryWidget* InventoryWidget = Cast<UInventoryWidget>(InventoryWidgetInstance);

		if (InventoryWidget)
		{
			InventoryWidget->LoadInventoryUIContents();

		} else { UE_LOG(LogTemp, Error, TEXT("InventoryWidget not found in UIManager, UpdateInventoryWidgetContent")); }
	} else { UE_LOG(LogTemp, Error, TEXT("InventoryWidgetInstance is null in UIManager, UpdateInventoryWidgetContent")); }
}

void UUIManager::SetCurrentRoundText(int CurrentRound)
{
	if (CombatWidgetInstance)
	{
		// Cast to CombatWidget
		UCombatWidget* CombatWidget = Cast<UCombatWidget>(CombatWidgetInstance);

		if (CombatWidget)
		{
			CombatWidget->SetCurrentRoundText(CurrentRound);

		} else { UE_LOG(LogTemp, Error, TEXT("CombatWidget not found in UIManager, SetCurrentRoundText")); }
	} else { UE_LOG(LogTemp, Error, TEXT("CombatWidgetInstance is null in UIManager, SetCurrentRoundText")); }
}

void UUIManager::SetEnemyInfo(UMaterial* EnemyAvatarMaterial, FText EnemyName)
{
	if (CombatWidgetInstance)
	{
		// Cast to CombatWidget
		UCombatWidget* CombatWidget = Cast<UCombatWidget>(CombatWidgetInstance);
	
		if (CombatWidget)
		{
			CombatWidget->SetEnemyAvatar(EnemyAvatarMaterial);
			CombatWidget->SetEnemyName(EnemyName);

		} else { UE_LOG(LogTemp, Error, TEXT("CombatWidget not found in UIManager, SetEnemyAvatar")); }
	} else { UE_LOG(LogTemp, Error, TEXT("CombatWidgetInstance is null in UIManager, SetEnemyAvatar")); }
}

void UUIManager::SetEnemyHpPercent(float NormalizedPercent)
{
if (CombatWidgetInstance)
	{
		// Cast to CombatWidget
		UCombatWidget* CombatWidget = Cast<UCombatWidget>(CombatWidgetInstance);

		if (CombatWidget)
		{
			CombatWidget->SetEnemyHpBarPercent(NormalizedPercent);

		} else { UE_LOG(LogTemp, Error, TEXT("CombatWidget not found in UIManager, SetEnemyHpPercent")); }
	} else { UE_LOG(LogTemp, Error, TEXT("CombatWidgetInstance is null in UIManager, SetEnemyHpPercent")); }
}

void UUIManager::SetPlayerHpPercent(float NormalizedPercent)
{
	if (CombatWidgetInstance)
	{
		// Cast to CombatWidget
		UCombatWidget* CombatWidget = Cast<UCombatWidget>(CombatWidgetInstance);

		if (CombatWidget)
		{
			CombatWidget->SetPlayerHpBarPercent(NormalizedPercent);

		} else { UE_LOG(LogTemp, Error, TEXT("CombatWidget not found in UIManager, SetPlayerHpPercent")); }
	} else { UE_LOG(LogTemp, Error, TEXT("CombatWidgetInstance is null in UIManager, SetPlayerHpPercent")); }
}

void UUIManager::SetCombatActionBtnsEnabled(bool IsEnabled)
{
	if (CombatWidgetInstance)
	{
		// Cast to CombatWidget
		UCombatWidget* CombatWidget = Cast<UCombatWidget>(CombatWidgetInstance);

		if (CombatWidget)
		{
			CombatWidget->SetActionBtnsEnabled(IsEnabled);

		} else { UE_LOG(LogTemp, Error, TEXT("CombatWidget not found in UIManager, SetPlayerHpPercent")); }
	} else { UE_LOG(LogTemp, Error, TEXT("CombatWidgetInstance is null in UIManager, SetPlayerHpPercent")); }
}

void UUIManager::UpdatePlayerCombatActionButtons(TArray<class UDA_ItemAction*> AttackActions)
{
	if (CombatWidgetInstance)
	{
		// Cast to CombatWidget
		UCombatWidget* CombatWidget = Cast<UCombatWidget>(CombatWidgetInstance);

		if (CombatWidget)
		{
			CombatWidget->SetUpAttackButtons(AttackActions);

		} else { UE_LOG(LogTemp, Error, TEXT("CombatWidget not found in UIManager, UpdatePlayerCombatActionBtns")); }
	} else { UE_LOG(LogTemp, Error, TEXT("CombatWidgetInstance is null in UIManager, UpdatePlayerCombatActionBtns")); }
}

void UUIManager::DisplayPreviousWidget()
{
	DisplayWidget(PreviousWidget);
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
	// UI Screens
	MainMenuWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), MainMenuWidgetAssetRef);
	PauseMenuWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), PauseMenuWidgetAssetRef);
	OptionsMenuWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), OptionsMenuWidgetAssetRef);
	AudioOptionsMenuWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), AudioOptionsMenuWidgetAssetRef);
	RPEncounterWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), RPEncounterWidgetAssetRef);
	CombatWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), CombatWidgetAssetRef);
	InventoryWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), InventoryWidgetAssetRef);
	TradingInventoryWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), TradingInventoryWidgetAssetRef);

	// HUD only
	HUDWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), HUDWidgetAssetRef);

	// Alert Widgets
	QuitGameAlertWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), QuitGameAlertWidgetAssetRef);
	NewGameAlertWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), NewGameAlertWidgetAssetRef);

}

/*
 * Add all the created widgets to the widget switcher. If you add something here,
 * make sure you also created it in CreateUIWidgets!!!
 */
void UUIManager::AddWidgetsToWidgetSwitcher()
{
	AddWidgetToWidgetSwitcher(MainMenuWidgetInstance);
	AddWidgetToWidgetSwitcher(PauseMenuWidgetInstance);
	AddWidgetToWidgetSwitcher(OptionsMenuWidgetInstance);
	AddWidgetToWidgetSwitcher(AudioOptionsMenuWidgetInstance);
	AddWidgetToWidgetSwitcher(RPEncounterWidgetInstance);
	AddWidgetToWidgetSwitcher(CombatWidgetInstance);
	AddWidgetToWidgetSwitcher(HUDWidgetInstance);
	AddWidgetToWidgetSwitcher(InventoryWidgetInstance);
	AddWidgetToWidgetSwitcher(TradingInventoryWidgetInstance);

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
 * Use the widget switcher to display a widget on screen
 *
 * INPUT: UUserWidget* WidgetInstanceToDisplay: The widget to be displayed
 */
void UUIManager::DisplayWidget(UUserWidget* WidgetInstanceToDisplay)
{
	PreviousWidget = Cast<UUserWidget>(WidgetSwitcher->GetActiveWidget());

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	AOdysseyCharacter* PlayerCharacter = Cast<AOdysseyCharacter>(GetOwner());

	if (!WidgetSwitcher) { UE_LOG(LogTemp, Error, TEXT("WidgetSwitcher not found in UIManager, DisplayWidget")); return; }
	if (!PlayerController) { UE_LOG(LogTemp, Error, TEXT("PlayerController not found in UIManager, DisplayWidget")); return; }
	if (!PlayerCharacter) { UE_LOG(LogTemp, Error, TEXT("PlayerCharacter not found in UIManager, DisplayWidget")); return; }


	WidgetSwitcher->SetActiveWidget(WidgetInstanceToDisplay);

	// When returning to game world from anywhere
	if (WidgetInstanceToDisplay == HUDWidgetInstance)
	{
		// Hide mouse cursor
		PlayerController->bShowMouseCursor = false;
		// Switch to exploration controls
		PlayerCharacter->ActivateExploreMappingContext();
		// Resume game world
		//UGameplayStatics::SetGamePaused(GetWorld(), false);

	}
	// When leaving game and entering a menu or other UI screen
	else
	{
		// Show mouse cursor
		PlayerController->bShowMouseCursor = true;
		// Switch to menu controls
		PlayerCharacter->ActivateMenuMappingContext();
		// Pause game world
		//UGameplayStatics::SetGamePaused(GetWorld(), true);
	}
}

