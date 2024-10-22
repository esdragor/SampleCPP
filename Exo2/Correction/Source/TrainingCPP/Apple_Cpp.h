// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Apple_Cpp.generated.h"
UCLASS()
class TRAININGCPP_API AApple_Cpp : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AApple_Cpp();
	void SetPhysics(bool enabled);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	//mesh component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh)
	UStaticMeshComponent* MeshComp;
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
