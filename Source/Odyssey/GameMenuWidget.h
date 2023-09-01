// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetSwitchable.h"
#include "GameMenuWidget.generated.h"

class UWidgetSwitcher;
class UUIManager;

UCLASS()
class ODYSSEY_API UGameMenuWidget : public UUserWidget, public IWidgetSwitchable
{
	GENERATED_BODY()
	

public:
	virtual void PrepareToDisplay_Implementation() override;

protected:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable, Category = "UI Widgets")
	void HandleNextButtonClicked();

	UFUNCTION(BlueprintCallable, Category = "UI Widgets")
	void HandlePreviousButtonClicked();

protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UWidgetSwitcher* WidgetSwitcher;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI Widgets")
	TArray<TSubclassOf<UUserWidget>> WidgetsRefsArray;


private:
	void SetUpUIWidgets();
	void AddWidgetsToWidgetSwitcher();
	void AddWidgetToWidgetSwitcher(UUserWidget* WidgetInstanceToAdd);
	void DisplayWidget(int Index);

private:
	UUIManager* UIManager;
	TArray<UUserWidget*> WidgetsArray = TArray<UUserWidget*>();
	int CurrentWidgetIndex = 0;
};
