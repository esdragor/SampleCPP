// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Apple_Cpp.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "WorkZoneCpp.h"

#include "MyCharacterCpp.generated.h"


UCLASS()
class TRAININGCPP_API AMyCharacterCpp : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacterCpp();
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	USpringArmComponent* SpringArmComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	UCameraComponent* CameraComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh)
	USkeletalMeshComponent* MeshComp;

	//event Action Travail
	DECLARE_DELEGATE(FWorkAction);
	FWorkAction OnWorkAction;

	DECLARE_DELEGATE(FStopWorkAction);
	FStopWorkAction OnStopWorkAction;
	
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void PerformLineTrace();
	void SpawnApple();

	UFUNCTION()
	void OnMoneyGenerated();

	bool IsInBuyerRange = false;
	bool IsInWorkerRange = false;
	bool AppleSpawned = false;
	bool HasApple = false;
	UPROPERTY(EditAnywhere)
	int money = 0;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AApple_Cpp> AppleToSpawn = nullptr;

	AWorkZoneCpp* WorkZone = nullptr;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* PlayerInputMappingContext;

	// Références aux Input Actions
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* InteractAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* WorkAction;

	/*UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	AApple_Cpp* AppleClassToSpawn;*/

	AApple_Cpp* AppleCarried = nullptr;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void JumpActionTriggered();
	void InteractActionTriggered();
	void WorkActionTriggered();
	void StopWorkActionTriggered();
};
