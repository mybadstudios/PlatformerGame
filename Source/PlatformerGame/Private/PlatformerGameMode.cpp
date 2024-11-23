// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "UI/PlatformerGameMode.h"
#include "PlatformerGame.h"
#include "WpServerGlobals.h"
#include "Player/PlatformerPlayerController.h"
#include "Player/PlatformerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/GameInstance.h"

APlatformerGameMode::APlatformerGameMode(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void APlatformerGameMode::PrepareRound()
{
	GameState = EGameState::Waiting;
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

void APlatformerGameMode::AddPointsToScore(int32 Points) 
{ 
	PointsScore += Points; 
}

int32 APlatformerGameMode::GetFinalScore() const
{ 
	return FMath::Abs(PointsScore + GetTimeBonus()); 
}

int32 APlatformerGameMode::GetTimeBonus() const 
{
	float val = (RoundTimeLimit - RoundDuration) * TimeBonusAmount; return FMath::Max(val, 0); 
}

int32 APlatformerGameMode::GetBestScore() const 
{
	return UGameplayStatics::GetGameInstance(this)->GetSubsystem<UWpServerGlobals>()->BestScore;
}

float APlatformerGameMode::GetTimeRemaining() const 
{ 
	return RoundTimeLimit - RoundDuration; 
}
