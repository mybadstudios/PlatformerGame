// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "WpServerGlobals.h"
#include "WordPressGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "PlatformerGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PLATFORMERGAME_API UPlatformerGameInstance : public UWordPressGameInstance
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	bool ScoreIsLessThanHighScore(int32 ValueToTest) const 
	{
		auto SG = GetSubsystem<UWpServerGlobals>();
		if (!SG)
			return true;

		FString Key = FString::Printf(TEXT("%d_HighScore"), SG->GameId);
		return SG->FetchedInfo->GetInt(Key) > ValueToTest;
	}

	UFUNCTION(BlueprintCallable)
	int GetHighScore() const 
	{
		auto SG = GetSubsystem<UWpServerGlobals>();
		if (!SG)
		{
			return 0;
		}
		FString Key = FString::Printf(TEXT("%d_HighScore"), SG->GameId);
		return SG->FetchedInfo->GetInt(Key);
	}

	UFUNCTION(BlueprintCallable)
	void SetHighScoreLocally(int32 Value) 
	{
		auto SG = GetSubsystem<UWpServerGlobals>();
		if (!SG)
			return ;
		FString Key = FString::Printf(TEXT("%d_HighScore"), SG->GameId);
		SG->FetchedInfo->SetInt(Key, Value);
	}
};
