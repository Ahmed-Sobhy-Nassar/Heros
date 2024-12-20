// Copyright Epic Games, Inc. All Rights Reserved.

#include "HerosGameMode.h"
#include "HerosCharacter.h"
#include "UObject/ConstructorHelpers.h"

AHerosGameMode::AHerosGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
