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
		Restarting,
	};
}

UCLASS()
class APlatformerGameMode : public AGameModeBase
{
	GENERATED_UCLASS_BODY()

public:

	/** prepare game state and show HUD message */
	void PrepareRound(bool bRestarting = false);

	/** used to start this round */
	void StartRound();

	/** finish current round */
	void FinishRound();

	/** is game paused? */
	bool IsGamePaused() const;

	/** pauses/unpauses the game */
	void SetGamePaused(bool bIsPaused);

	/** sets if round can be restarted */
	void SetCanBeRestarted(bool bAllowRestart);

	/** returns if round can be restarted */
	bool CanBeRestarted() const;

	void InitializeHUD();

	UFUNCTION(BlueprintCallable, Category = "Game")
	void UpdateHUD();

	/** 
	 * returns time that passed since round has started (in seconds)
	 * if the round has already ended returns round duration
	 */
	float GetRoundDuration();

	/** increases/decreases round duration by DeltaTime */
	void ModifyRoundDuration(float DeltaTime, bool bIncrease);

	/** returns true if round is in progress - player is still moving */
	bool IsRoundInProgress() const;

	/** returns true if round was won (best time) */
	bool IsRoundWon() const;

	/** get current state of game */
	EGameState::Type GetGameState() const;

	UFUNCTION(BlueprintCallable, Category = "Game")
	void AddPointsToScore(int32 Points) { PointsScore += Points; }

	/** delegate to broadcast about finished round */
	UPROPERTY(BlueprintAssignable)
	FRoundFinishedDelegate OnRoundFinished;

	UFUNCTION(BlueprintCallable, Category = "Game")
	int32 GetFinalScore() const { return FMath::Abs(PointsScore + GetTimeBonus()); }

	UFUNCTION(BlueprintCallable, Category = "Game")
	int32 GetTimeBonus() const { float val = (RoundTimeLimit - RoundDuration) * TimeBonusAmount; return FMath::Max(val,0); }

	UFUNCTION(BlueprintCallable, Category = "Game")
	int32 GetBestScore() const { 
		return UGameplayStatics::GetGameInstance(this)->GetSubsystem<UWpServerGlobals>()->BestScore;
	}

	UFUNCTION(BlueprintCallable, Category = "Game")
	float GetTimeRemaining() const { return RoundTimeLimit - RoundDuration; }

public:
	UMainHUDWidget* MainHUD;

private:
	float RoundTimeLimit = 60;
	int32 TimeBonusAmount = 1000;
	int32 PointsScore=0;
	float RoundDuration;

	/** Handle for efficient management of StartRound timer */
	FTimerHandle TimerHandle_StartRound;

	/** the time player started this round */
	//float RoundStartTime;

	/** true when round is in progress */
	EGameState::Type GameState;

	/** true if player won this round, false otherwise */
	uint32 bRoundWasWon:1;

	/** true if game is paused */
	uint32 bIsGamePaused:1;

	/** true if round can be restarted after finishing */
	uint32 bCanBeRestarted:1;
};

