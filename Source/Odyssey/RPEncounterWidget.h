// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RPEncounterWidget.generated.h"

class UHUDWidget;
class UDialogueComponent;
class UImage;
class UTextBlock;
class UUIManager;
class UDialogueComponent;
class UButton;

UCLASS()
class ODYSSEY_API URPEncounterWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Text Fields")
	void SetBodyText(FText NewAdventureText);

	UFUNCTION(BlueprintCallable, Category = "Text Fields")
	void SetOptionText(int OptionNumber, FText NewOptionText);

	UFUNCTION(BlueprintCallable, Category = "Text Fields")
	void SetOptionVisibility(int OptionNumber, bool IsVisible);

	UFUNCTION(BlueprintCallable, Category = "Avatar Image")
	void SetAvatar(UMaterial* NewAvatarMaterial, FText NewAvatarName);

	void SetAvatarName(FText& NewAvatarName);

	void SetAvatarImage(UMaterial* NewAvatarMaterial);

	UFUNCTION()
	void SetDialogueOwner(class UDialogueComponent* NewDialogueOwner) { DialogueOwner = NewDialogueOwner; }

	UFUNCTION()
	UHUDWidget* GetHUDWidget();


protected:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable, Category = "UI Functions")
	void HandleOption1BtnClicked();

	UFUNCTION(BlueprintCallable, Category = "UI Functions")
	void HandleOption2BtnClicked();

	UFUNCTION(BlueprintCallable, Category = "UI Functions")
	void HandleOption3BtnClicked();

	UFUNCTION(BlueprintCallable, Category = "UI Functions")
	void HandleOption4BtnClicked();

protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UHUDWidget* HUDWidget;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* AdventureText;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UImage* AvatarImg;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* AvatarName;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* OptionBtn1;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* OptionBtn2;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* OptionBtn3;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* OptionBtn4;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* OptionText1;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* OptionText2;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* OptionText3;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* OptionText4;

private:
	UUIManager* UIManager;
	UDialogueComponent* DialogueOwner;
};
