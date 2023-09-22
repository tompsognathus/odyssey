// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CombatWidget.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCombatActionRequested, UDA_ItemAction*, ItemAction);

class UImage;
class UTextBlock;
class UProgressBar;
class UUniformGridPanel;
class UUserWidget;
class UMaterial;
class UDA_ItemAction;
class UWBP_AttackBtn;
class UBorder;
class UCharSheet;
class AAvatar;

UCLASS()
class ODYSSEY_API UCombatWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Combat UI Functions")
	void SetEnemyAvatar(AAvatar* NewEnemyAvatar, UMaterial* AvatarMaterial);

	UFUNCTION(BlueprintCallable, Category = "Combat UI Functions")
	void SetEnemyName(FText& EnemyName);

	UFUNCTION(BlueprintCallable, Category = "Combat UI Functions")
	void SetCurrentRoundText(int CurrentRound);

	UFUNCTION(BlueprintCallable, Category = "Combat UI Functions")
	void SetEnemyHpBarPercent(float NormalizedPercent);

	UFUNCTION(BlueprintCallable, Category = "Combat UI Functions")
	void SetPlayerHpBarPercent(float NormalizedPercent);

	UFUNCTION(BlueprintCallable, Category = "Combat UI Functions")
	void SetUpAttackButtons(TArray<UDA_ItemAction*> AttackActions);

	UFUNCTION(BlueprintCallable, Category = "Combat UI Functions")
	void HighlightPlayerBorder();

	UFUNCTION(BlueprintCallable, Category = "Combat UI Functions")
	void HighlightEnemyBorder();

	UFUNCTION(BlueprintCallable, Category = "Combat UI Functions")
	void SetActionBtnsEnabled(bool IsEnabled);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Combat UI Functions")
	void ResolveCombatRound(float PlayerAttackDamage);

	void SetUpCombatantBindings(class UCharSheet* PlayerCharSheet, class UCharSheet* EnemyCharSheet);

	void RemoveCombatantBindings();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat UI")
	TSubclassOf<UUserWidget> AttackButtonAssetRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat UI")
	int NumButtonsPerRow = 4;

	FOnCombatActionRequested OnCombatActionRequestedDelegate;


protected:
	virtual void NativeConstruct() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat UI")
	FLinearColor HighlightedBorderBrushColor;

	/***** Bindings *****/
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UImage* EnemyAvatarImage;
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* EnemyNameTextBlock;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* CurrentRoundTextBlock;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UProgressBar* EnemyHpBar;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UProgressBar* PlayerHpBar;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UUniformGridPanel* PlayerActionGrid;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UBorder* PlayerBorder;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UBorder* EnemyBorder;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	UCharSheet* PlayerCharSheet;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	UCharSheet* EnemyCharSheet;

private:
	UFUNCTION()
	void HandleAttackButtonClicked(UWBP_AttackBtn* AttackBtn);

	UFUNCTION()
	void HandleAttackButtonHovered(UWBP_AttackBtn* AttackBtn);

	UFUNCTION()
	void HandleAttackButtonUnhovered(UWBP_AttackBtn* AttackBtn);

	UFUNCTION()
	void HandleCombatActionRequested(UDA_ItemAction* ItemAction);

	void HighlightBorder(UBorder* BorderToHighlight, UBorder* BorderToUnhighlight);

private:

	AAvatar* PlayerAvatar;
	AAvatar* EnemyAvatar;

	TArray<UWBP_AttackBtn*> AttackButtons = TArray<UWBP_AttackBtn*>();
	TArray<UDA_ItemAction*> AttackActions = TArray<UDA_ItemAction*>();

	FLinearColor DefaultBorderBrushColor;
	
};
