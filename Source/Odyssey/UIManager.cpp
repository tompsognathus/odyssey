// Fill out your copyright notice in the Description page of Project Settings.


#include "UIManager.h"
#include "WidgetSwitchable.h"
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
#include "Utility.h"
#include "Avatar.h"
#include "GameMenuWidget.h"

UUIManager::UUIManager()
{
	PrimaryComponentTick.bCanEverTick = false;
}

// Called when the game starts
void UUIManager::BeginPlay()
{
	Super::BeginPlay();

	CreateParentUIWidget();  // Used to hold all other widgets

	if (!IsValid(ParentUIWidgetInstance))
	{
		UE_LOG(LogTemp, Error, TEXT("UUIManager::BeginPlay: Invalid ParentUIWidgetInstance"));
		return;
	}
	
	UWidget* WigetSwitcherWidget = ParentUIWidgetInstance->GetWidgetFromName("WidgetSwitcher");
	if (!IsValid(WigetSwitcherWidget))
	{
		UE_LOG(LogTemp, Error, TEXT("UUIManager::BeginPlay: Invalid WidgetSwitcherWidget"));
		return;
	}

	WidgetSwitcher = Cast<UWidgetSwitcher>(WigetSwitcherWidget);
	if (!WidgetSwitcher)
	{
		UE_LOG(LogTemp, Error, TEXT("UUIManager::BeginPlay: Invalid WidgetSwitcher"));
		return;
	}

	SetUpUIWidgets();

	DisplayWidget(MainMenuWidgetInstance); 	// Game starts with the main menu widget

	CombatManager = Utility::GetCombatManager(this);
	if (!IsValid(CombatManager)) 
	{ 
		UE_LOG(LogTemp, Error, TEXT("UUIManager::BeginPlay: Invalid CombatManager")); 
		return;
	}
}

/*
 * Create a parent widget that only contains a widget switcher and is used to hold all other widgets
 * and add it to viewport
 */
void UUIManager::CreateParentUIWidget()
{
	if (!IsValid(ParentUIWidgetAssetRef))
	{
		UE_LOG(LogTemp, Error, TEXT("UUIManager::CreateParentUIWidget: Invalid ParentUIWidgetAssetRef. Did you assign it in the editor?"));
		return;
	}

	UWorld* World = GetWorld();
	if (!IsValid(World))
	{
		UE_LOG(LogTemp, Error, TEXT("UUIManager::CreateParentUIWidget: Couldn't find world"));
		return;
	}

	ParentUIWidgetInstance = CreateWidget(GetWorld(), ParentUIWidgetAssetRef);
	if (!IsValid(ParentUIWidgetInstance))
	{
		UE_LOG(LogTemp, Error, TEXT("UUIManager::CreateParentUIWidget: Invalid ParentUIWidgetInstance"));
		return;
	}
	
	ParentUIWidgetInstance->AddToViewport();
}

void UUIManager::DisplayHUDWidgetOnly()
{
	// DisplayWidget checks if widget is valid, no need to check here
	DisplayWidget(HUDWidgetInstance);
}

void UUIManager::DisplayMainMenuWidget()
{
	// DisplayWidget checks if widget is valid, no need to check here
	DisplayWidget(MainMenuWidgetInstance);
}

void UUIManager::DisplayPauseMenuWidget()
{
	// DisplayWidget checks if widget is valid, no need to check here
	DisplayWidget(PauseMenuWidgetInstance);
}

void UUIManager::DisplayOptionsMenuWidget()
{
	// DisplayWidget checks if widget is valid, no need to check here
	DisplayWidget(OptionsMenuWidgetInstance);
}

void UUIManager::DisplayAudioOptionsMenuWidget()
{
	// DisplayWidget checks if widget is valid, no need to check here
	DisplayWidget(AudioOptionsMenuWidgetInstance);
}

void UUIManager::DisplayRPEncounterWidget(UDialogueComponent* DialogueOwnerComponent)
{
	// DisplayWidget checks if widget is valid, no need to check here
	DisplayWidget(RPEncounterWidgetInstance);

	URPEncounterWidget* RPEncounterWidget = Cast<URPEncounterWidget>(RPEncounterWidgetInstance);
	if (!IsValid(RPEncounterWidget))
	{
		UE_LOG(LogTemp, Error, TEXT("UUIManager::DisplayRPEncounterWidget: Invalid RPEncounterWidget"));
		return;
	}

	RPEncounterWidget->SetDialogueOwner(DialogueOwnerComponent);
}

void UUIManager::DisplayCombatWidget(class ANPC* Enemy)
{
	// DisplayWidget checks if widget is valid, no need to check here
	DisplayWidget(CombatWidgetInstance);

	if (!IsValid(CombatManager))
	{
		UE_LOG(LogTemp, Error, TEXT("UUIManager::DisplayCombatWidget: Invalid CombatManager"));
		return;
	}
	CombatManager->StartNewCombat(Enemy);
}

void UUIManager::DisplayTradingInventoryWidget(ULootBox* LootBox)
{
	// DisplayWidget checks if widget is valid, no need to check here
	DisplayWidget(TradingInventoryWidgetInstance);
	LoadTradingInventoryWidgetContent(LootBox);
}

void UUIManager::DisplayGameMenuWidget()
{
	// DisplayWidget checks if widget is valid, no need to check here
	DisplayWidget(GameMenuWidgetInstance);
}

void UUIManager::DisplayCreditsWidget()
{
	// DisplayWidget checks if widget is valid, no need to check here
	DisplayWidget(CreditsWidgetInstance);
}

void UUIManager::OverlayQuitGameAlertWidget()
{
	if (!IsValid(QuitGameAlertWidgetInstance))
	{
		UE_LOG(LogTemp, Error, TEXT("UUIManager::OverlayQuitGameAlertWidget: Invalid QuitGameAlertWidgetInstance"));
		return;
	}	
	QuitGameAlertWidgetInstance->AddToViewport();
}

void UUIManager::OverlayNewGameAlertWidget()
{
	if (!IsValid(NewGameAlertWidgetInstance))
	{
		UE_LOG(LogTemp, Error, TEXT("UUIManager::OverlayNewGameAlertWidget: Invalid NewGameAlertWidgetInstance"));
		return;
	}
	NewGameAlertWidgetInstance->AddToViewport();
}

void UUIManager::HideAllAlerts()
{
	if (!IsValid(QuitGameAlertWidgetAssetRef))
	{
		UE_LOG(LogTemp, Error, TEXT("UUIManager::HideAllAlerts: Invalid QuitGameAlertWidgetAssetRef"));
		return;
	}
	if (!IsValid(NewGameAlertWidgetAssetRef))
	{
		UE_LOG(LogTemp, Error, TEXT("UUIManager::HideAllAlerts: Invalid NewGameAlertWidgetAssetRef"));
		return;
	}
	
	QuitGameAlertWidgetInstance->RemoveFromParent();
	NewGameAlertWidgetInstance->RemoveFromParent();
}

/*
 * Update the main encounter text on the RP Encounter widget
 *
 * INPUT: FText MainText: The text to be displayed
 */
void UUIManager::SetRPEncounterBodyText(FText BodyText)
{
	if (!IsValid(RPEncounterWidgetInstance))
	{
		UE_LOG(LogTemp, Error, TEXT("UUIManager::SetRPEncounterBodyText: Invalid RPEncounterWidgetInstance on %s. Did you set it in the editor?"), *GetName());
		return;
	}

	URPEncounterWidget* RPEncounterWidget = Cast<URPEncounterWidget>(RPEncounterWidgetInstance);
	if (!IsValid(RPEncounterWidget))
	{
		UE_LOG(LogTemp, Error, TEXT("UUIManager::SetRPEncounterBodyText: Invalid RPEncounterWidget"));
		return;
	}

	RPEncounterWidget->SetBodyText(BodyText);
}

/*
 * Update the option text on the RP Encounter widget
 *
 * INPUT: int OptionNumber: The option number to be updated
 * INPUT: FText NewOptionText: The text to be displayed
 */
void UUIManager::SetRPEncounterOptionText(int OptionNumber, FText NewOptionText)
{
	if (!IsValid(RPEncounterWidgetInstance))
	{
		UE_LOG(LogTemp, Error, TEXT("UUIManager::SetRPEncounterOptionText: Invalid RPEncounterWidgetInstance on %s. Did you set it in the editor?"), *GetName());
		return;
	}

	URPEncounterWidget* RPEncounterWidget = Cast<URPEncounterWidget>(RPEncounterWidgetInstance);
	if (!IsValid(RPEncounterWidget))
	{
		UE_LOG(LogTemp, Error, TEXT("UUIManager::SetRPEncounterOptionText: Invalid RPEncounterWidget"));
		return;
	}

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
		UE_LOG(LogTemp, Error, TEXT("UUIManager::SetRPEncounterOptionText: Invalid option number"));
		break;
	}
}

void UUIManager::SetRPEncounterOptionVisibility(int OptionNumber, bool IsVisible)
{
	if (!IsValid(RPEncounterWidgetInstance))
	{
		UE_LOG(LogTemp, Error, TEXT("UUIManager::SetRPEncounterOptionVisibility: Invalid RPEncounterWidgetInstance on %s. Did you set it in the editor?"), *GetName());
		return;
	}
	URPEncounterWidget* RPEncounterWidget = Cast<URPEncounterWidget>(RPEncounterWidgetInstance);
	if (!IsValid(RPEncounterWidget))
	{
		UE_LOG(LogTemp, Error, TEXT("UUIManager::SetRPEncounterOptionVisibility: Invalid RPEncounterWidget"));
		return;
	}

	RPEncounterWidget->SetOptionVisibility(OptionNumber, IsVisible);
}

void UUIManager::StartPrologue()
{
	if (!IsValid(GM))
	{
		UE_LOG(LogTemp, Error, TEXT("UUIManager::StartPrologue: Invalid GM"));
		return;
	}

	UDialogueComponent* GMDialogueComponent = GM->GetDialogueComponent();
	if (!IsValid(GMDialogueComponent))
	{
		UE_LOG(LogTemp, Error, TEXT("UUIManager::StartPrologue: Invalid GMDialogueComponent"));
		return;
	}

	TArray<UDlgDialogue*> Dialogues = GMDialogueComponent->GetDialogues();
	TArray<UObject*> Participants = GMDialogueComponent->GetParticipants();

	if (Dialogues.Num() > 0)
	{
		GMDialogueComponent->StartDialogue(Dialogues[0], Participants);
	} 
	else 
	{ 
		UE_LOG(LogTemp, Error, TEXT("UUIManager::StartPrologue: No dialogues found on DialogueComponent")); 
		return;
	}
}

void UUIManager::SetRPEncounterAvatar(UMaterial* AvatarMaterial, FText AvatarName)
{
	if (!IsValid(RPEncounterWidgetInstance))
	{
		UE_LOG(LogTemp, Error, TEXT("UUIManager::SetRPEncounterAvatar: Invalid RPEncounterWidgetInstance on %s. Did you set it in the editor?"), *GetName());
		return;
	}

	URPEncounterWidget* RPEncounterWidget = Cast<URPEncounterWidget>(RPEncounterWidgetInstance);
	if (!IsValid(RPEncounterWidget))
	{
		UE_LOG(LogTemp, Error, TEXT("UUIManager::SetRPEncounterAvatar: Invalid RPEncounterWidget"));
		return;
	}

	RPEncounterWidget->SetAvatar(AvatarMaterial, AvatarName);
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
		UE_LOG(LogTemp, Error, TEXT("UUIManager::SelectDialogueOption: Invalid option number, must be between 1 and 4"));
		return;
	}
	if (!IsValid(DialogueOwnerComponent))
	{
		UE_LOG(LogTemp, Error, TEXT("UUIManager::SelectDialogueOption: Invalid DialogueOwnerComponent"));
		return;
	}

	bool HasReachedEndOfDialogue = !(DialogueOwnerComponent->SelectDialogueOption(OptionNumber));
	if (!HasReachedEndOfDialogue)
	{
		DialogueOwnerComponent->PopulateDialogueBodyText();
		DialogueOwnerComponent->PopulateDialogueOptionsText();
	}
	else
	{
		if (!IsValid(HUDWidgetInstance))
		{
			UE_LOG(LogTemp, Error, TEXT("UUIManager::SelectDialogueOption: Invalid HUDWidgetInstance on %s. Did you set it in the editor?"), *GetName());
			return;
		}
		DisplayWidget(HUDWidgetInstance);
	}
}


void UUIManager::LoadTradingInventoryWidgetContent(ULootBox* LootBox)
{
	if (!IsValid(TradingInventoryWidgetInstance))
	{
		UE_LOG(LogTemp, Error, TEXT("UUIManager::LoadTradingInventoryWidgetContent: Invalid TradingInventoryWidgetInstance"));
		return;
	}

	UTradingInventoryWidget* TradingInventoryWidget = Cast<UTradingInventoryWidget>(TradingInventoryWidgetInstance);
	if (!IsValid(TradingInventoryWidget))
	{
		UE_LOG(LogTemp, Error, TEXT("UUIManager::LoadTradingInventoryWidgetContent: Invalid TradingInventoryWidget"));
		return;
	}

	TradingInventoryWidget->LoadLootBoxInventoryUIContents(LootBox);
	TradingInventoryWidget->LoadPlayerInventoryUIContents();

	TradingInventoryWidget->SetLootBoxNameText(LootBox->GetLootBoxDisplayName());
}

void UUIManager::SetCurrentRoundText(int CurrentRound)
{
	if (!IsValid(CombatWidgetInstance))
	{
		UE_LOG(LogTemp, Error, TEXT("UUIManager::SetCurrentRoundText: Invalid CombatWidgetInstance"));
		return;
	}
	
	UCombatWidget* CombatWidget = Cast<UCombatWidget>(CombatWidgetInstance);
	if (!IsValid(CombatWidget))
	{
		UE_LOG(LogTemp, Error, TEXT("UUIManager::SetCurrentRoundText: Invalid CombatWidget"));
		return;
	}

	CombatWidget->SetCurrentRoundText(CurrentRound);
}

void UUIManager::SetEnemyInfo(AAvatar* EnemyAvatar, UMaterial* EnemyAvatarMaterial, FText EnemyName)
{
	if (!IsValid(CombatWidgetInstance))
	{
		UE_LOG(LogTemp, Error, TEXT("UUIManager::SetEnemyInfo: Invalid CombatWidgetInstance"));
		return;
	}

	UCombatWidget* CombatWidget = Cast<UCombatWidget>(CombatWidgetInstance);
	if (!IsValid(CombatWidget))
	{
		UE_LOG(LogTemp, Error, TEXT("UUIManager::SetEnemyInfo: Invalid CombatWidget"));
		return;
	}

	CombatWidget->SetEnemyAvatar(EnemyAvatar, EnemyAvatarMaterial);
	CombatWidget->SetEnemyName(EnemyName);
}

void UUIManager::SetEnemyHpPercent(float NormalizedPercent)
{
	if (!IsValid(CombatWidgetInstance))
	{
		UE_LOG(LogTemp, Error, TEXT("UUIManager::SetEnemyHpPercent: Invalid CombatWidgetInstance"));
		return;
	}

	UCombatWidget* CombatWidget = Cast<UCombatWidget>(CombatWidgetInstance);
	if (!IsValid(CombatWidget))
	{
		UE_LOG(LogTemp, Error, TEXT("UUIManager::SetEnemyHpPercent: Invalid CombatWidget"));
		return;
	}

	CombatWidget->SetEnemyHpBarPercent(NormalizedPercent);
}

void UUIManager::SetPlayerHpPercent(float NormalizedPercent)
{
	if (!IsValid(CombatWidgetInstance))
	{
		UE_LOG(LogTemp, Error, TEXT("UUIManager::SetPlayerHpPercent: Invalid CombatWidgetInstance"));
		return;
	}
	
	UCombatWidget* CombatWidget = Cast<UCombatWidget>(CombatWidgetInstance);
	if (!IsValid(CombatWidget))
	{
		UE_LOG(LogTemp, Error, TEXT("UUIManager::SetPlayerHpPercent: Invalid CombatWidget"));
		return;
	}

	CombatWidget->SetPlayerHpBarPercent(NormalizedPercent);
}

void UUIManager::SetCombatActionBtnsEnabled(bool IsEnabled)
{
	if (!IsValid(CombatWidgetInstance))
	{
		UE_LOG(LogTemp, Error, TEXT("UUIManager::SetCombatActionBtnsEnabled: Invalid CombatWidgetInstance"));
		return;
	}
	
	UCombatWidget* CombatWidget = Cast<UCombatWidget>(CombatWidgetInstance);
	if (!IsValid(CombatWidget))
	{
		UE_LOG(LogTemp, Error, TEXT("UUIManager::SetCombatActionBtnsEnabled: Invalid CombatWidget"));
		return;
	}

	CombatWidget->SetActionBtnsEnabled(IsEnabled);
}

void UUIManager::UpdatePlayerCombatActionButtons(TArray<class UDA_ItemAction*> AttackActions)
{
	if (!IsValid(CombatWidgetInstance))
	{
		UE_LOG(LogTemp, Error, TEXT("UUIManager::UpdatePlayerCombatActionButtons: Invalid CombatWidgetInstance"));
		return;
	}

	UCombatWidget* CombatWidget = Cast<UCombatWidget>(CombatWidgetInstance);
	if (!IsValid(CombatWidget))
	{
		UE_LOG(LogTemp, Error, TEXT("UUIManager::UpdatePlayerCombatActionButtons: Invalid CombatWidget"));
		return;
	}

	CombatWidget->SetUpAttackButtons(AttackActions);
}

void UUIManager::DisplayPreviousWidget()
{
	if (WidgetPathThroughMenusStack.Num() <= 1)
	{
		UE_LOG(LogTemp, Error, TEXT("UUIManager::DisplayPreviousWidget: WidgetPathThroughMenusStack only contains %d widgets"), WidgetPathThroughMenusStack.Num());
		return;
	}
	WidgetPathThroughMenusStack.RemoveAt(WidgetPathThroughMenusStack.Num() - 1);

	DisplayWidget(WidgetPathThroughMenusStack[WidgetPathThroughMenusStack.Num() - 1], false);
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
	if (!IsValid(MainMenuWidgetAssetRef))
	{
		UE_LOG(LogTemp, Error, TEXT("UUIManager::CreateUIWidgets: Invalid MainMenuWidgetAssetRef"));
		return;
	}
	if (!IsValid(PauseMenuWidgetAssetRef))
	{
		UE_LOG(LogTemp, Error, TEXT("UUIManager::CreateUIWidgets: Invalid PauseMenuWidgetAssetRef"));
		return;
	}
	if (!IsValid(OptionsMenuWidgetAssetRef))
	{
		UE_LOG(LogTemp, Error, TEXT("UUIManager::CreateUIWidgets: Invalid OptionsMenuWidgetAssetRef"));
		return;
	}
	if (!IsValid(AudioOptionsMenuWidgetAssetRef))
	{
		UE_LOG(LogTemp, Error, TEXT("UUIManager::CreateUIWidgets: Invalid AudioOptionsMenuWidgetAssetRef"));
		return;
	}
	if (!IsValid(RPEncounterWidgetAssetRef))
	{
		UE_LOG(LogTemp, Error, TEXT("UUIManager::CreateUIWidgets: Invalid RPEncounterWidgetAssetRef"));
		return;
	}
	if (!IsValid(CombatWidgetAssetRef))
	{
		UE_LOG(LogTemp, Error, TEXT("UUIManager::CreateUIWidgets: Invalid CombatWidgetAssetRef"));
		return;
	}
	//if (!IsValid(InventoryWidgetAssetRef))
	//{
	//	UE_LOG(LogTemp, Error, TEXT("UUIManager::CreateUIWidgets: Invalid InventoryWidgetAssetRef"));
	//	return;
	//}
	if (!IsValid(TradingInventoryWidgetAssetRef))
	{
		UE_LOG(LogTemp, Error, TEXT("UUIManager::CreateUIWidgets: Invalid TradingInventoryWidgetAssetRef"));
		return;
	}
	//if (!IsValid(MemoriesWidgetAssetRef))
	//{
	//	UE_LOG(LogTemp, Error, TEXT("UUIManager::CreateUIWidgets: Invalid MemoriesWidgetAssetRef"));
	//	return;
	//}
	if (!IsValid(GameMenuWidgetAssetRef))
	{
		UE_LOG(LogTemp, Error, TEXT("UUIManager::CreateUIWidgets: Invalid GameMenuWidgetAssetRef"));
		return;
	}
	if (!IsValid(HUDWidgetAssetRef))
	{
		UE_LOG(LogTemp, Error, TEXT("UUIManager::CreateUIWidgets: Invalid HUDWidgetAssetRef"));
		return;
	}
	if (!IsValid(QuitGameAlertWidgetAssetRef))
	{
		UE_LOG(LogTemp, Error, TEXT("UUIManager::CreateUIWidgets: Invalid QuitGameAlertWidgetAssetRef"));
		return;
	}
	if (!IsValid(NewGameAlertWidgetAssetRef))
	{
		UE_LOG(LogTemp, Error, TEXT("UUIManager::CreateUIWidgets: Invalid NewGameAlertWidgetAssetRef"));
		return;
	}
	if (!IsValid(CreditsWidgetAssetRef))
	{
		UE_LOG(LogTemp, Error, TEXT("UUIManager::CreateUIWidgets: Invalid CreditsWidgetAssetRef"));
		return;
	}

	// UI Screens
	MainMenuWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), MainMenuWidgetAssetRef);
	PauseMenuWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), PauseMenuWidgetAssetRef);
	OptionsMenuWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), OptionsMenuWidgetAssetRef);
	AudioOptionsMenuWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), AudioOptionsMenuWidgetAssetRef);
	RPEncounterWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), RPEncounterWidgetAssetRef);
	CombatWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), CombatWidgetAssetRef);
	TradingInventoryWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), TradingInventoryWidgetAssetRef);
	GameMenuWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), GameMenuWidgetAssetRef);
	CreditsWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), CreditsWidgetAssetRef);

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
	AddWidgetToWidgetSwitcher(TradingInventoryWidgetInstance);
	AddWidgetToWidgetSwitcher(GameMenuWidgetInstance);
	AddWidgetToWidgetSwitcher(CreditsWidgetInstance);
}

/*
 * Add a widget to the widget switcher.
 *
 * INPUT: UUserWidget* WidgetInstanceToAdd: The widget to be added to the WidgetSwitcher
 */
void UUIManager::AddWidgetToWidgetSwitcher(UUserWidget* WidgetInstanceToAdd)
{
	if (!IsValid(WidgetInstanceToAdd))
	{
		UE_LOG(LogTemp, Error, TEXT("UUIManager::AddWidgetToWidgetSwitcher: Invalid WidgetInstanceToAdd"));
		return;
	}
	if (!WidgetSwitcher)
	{
		UE_LOG(LogTemp, Error, TEXT("UUIManager::AddWidgetToWidgetSwitcher: Invalid WidgetSwitcher"));
		return;
	}

	WidgetSwitcher->AddChild(WidgetInstanceToAdd);
}

/*
 * Use the widget switcher to display a widget on screen
 *
 * INPUT: UUserWidget* WidgetInstanceToDisplay: The widget to be displayed
 * INPUT: bool DoAddToWidgetStack: Whether or not to add the widget to the widget stack. We do want to add it when diving deeper into a menu
 * and not when returning to a previous menu
 */
void UUIManager::DisplayWidget(UUserWidget* WidgetInstanceToDisplay, bool DoAddToWidgetStack)
{
	if (!IsValid(WidgetInstanceToDisplay))
	{
		UE_LOG(LogTemp, Error, TEXT("UUIManager::DisplayWidget: Invalid WidgetInstanceToDisplay"));
		return;
	}
	if (!IsValid(HUDWidgetInstance))
	{
		UE_LOG(LogTemp, Error, TEXT("UUIManager::DisplayWidget: Invalid HUDWidgetInstance"));
		return;
	}
	if (!WidgetSwitcher)
	{
		UE_LOG(LogTemp, Error, TEXT("UUIManager::DisplayWidget: Invalid WidgetSwitcher"));
		return;
	}

	if (WidgetInstanceToDisplay->Implements<UWidgetSwitchable>())
	{
		IWidgetSwitchable::Execute_PrepareToDisplay(GameMenuWidgetInstance);
	}

	APlayerController* PlayerController = Utility::GetFirstPlayerController(this);
	if (!IsValid(PlayerController))
	{
		UE_LOG(LogTemp, Error, TEXT("UUIManager::DisplayWidget: Invalid PlayerController"));
		return;
	}

	AActor* PlayerCharacterActor = GetOwner();
	if (!IsValid(PlayerCharacterActor))
	{
		UE_LOG(LogTemp, Error, TEXT("UUIManager::DisplayWidget: Invalid PlayerCharacterActor"));
		return;
	}

	AOdysseyCharacter* PlayerCharacter = Cast<AOdysseyCharacter>(GetOwner());
	if (!IsValid(PlayerCharacter))
	{
		UE_LOG(LogTemp, Error, TEXT("UUIManager::DisplayWidget: Invalid PlayerCharacter"));
		return;
	}

	WidgetSwitcher->SetActiveWidget(WidgetInstanceToDisplay);

	if (DoAddToWidgetStack)
	{
		WidgetPathThroughMenusStack.Add(WidgetInstanceToDisplay);
	}

	// When returning to game world from anywhere
	if (WidgetInstanceToDisplay == HUDWidgetInstance)
	{
		// Hide mouse cursor
		PlayerController->bShowMouseCursor = false;
		// Switch to exploration controls
		PlayerCharacter->ActivateExploreOrInteractMappingContext();
		// Clear widget stack
		WidgetPathThroughMenusStack.Empty();
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

