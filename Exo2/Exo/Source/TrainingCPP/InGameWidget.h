// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InGameWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnButtonClicked, bool, IsClicked);

UCLASS()
class TRAININGCPP_API UInGameWidget : public UUserWidget
{
	GENERATED_BODY()

	UFUNCTION()
	virtual void NativeConstruct() override;


protected:
	UFUNCTION(BlueprintCallable)
	void OnButtonClicked();
	UFUNCTION()
	void OnButtonRedClicked(bool bIsClicked);
	UFUNCTION()
	void OnButtonBlueClicked(bool bIsClicked);
	
protected:
	UPROPERTY(BlueprintAssignable)
	FOnButtonClicked OnButtonClickedDelegate;
};
