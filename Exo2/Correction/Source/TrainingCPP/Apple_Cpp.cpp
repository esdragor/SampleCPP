// Fill out your copyright notice in the Description page of Project Settings.


#include "Apple_Cpp.h"

// Sets default values
AApple_Cpp::AApple_Cpp()
{
 	//mesh component
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	RootComponent = MeshComp;
	//setup physics
	MeshComp->SetSimulatePhysics(true);

}

void AApple_Cpp::SetPhysics(bool enabled)
{
	MeshComp->SetSimulatePhysics(enabled);
}

// Called when the game starts or when spawned
void AApple_Cpp::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AApple_Cpp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

