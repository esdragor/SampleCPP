// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "MakingMoneyUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class TRAININGCPP_API UMakingMoneyUserWidget : public UUserWidget
{
	GENERATED_BODY()

public :
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UProgressBar* MoneyProgressBar;

	void SetProgressBarPercent(float Percent);
};
