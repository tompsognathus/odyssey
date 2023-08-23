// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RPEncounterWidget.generated.h"

/**
 * 
 */
UCLASS()
class ODYSSEY_API URPEncounterWidget : public UUserWidget
{
	GENERATED_BODY()
	
private:
	class UUIManager* UIManager;
	class UDialogueComponent* DialogueOwner;

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UHUDWidget* HUDWidget;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* AdventureText;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UImage* AvatarImg;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* OptionText1;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* OptionText2;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* OptionText3;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* OptionText4;


	UFUNCTION(BlueprintCallable, Category = "UI Functions")
	void HandleOption1BtnClicked();

	UFUNCTION(BlueprintCallable, Category = "UI Functions")
	void HandleOption2BtnClicked();

	UFUNCTION(BlueprintCallable, Category = "UI Functions")
	void HandleOption3BtnClicked();

	UFUNCTION(BlueprintCallable, Category = "UI Functions")
	void HandleOption4BtnClicked();

public:
	UFUNCTION(BlueprintCallable, Category = "Text Fields")
	void SetBodyText(FText NewAdventureText);

	UFUNCTION(BlueprintCallable, Category = "Text Fields")
	void SetOptionText(int OptionNumber, FText NewOptionText);

	UFUNCTION(BlueprintCallable, Category = "Avatar Image")
	void SetAvatar(UMaterial* NewAvatarMaterial);

	UFUNCTION()
	void SetDialogueOwner(class UDialogueComponent* NewDialogueOwner) { DialogueOwner = NewDialogueOwner; }

	UFUNCTION()
	UHUDWidget* GetHUDWidget();

};
