// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UIManager.generated.h"

class UUserWidget;
class ANPC;
class ULootBox;
class UDA_ItemAction;
class UWidgetSwitcher;
class AAvatar;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ODYSSEY_API UUIManager : public UActorComponent
{
	GENERATED_BODY()

public:
	UUIManager();

	/***** UI Widget Functions *****/
	UFUNCTION(BlueprintCallable, Category = "UI Functions")
	void DisplayHUDWidgetOnly();

	UFUNCTION(BlueprintCallable, Category = "UI Functions")
	void DisplayMainMenuWidget();

	UFUNCTION(BlueprintCallable, Category = "UI Functions")
	void DisplayPauseMenuWidget();

	UFUNCTION(BlueprintCallable, Category = "UI Functions")
	void DisplayOptionsMenuWidget();

	UFUNCTION(BlueprintCallable, Category = "UI Functions")
	void DisplayAudioOptionsMenuWidget();

	UFUNCTION(BlueprintCallable, Category = "UI Functions")
	void DisplayRPEncounterWidget(UDialogueComponent* DialogueOwnerComponent);

	UFUNCTION(BlueprintCallable, Category = "UI Functions")
	void DisplayCombatWidget(ANPC* Enemy);

	UFUNCTION(BlueprintCallable, Category = "UI Functions")
	void DisplayTradingInventoryWidget(ULootBox* LootBox);

	UFUNCTION(BlueprintCallable, Category = "UI Functions")
	void DisplayGameMenuWidget();

	UFUNCTION(BlueprintCallable, Category = "UI Functions")
	void DisplayCreditsWidget();

	UFUNCTION(BlueprintCallable, Category = "UI Functions")
	void DisplayPreviousWidget();

	/***** UI Widget Getters *****/
	UFUNCTION(BlueprintCallable, Category = "UI Functions|Getters")
	UUserWidget* const GetCombatWidgetInstance() { return CombatWidgetInstance; }

	/***** Alert Functions *****/
	UFUNCTION(BlueprintCallable, Category = "UI Functions|Alerts")
	void OverlayQuitGameAlertWidget();

	UFUNCTION(BlueprintCallable, Category = "UI Functions|Alerts")
	void OverlayNewGameAlertWidget();

	UFUNCTION(BlueprintCallable, Category = "UI Functions|Alerts")
	void HideAllAlerts();

	/***** RP Encounter UI Widget *****/
	UFUNCTION()
	void SetRPEncounterBodyText(FText BodyText);

	UFUNCTION()
	void SetRPEncounterOptionText(int OptionNumber, FText NewOptionText);

	UFUNCTION()
	void SetRPEncounterOptionVisibility(int OptionNumber, bool IsVisible);

	UFUNCTION()
	void SetRPEncounterAvatar(UMaterial* AvatarMaterial, FText AvatarName);

	UFUNCTION()
	void SelectDialogueOption(int OptionNumber, UDialogueComponent* NPCDialogueOwner);

	UFUNCTION()
	void StartPrologue();

	/***** Trading Inventory UI Widget *****/
	UFUNCTION(BlueprintCallable, Category = "Trading Inventory")
	void LoadTradingInventoryWidgetContent(ULootBox* LootBox);

	//UFUNCTION(BlueprintCallable, Category = "Trading Inventory")
	//void LoadPlayerInventoryWidgetContent();

	/***** Combat UI Widget *****/
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void SetCurrentRoundText(int CurrentRound);

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void SetEnemyInfo(AAvatar* EnemyAvatar, UMaterial* EnemyAvatarMaterial, FText EnemyName);

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void SetEnemyHpPercent(float NormalizedPercent);

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void SetPlayerHpPercent(float NormalizedPercent);

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void SetCombatActionBtnsEnabled(bool IsEnabled);

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void UpdatePlayerCombatActionButtons(TArray<UDA_ItemAction*> AttackActions);

public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI Widgets")
	ANPC* GM = nullptr;

	// Acceptable delay between clicks to count as a double click
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI Widgets")
	float DoubleClickTime = 0.25f;

	/***** UI Widget Assets *****/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI Widgets")
	TSubclassOf<UUserWidget> ParentUIWidgetAssetRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI Widgets|Menus")
	TSubclassOf<UUserWidget> MainMenuWidgetAssetRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI Widgets|Menus")
	TSubclassOf<UUserWidget> PauseMenuWidgetAssetRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI Widgets|Menus")
	TSubclassOf<UUserWidget> OptionsMenuWidgetAssetRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI Widgets|Menus")
	TSubclassOf<UUserWidget> AudioOptionsMenuWidgetAssetRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI Widgets|Gameplay")
	TSubclassOf<UUserWidget> RPEncounterWidgetAssetRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI Widgets|Gameplay")
	TSubclassOf<UUserWidget> CombatWidgetAssetRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI Widgets|Gameplay")
	TSubclassOf<UUserWidget> HUDWidgetAssetRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI Widgets|Inventory")
	TSubclassOf<UUserWidget> TradingInventoryWidgetAssetRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI Widgets|Inventory")
	TSubclassOf<UUserWidget> InventorySlotAssetRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI Widgets|GameMenu")
	TSubclassOf<UUserWidget> GameMenuWidgetAssetRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI Widgets|Inventory")
	TSubclassOf<UUserWidget> MemoryCardAssetRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI Widgets|MainMenu")
	TSubclassOf<UUserWidget> CreditsWidgetAssetRef;

	/* Alerts */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI Widgets|Alerts")
	TSubclassOf<UUserWidget> QuitGameAlertWidgetAssetRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI Widgets|Alerts")
	TSubclassOf<UUserWidget> NewGameAlertWidgetAssetRef;


protected:
	virtual void BeginPlay() override;

	void CreateParentUIWidget();


private:
	void DisplayWidget(UUserWidget* WidgetInstanceToDisplay, bool DoAddToWidgetStack = true);

	void SetUpUIWidgets();

	void CreateUIWidgets();

	void AddWidgetsToWidgetSwitcher();

	void AddWidgetToWidgetSwitcher(UUserWidget* WidgetInstanceToAdd);

private:
	class UCombatManager* CombatManager;

	/***** Variables to hold UI Widgets Once They're Created *****/
	UUserWidget* ParentUIWidgetInstance;
	UWidgetSwitcher* WidgetSwitcher;

	UUserWidget* MainMenuWidgetInstance;
	UUserWidget* PauseMenuWidgetInstance;
	UUserWidget* OptionsMenuWidgetInstance;
	UUserWidget* AudioOptionsMenuWidgetInstance;
	UUserWidget* RPEncounterWidgetInstance;
	UUserWidget* CombatWidgetInstance;
	UUserWidget* HUDWidgetInstance;
	UUserWidget* TradingInventoryWidgetInstance;
	UUserWidget* GameMenuWidgetInstance;
	UUserWidget* QuitGameAlertWidgetInstance;
	UUserWidget* NewGameAlertWidgetInstance;
	UUserWidget* CreditsWidgetInstance;

	// Remember what the previous UI widget was
	TArray<UUserWidget*> WidgetPathThroughMenusStack;
};
