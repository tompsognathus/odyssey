// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetSwitchable.h"
#include "MemoriesWidget.generated.h"


UCLASS()
class ODYSSEY_API UMemoriesWidget : public UUserWidget, public IWidgetSwitchable
{
	GENERATED_BODY()

public:
	virtual void PrepareToDisplay_Implementation() override;
	
};
