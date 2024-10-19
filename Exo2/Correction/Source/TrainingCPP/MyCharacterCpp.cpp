// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacterCpp.h"
#include "Components/InputComponent.h"
#include "GameFramework/Controller.h"

// Sets default values
AMyCharacterCpp::AMyCharacterCpp()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->TargetArmLength = 400.f;
	
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(SpringArmComp);

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetupAttachment(RootComponent);
	//setup a capsule mesh to see the character
	MeshComp->SetStaticMesh(ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'")).Object);

}

// Called when the game starts or when spawned
void AMyCharacterCpp::BeginPlay()
{
	Super::BeginPlay();
	//log hello world
	
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		// Ajouter l'Input Mapping Context à l'Enhanced Input System
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(PlayerInputMappingContext, 0); // Priorité 0 pour ce contexte
		}
	}
	
}



// Called every frame
void AMyCharacterCpp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}
void AMyCharacterCpp::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// Ajouter un mouvement en avant/arrière
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);

		// Ajouter un mouvement de gauche à droite
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void AMyCharacterCpp::Look(const FInputActionValue& Value)
{
	FVector2D LookVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// Ajouter un mouvement de la souris en Y
		AddControllerPitchInput(LookVector.Y);

		// Ajouter un mouvement de la souris en X
		AddControllerYawInput(LookVector.X);
	}
}

void AMyCharacterCpp::JumpActionTriggered()
{
	Jump();
}

void AMyCharacterCpp::InteractActionTriggered()
{
	if(IsInBuyerRange && !HasApple)
	{
		HasApple = true;
		UE_LOG(LogTemp, Warning, TEXT("You have an apple"));
		//enlever les thunes
	}
}

// Called to bind functionality to input
void AMyCharacterCpp::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	
	
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Assigner l'Action de déplacement à une fonction
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMyCharacterCpp::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMyCharacterCpp::Look);
        
		// Assigner l'Action de saut à une fonction
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &AMyCharacterCpp::JumpActionTriggered);
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &AMyCharacterCpp::InteractActionTriggered);
	}

}



