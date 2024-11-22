// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "Player/PlatformerPlayerController.h"
#include "PlatformerGame.h"
#include "Player/PlatformerPlayerCameraManager.h"
#include "UI/PlatformerGameMode.h"


APlatformerPlayerController::APlatformerPlayerController(const FObjectInitializer& ObjectInitializer) 
	: Super(ObjectInitializer)
{
	PlayerCameraManagerClass = APlatformerPlayerCameraManager::StaticClass();
	bEnableClickEvents = true;
	bEnableTouchEvents = true;
}

bool APlatformerPlayerController::TryStartingGame()
{
	APlatformerGameMode* MyGame = GetWorld()->GetAuthGameMode<APlatformerGameMode>();
	if (MyGame)
	{
		const EGameState::Type GameState = MyGame->GetGameState();
		switch (GameState)
		{
			case EGameState::Waiting:
				MyGame->StartRound();
				return true;

			case EGameState::Finished:
				return true;
		}
	}

	return false;
}
