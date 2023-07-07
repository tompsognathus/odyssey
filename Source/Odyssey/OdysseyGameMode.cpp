// Copyright Epic Games, Inc. All Rights Reserved.

#include "OdysseyGameMode.h"
#include "OdysseyCharacter.h"
#include "UObject/ConstructorHelpers.h"

AOdysseyGameMode::AOdysseyGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
