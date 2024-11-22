// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "UI/PlatformerGameMode.h"
#include "PlatformerGame.h"
#include "WpServerGlobals.h"
#include "Player/PlatformerPlayerController.h"
#include "Player/PlatformerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/GameInstance.h"

APlatformerGameMode::APlatformerGameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PlayerControllerClass = APlatformerPlayerController::StaticClass();
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClass(TEXT("/Game/Pawn/PlayerPawn"));
	DefaultPawnClass = PlayerPawnClass.Class;

	GameState = EGameState::Intro;
	bRoundWasWon = false;
	RoundDuration = 0.0f;
	bIsGamePaused = false;
	if ((GEngine != NULL) && (GEngine->GameViewport != NULL))
	{
		GEngine->GameViewport->SetSuppressTransitionMessage(true);
	}
}

void APlatformerGameMode::PrepareRound(bool bRestarting)
{
	if (bRestarting)
	{
		OnRoundFinished.Broadcast();
	}	

	GameState = bRestarting ? EGameState::Restarting : EGameState::Waiting;
	bRoundWasWon = false;
	RoundDuration = 0.0f;
	
	APlatformerPlayerController* PC = Cast<APlatformerPlayerController>(GEngine->GetFirstLocalPlayerController(GetWorld()));
	APlatformerCharacter* Pawn = PC ? Cast<APlatformerCharacter>(PC->GetPawn()) : NULL;
	if (Pawn)
	{
		AActor* StartSpot = FindPlayerStart(PC);
		Pawn->TeleportTo(StartSpot->GetActorLocation(), StartSpot->GetActorRotation());

		if (Pawn->IsHidden())
		{
			Pawn->SetActorHiddenInGame(false);
		}
	}
}

void APlatformerGameMode::SetCanBeRestarted(bool bAllowRestart)
{
	if (GameState == EGameState::Finished)
	{
		bCanBeRestarted = bAllowRestart;
	}
}

bool APlatformerGameMode::CanBeRestarted() const
{
	return (GameState == EGameState::Finished && bCanBeRestarted);
}

void APlatformerGameMode::InitializeHUD()
{
	MainHUD->SetBestScore(GetBestScore());
	MainHUD->SetCurrentScore(0);
	MainHUD->SetTime(RoundTimeLimit);
	MainHUD->SetTimeBonus(static_cast<int>(RoundTimeLimit * 1000));
}

void APlatformerGameMode::UpdateHUD()
{
	const float TimeRemaining = RoundTimeLimit - GetRoundDuration();
	MainHUD->SetCurrentScore(GetFinalScore());
	MainHUD->SetTime(TimeRemaining);
	MainHUD->SetTimeBonus(GetTimeBonus());
}


void APlatformerGameMode::StartRound()
{
	RoundDuration = 0.0f;
	GameState = EGameState::Playing;
}

void APlatformerGameMode::FinishRound()
{
	GameState = EGameState::Finished;
	
	// determine game state
	bRoundWasWon = GetFinalScore() >= GetBestScore();

	// notify player
	APlayerController* PC = GEngine->GetFirstLocalPlayerController(GetWorld());
	APlatformerCharacter* Pawn = PC ? Cast<APlatformerCharacter>(PC->GetPawn()) : NULL;
	if (Pawn)
	{
		Pawn->OnRoundFinished();
	}
}

void APlatformerGameMode::ModifyRoundDuration(float DeltaTime, bool bIncrease)
{
	if (IsRoundInProgress())
	{
		const float Delta = FMath::Abs(DeltaTime);
		if (bIncrease)
		{
			RoundDuration += Delta;
		}
		else
		{
			RoundDuration -= Delta;
		}
	}
}

float APlatformerGameMode::GetRoundDuration() 
{
	if (IsRoundInProgress())
	{
		RoundDuration += GetWorld()->GetDeltaSeconds();
	}
	return RoundDuration;
}

void APlatformerGameMode::SetGamePaused(bool bIsPaused)
{
	APlayerController* PC = GEngine->GetFirstLocalPlayerController(GetWorld());
	PC->SetPause(bIsPaused);
	bIsGamePaused = bIsPaused;
}

bool APlatformerGameMode::IsGamePaused() const
{
	return bIsGamePaused;
}

bool APlatformerGameMode::IsRoundInProgress() const
{
	return GameState == EGameState::Playing;
}

bool APlatformerGameMode::IsRoundWon() const
{
	return bRoundWasWon;
}

EGameState::Type APlatformerGameMode::GetGameState() const
{
	return GameState;
}
