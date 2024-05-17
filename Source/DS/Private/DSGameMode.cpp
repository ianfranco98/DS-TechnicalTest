// Copyright Epic Games, Inc. All Rights Reserved.

#include "DSGameMode.h"
#include "DSCharacter.h"
#include "UObject/ConstructorHelpers.h"

ADSGameMode::ADSGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
