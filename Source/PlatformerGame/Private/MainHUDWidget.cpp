// Fill out your copyright notice in the Description page of Project Settings.


#include "MainHUDWidget.h"
#include "UI/PlatformerGameMode.h"
#include "Kismet/GameplayStatics.h"

bool UMainHUDWidget::Initialize()
{
	bool bResult = Super::Initialize();

	auto GameMode = (APlatformerGameMode*) GetWorld()->GetAuthGameMode();
	if (GameMode)
	{
		GameMode->MainHUD = this;
		GameMode->InitializeHUD();
	}
	return bResult;
}

void UMainHUDWidget::SetBestScore(int32 Score)
{
	if (BestScoreText)
	{
		BestScoreText->SetText(FText::FromString(FString::FromInt(Score)));
	}
}

void UMainHUDWidget::SetCurrentScore(int32 Score)
{
	if (CurrentScoreText)
	{
		CurrentScoreText->SetText(FText::FromString(FString::FromInt(Score)));
	}
}

void UMainHUDWidget::SetTime(int32 Time)
{
	if (TimeText)
	{
		TimeText->SetText(FText::FromString(FString::FromInt(Time)));
	}
}

void UMainHUDWidget::SetTimeBonus(int32 TimeBonus)
{
	if (TimeBonusText)
	{
		TimeBonusText->SetText(FText::FromString(FString::FromInt(TimeBonus)));
	}
}
