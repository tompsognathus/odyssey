// Fill out your copyright notice in the Description page of Project Settings.


#include "GM.h"
#include "UIManager.h"

AGM::AGM()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AGM::StartPrologueDlg()
{
	StartDialogue(Dialogues[0], { this });

	if (UIManager)
	{
		UIManager->DisplayRPEncounterWidget(this);
		PopulateDialogueBodyText();
		PopulateDialogueOptionsText();

	}
	else { UE_LOG(LogTemp, Error, TEXT("UIManager not found")); }
}