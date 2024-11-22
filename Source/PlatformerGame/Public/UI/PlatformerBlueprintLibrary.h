// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "PlatformerBlueprintLibrary.generated.h"

UCLASS()
class UPlatformerBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

	/** switch to waiting state, player will be able to start race by himself */
	UFUNCTION(BlueprintCallable, Category=Game, meta=(WorldContext="WorldContextObject"))
	static void PrepareRace(class UObject* WorldContextObject);

	/** finish round, player will be able to replay, returns true when scoring new record */
	UFUNCTION(BlueprintCallable, Category=Game, meta=(WorldContext="WorldContextObject"))
	static bool FinishRace(class UObject* WorldContextObject);

	/** allow player to restart round */
	UFUNCTION(BlueprintCallable, Category=Game, meta=(WorldContext="WorldContextObject"))
	static void AllowToRestartRace(class UObject* WorldContextObject);

	/** allows changing round duration, while round is still in progress - used to give players time bonuses */
	UFUNCTION(BlueprintCallable, Category=Game, meta=(WorldContext="WorldContextObject"))
	static void DecreaseRoundDuration(class UObject* WorldContextObject, float DeltaTime);

	/** allows changing round duration, while round is still in progress - used to give players time bonuses */
	UFUNCTION(BlueprintCallable, Category = Game, meta = (WorldContext = "WorldContextObject"))
	void IncreaseBaseScore(UObject* WorldContextObject, int Amount);

	/** converts time to string in mm:ss.sss format */
	UFUNCTION(BlueprintPure, Category=HUD)
	static FString DescribeTime(float TimeSeconds, bool bShowSign = true);


};
