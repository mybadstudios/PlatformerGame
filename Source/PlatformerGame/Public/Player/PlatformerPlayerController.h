// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "PlatformerPlayerController.generated.h"

UCLASS()
class APlatformerPlayerController : public APlayerController
{
	GENERATED_UCLASS_BODY()

public:

	/** try starting game **/
	UFUNCTION(BlueprintCallable, Category="Game")
	bool TryStartingGame();

protected:

	/** platformer in-game menu */
	TSharedPtr<class FPlatformerIngameMenu> PlatformerIngameMenu;
};
