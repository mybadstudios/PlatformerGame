// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "UI/PlatformerBlueprintLibrary.h"
#include "PlatformerGame.h"
#include "UI/PlatformerGameMode.h"

UPlatformerBlueprintLibrary::UPlatformerBlueprintLibrary(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

APlatformerGameMode* GetGameFromContextObject(class UObject* WorldContextObject)
{
	UWorld* const MyWorld = GEngine->GetWorldFromContextObjectChecked(WorldContextObject);
	check(MyWorld);

	APlatformerGameMode* const MyGame = MyWorld->GetAuthGameMode<APlatformerGameMode>();
	return MyGame;
}

void UPlatformerBlueprintLibrary::PrepareRace(class UObject* WorldContextObject)
{
	APlatformerGameMode* const MyGame = GetGameFromContextObject(WorldContextObject);
	if (MyGame)
	{
		MyGame->PrepareRound();
	}
}

bool UPlatformerBlueprintLibrary::FinishRace(class UObject* WorldContextObject)
{
	bool bHasWon = false;

	APlatformerGameMode* MyGame = GetGameFromContextObject(WorldContextObject);
	if (MyGame)
	{
		MyGame->FinishRound();
		bHasWon = MyGame->IsRoundWon();
	}

	return bHasWon;
}

void UPlatformerBlueprintLibrary::DecreaseRoundDuration(class UObject* WorldContextObject, float DeltaTime)
{
	APlatformerGameMode* MyGame = GetGameFromContextObject(WorldContextObject);
	if (MyGame)
	{
		const float Delta = FMath::Abs(DeltaTime);
		MyGame->ModifyRoundDuration(Delta, (DeltaTime > 0) ? false : true);
	}
}

void UPlatformerBlueprintLibrary::IncreaseBaseScore(class UObject* WorldContextObject, int Amount)
{
	APlatformerGameMode* MyGame = GetGameFromContextObject(WorldContextObject);
	if (MyGame)
	{
		MyGame->AddPointsToScore(Amount);
	}
}

FString UPlatformerBlueprintLibrary::DescribeTime(float TimeSeconds, bool bShowSign)
{
	const float AbsTimeSeconds = FMath::Abs(TimeSeconds);
	const bool bIsNegative = (TimeSeconds < 0);

	const int32 TotalSeconds = FMath::TruncToInt(AbsTimeSeconds) % 3600;
	const int32 NumMinutes = TotalSeconds / 60;
	const int32 NumSeconds = TotalSeconds % 60;

	const int32 NumMiliSeconds = FMath::TruncToInt(FMath::Fractional(AbsTimeSeconds) * 1000.0f);

	FString TimeDesc = FString::Printf(TEXT("%s%02d:%02d.%03d"), 
		bShowSign ? (bIsNegative ? TEXT("-") : TEXT("+")) : TEXT(""),
		NumMinutes, NumSeconds, NumMiliSeconds);

	return TimeDesc;
}
