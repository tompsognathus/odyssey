// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UIManager.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ODYSSEY_API UUIManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UUIManager();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void CreateParentUIWidget();


public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI Widgets")
	class ANPC* GM = nullptr;

	// Acceptable delay between clicks to count as a double click
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI Widgets")
	float DoubleClickTime = 0.25f;


	/***** UI Widget Assets *****/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI Widgets")
	TSubclassOf<class UUserWidget> ParentUIWidgetAssetRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI Widgets|Menus")
	TSubclassOf<class UUserWidget> MainMenuWidgetAssetRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI Widgets|Menus")
	TSubclassOf<class UUserWidget> PauseMenuWidgetAssetRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI Widgets|Menus")
	TSubclassOf<class UUserWidget> OptionsMenuWidgetAssetRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI Widgets|Menus")
	TSubclassOf<class UUserWidget> AudioOptionsMenuWidgetAssetRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI Widgets|Gameplay")
	TSubclassOf<class UUserWidget> RPEncounterWidgetAssetRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI Widgets|Gameplay")
	TSubclassOf<class UUserWidget> CombatWidgetAssetRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI Widgets|Gameplay")
	TSubclassOf<class UUserWidget> HUDWidgetAssetRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI Widgets|Inventory")
	TSubclassOf<class UUserWidget> InventoryWidgetAssetRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI Widgets|Inventory")
	TSubclassOf<class UUserWidget> TradingInventoryWidgetAssetRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI Widgets|Inventory")
	TSubclassOf<class UUserWidget> InventorySlotAssetRef;

	/* Alerts */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI Widgets|Alerts")
	TSubclassOf<class UUserWidget> QuitGameAlertWidgetAssetRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI Widgets|Alerts")
	TSubclassOf<class UUserWidget> NewGameAlertWidgetAssetRef;

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
	void DisplayCombatWidget(class ANPC* Enemy);

	UFUNCTION(BlueprintCallable, Category = "UI Functions")
	void DisplayInventoryWidget();

	UFUNCTION(BlueprintCallable, Category = "UI Functions")
	void DisplayTradingInventoryWidget(class ULootBox* LootBox);

	UFUNCTION(BlueprintCallable, Category = "UI Functions")
	void DisplayPreviousWidget();

	/***** UI Widget Getters *****/
	UFUNCTION(BlueprintCallable, Category = "UI Functions|Getters")
	class UUserWidget* const GetCombatWidgetInstance() { return CombatWidgetInstance; }

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
	void SetRPEncounterAvatar(UMaterial* AvatarMaterial);

	UFUNCTION()
	void SelectDialogueOption(int OptionNumber, UDialogueComponent* NPCDialogueOwner);

	UFUNCTION()
	void StartPrologue();

	/***** Trading Inventory UI Widget *****/
	UFUNCTION(BlueprintCallable, Category = "Trading Inventory")
	void LoadTradingInventoryWidgetContent(class ULootBox* LootBox);

	UFUNCTION(BlueprintCallable, Category = "Trading Inventory")
	void LoadPlayerInventoryWidgetContent();

	/***** Combat UI Widget *****/
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void SetCurrentRoundText(int CurrentRound);

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void SetEnemyInfo(UMaterial* EnemyAvatarMaterial, FText EnemyName);

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void SetEnemyHpPercent(float NormalizedPercent);

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void SetPlayerHpPercent(float NormalizedPercent);

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void SetCombatActionBtnsEnabled(bool IsEnabled);

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void UpdatePlayerCombatActionBtns(TArray<class UDA_ItemAction*> AttackActions);

private:
	class UCombatManager* CombatManager;

	/***** UI Widgets *****/

	// Variable to hold the Parent UI Widget After Creating it
	class UUserWidget* ParentUIWidgetInstance;

	// Variable to hold the Widget Switcher After Creating it
	class UWidgetSwitcher* WidgetSwitcher;

	// Variable to hold the Main Menu Widget After Creating it
	class UUserWidget* MainMenuWidgetInstance;

	// Variable to hold the Pause Menu Widget After Creating it
	class UUserWidget* PauseMenuWidgetInstance;

	// Variable to hold the Options Menu Widget After Creating it
	class UUserWidget* OptionsMenuWidgetInstance;

	// Variable to hold the Options Menu Widget After Creating it
	class UUserWidget* AudioOptionsMenuWidgetInstance;

	// Variable to hold the Options Menu Widget After Creating it
	class UUserWidget* RPEncounterWidgetInstance;

	// Variable to hold the Combat Widget After Creating it
	class UUserWidget* CombatWidgetInstance;

	// Variable to hold the HUD Widget After Creating it
	class UUserWidget* HUDWidgetInstance;

	// Variable to hold the Quit Game Alert Widget After Creating it
	class UUserWidget* InventoryWidgetInstance;

	// Variable to hold the Quit Game Alert Widget After Creating it
	class UUserWidget* TradingInventoryWidgetInstance;

	// Variable to hold the Quit Game Alert Widget After Creating it
	class UUserWidget* QuitGameAlertWidgetInstance;

	// Variable to hold the Quit Game Alert Widget After Creating it
	class UUserWidget* NewGameAlertWidgetInstance;

	// Remember what the previous UI widget was
	class UUserWidget* PreviousWidget = MainMenuWidgetInstance;


	void DisplayWidget(class UUserWidget* WidgetInstanceToDisplay);

	void SetUpUIWidgets();

	void CreateUIWidgets();

	void AddWidgetsToWidgetSwitcher();

	void AddWidgetToWidgetSwitcher(UUserWidget* WidgetInstanceToAdd);

};
