// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacterCpp.h"

#include "Apple_Cpp.h"
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

	MeshComp = this->GetMesh();
	
	//setup a Arms mesh to see the character
	MeshComp->SetSkeletalMesh(LoadObject<USkeletalMesh>(nullptr, TEXT("SkeletalMesh'/Game/FirstPersonArms/Character/Mesh/SK_Mannequin_Arms.SK_Mannequin_Arms'")));
	MeshComp->SetupAttachment(RootComponent);
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
	if(IsInBuyerRange && !AppleSpawned)
	{
		SpawnApple();
		
		//enlever les thunes
	}
	PerformLineTrace();

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

void AMyCharacterCpp::PerformLineTrace()
{
	// Obtenir le point de départ et de fin du line trace
	FVector Start = GetActorLocation(); // Point de départ à partir de la position de l'acteur
	Start.Z += 50.0f; // Ajouter une hauteur pour éviter de toucher l'acteur lui-même
	// Obtenir la direction vers laquelle la camera regarde
	FRotator Rotation = GetControlRotation();
	FRotator YawRotation(Rotation.Pitch, Rotation.Yaw, 0);
	FVector ForwardVector = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	FVector End = Start + (ForwardVector * 300.0f); // 1000 unités devant l'acteur

	// Paramètres pour le line trace
	FHitResult OutHit;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this); // Ignorer l'acteur qui effectue le trace

	// Faire le line trace
	bool bHit = GetWorld()->LineTraceSingleByChannel(
		OutHit,      // Résultat du hit
		Start,          // Point de départ
		End,            // Point de fin
		ECC_Visibility, // Canal de collision (ici visibilité)
		CollisionParams // Paramètres de collision
	);
	if (HasApple)
	{
		// Lâcher la pomme
		AppleCarried->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
			
			
		AppleCarried->SetPhysics(true);
		AppleCarried->SetCollisions(true);
		AppleCarried = nullptr;
		HasApple = false;
	}
	// Si un objet est touché
	if (bHit)
	{
		// Si l'objet touché est une instance de AApple_Cpp
		if (!HasApple)
		{
			AppleCarried = Cast<AApple_Cpp>(OutHit.GetActor());
			if(AppleCarried && AppleCarried->IsValidLowLevelFast())
			{
				AppleCarried->SetPhysics(false);
				AppleCarried->SetCollisions(false);
				// Attacher la pomme à l'acteur via un socket skeletal mesh
				
				
				
				AppleCarried->AttachToComponent(MeshComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale, "hand_r");
				//disable les collisions
				
				

				//UE_LOG(LogTemp, Warning, TEXT("Pomme attachée à : %s"), *AppleCarried->GetParentComponent()->GetName());

				HasApple = true;
			}
		}
		
		
		
		// Dessiner le trace dans le monde (facultatif, pour debug)
		DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 1, 0, 5);
	}
	
	else
	{
		
		// Si aucun objet n'est touché, dessiner le trace sans hit
		DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 1, 0, 5);
	}
}

void AMyCharacterCpp::SpawnApple()
{
	AppleSpawned = true;
	// Créer une instance de AApple_Cpp
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	
	
	FVector SpawnLocation = GetActorLocation();
	SpawnLocation += GetActorForwardVector() * 100.f;
	GetWorld()->SpawnActor(AppleToSpawn, &SpawnLocation, nullptr, SpawnParams);
}

