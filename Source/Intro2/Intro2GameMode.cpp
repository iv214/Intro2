// Copyright Epic Games, Inc. All Rights Reserved.

#include "Intro2GameMode.h"
#include "Intro2Character.h"
#include "UObject/ConstructorHelpers.h"

AIntro2GameMode::AIntro2GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
