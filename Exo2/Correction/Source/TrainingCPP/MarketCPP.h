// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MarketCPP.generated.h"

class UBoxComponent;

UCLASS()
class TRAININGCPP_API AMarketCPP : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMarketCPP();
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collider)
	UBoxComponent* BoxComp;

	
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	TSubclassOf<UUserWidget> WidgetClass;

	UUserWidget* ActiveWidget;
	

private:
	
	
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, 
						class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
						bool bFromSweep, const FHitResult& SweepResult);

	// Fonction appelée quand quelque chose quitte la zone
	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, 
					  class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	

};
