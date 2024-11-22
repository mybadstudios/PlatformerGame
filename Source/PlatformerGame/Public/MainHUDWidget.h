// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "MainHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class PLATFORMERGAME_API UMainHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual bool Initialize() override;

public:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* BestScoreText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* CurrentScoreText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TimeText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TimeBonusText;

public :

	UFUNCTION(BlueprintCallable)
	void SetBestScore(int32 Score);

	UFUNCTION(BlueprintCallable)
	void SetCurrentScore(int32 Score);

	UFUNCTION(BlueprintCallable)
	void SetTime(int32 Time);

	UFUNCTION(BlueprintCallable)
	void SetTimeBonus(int32 TimeBonus);
	
};
