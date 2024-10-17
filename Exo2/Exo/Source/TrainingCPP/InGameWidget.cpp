// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameWidget.h"

void UInGameWidget::OnButtonRedClicked(bool bIsClicked)
{
	UE_LOG(LogTemp, Warning, TEXT("Button Red Clicked"));
}

void UInGameWidget::OnButtonBlueClicked(bool bIsClicked)
{
	UE_LOG(LogTemp, Warning, TEXT("Button Blue Clicked"));
}

void UInGameWidget::NativeConstruct()
{
	Super::NativeConstruct();

	OnButtonClickedDelegate.AddDynamic(this, &UInGameWidget::OnButtonRedClicked);
}

void UInGameWidget::OnButtonClicked()
{
	OnButtonClickedDelegate.Broadcast(true);
}
