// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MakingMoneyUserWidget.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "WorkZoneCpp.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMoneyGenerated);

UCLASS()
class TRAININGCPP_API AWorkZoneCpp : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWorkZoneCpp();
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collider)
	UBoxComponent* BoxComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	TSubclassOf<UUserWidget> WidgetClass;

	UMakingMoneyUserWidget* ActiveWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintAssignable, Category = "Money")
	FMoneyGenerated OnMoneyGenerated;

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
		class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
		class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void WorkActionStart();
	UFUNCTION()
	void WorkActionEnd();

	bool isWorking = false;
	float WorkTime = 0.0f;

	
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
