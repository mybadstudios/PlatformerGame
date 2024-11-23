// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Kismet/GameplayStatics.h"
#include "WpServerGlobals.h"
#include "Engine/GameInstance.h"
#include "MainHUDWidget.h"
#include "PlatformerGameMode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FRoundFinishedDelegate);

namespace EGameState
{
	enum Type
	{
		Intro,
		Waiting,
		Playing,
		Finished,
	};
}

UCLASS()
class APlatformerGameMode : public AGameModeBase
{
	GENERATED_UCLASS_BODY()

public:
	/** prepare game state and show HUD message */
	void PrepareRound();

	/** used to start this round */
	void StartRound();

	/** finish current round */
	void FinishRound();

	void InitializeHUD();

	float GetRoundDuration();

	/** increases/decreases round duration by DeltaTime */
	void ModifyRoundDuration(float DeltaTime, bool bIncrease);

	/** returns true if round is in progress - player is still moving */
	bool IsRoundInProgress() const;

	/** returns true if round was won (best time) */
	bool IsRoundWon() const;

	/** get current state of game */
	EGameState::Type GetGameState() const;

public:
	/** delegate to broadcast about finished round */
	UPROPERTY(BlueprintAssignable)
	FRoundFinishedDelegate OnRoundFinished;


public:
	UFUNCTION(BlueprintCallable, Category = "Game")
	void UpdateHUD();

	UFUNCTION(BlueprintCallable, Category = "Game")
	void AddPointsToScore(int32 Points);

	UFUNCTION(BlueprintCallable, Category = "Game")
	int32 GetFinalScore() const;

	UFUNCTION(BlueprintCallable, Category = "Game")
	int32 GetTimeBonus() const;

	UFUNCTION(BlueprintCallable, Category = "Game")
	int32 GetBestScore() const;

	UFUNCTION(BlueprintCallable, Category = "Game")
	float GetTimeRemaining() const;

public:
	UMainHUDWidget* MainHUD = nullptr;

private:
	int32 TimeBonusAmount = 1000;
	int32 PointsScore = 0;

	float RoundTimeLimit = 60;
	float RoundDuration = 0;

	bool bRoundWasWon = false;

	EGameState::Type GameState = EGameState::Waiting;
};

