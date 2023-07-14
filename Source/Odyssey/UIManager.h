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
	TSubclassOf<class UUserWidget> ParentUIWidgetAssetRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI Widgets")
	TSubclassOf<class UUserWidget> MainMenuWidgetAssetRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI Widgets")
	TSubclassOf<class UUserWidget> PauseMenuWidgetAssetRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI Widgets")
	TSubclassOf<class UUserWidget> OptionsMenuWidgetAssetRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI Widgets")
	TSubclassOf<class UUserWidget> RPEncounterWidgetAssetRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI Widgets")
	TSubclassOf<class UUserWidget> HUDWidgetAssetRef;

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
	void DisplayRPEncounterWidget();

	UFUNCTION(BlueprintCallable, Category = "UI Functions")
	void DisplayPreviousWidget();

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
		void SelectDialogueOption(int OptionNumber);


private:
	class AGM* GM;

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
	class UUserWidget* RPEncounterWidgetInstance;

	// Variable to hold the HUD Widget After Creating it
	class UUserWidget* HUDWidgetInstance;

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
