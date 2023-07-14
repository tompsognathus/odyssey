// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NPC.h"
#include "GM.generated.h"

/**
 * 
 */
UCLASS()
class ODYSSEY_API AGM : public ANPC
{
	GENERATED_BODY()
	
public:
	AGM();

	void StartPrologueDlg();


private:
	class UCharacterCreatorWidget* CharacterCreatorWidget;
};
