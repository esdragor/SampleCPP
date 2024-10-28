// Fill out your copyright notice in the Description page of Project Settings.


#include "WorkZoneCpp.h"

#include "MyCharacterCpp.h"
#include "Components/BoxComponent.h"

// Sets default values
AWorkZoneCpp::AWorkZoneCpp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	RootComponent = BoxComp;
	BoxComp->SetBoxExtent(FVector(100.f, 100.f, 100.f));
	BoxComp->SetCollisionProfileName(TEXT("Trigger"));
	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &AWorkZoneCpp::OnOverlapBegin); // Déclencheur d'entrée
	BoxComp->OnComponentEndOverlap.AddDynamic(this, &AWorkZoneCpp::OnOverlapEnd); // Déclencheur de sortie

	

}

// Called when the game starts or when spawned
void AWorkZoneCpp::BeginPlay()
{
	Super::BeginPlay();
	
}

void AWorkZoneCpp::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
	class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AMyCharacterCpp* Player = Cast<AMyCharacterCpp>(OtherActor);
	if (Player && (OtherActor != this))
	{
		//Bind the event
		Player->OnWorkAction.BindUObject(this, &AWorkZoneCpp::WorkActionStart);
		Player->OnStopWorkAction.BindUObject(this, &AWorkZoneCpp::WorkActionEnd);
		if (WidgetClass) // Vérifier si la classe de widget est définie
		{
			// Si un widget est déjà actif, le supprimer
			if (ActiveWidget)
			{
				ActiveWidget->RemoveFromParent();
				ActiveWidget = nullptr;
			}

			// Créer le widget et l'ajouter à l'écran
			ActiveWidget = CreateWidget<UMakingMoneyUserWidget>(GetWorld(), WidgetClass);
			UE_LOG(LogTemp , Warning, TEXT("In WorkZoneCpp"));
			if (ActiveWidget)
			{
				ActiveWidget->AddToViewport(); // Ajouter le widget à l'écran
				Player->IsInWorkerRange = true;
			}
		}
	}
}

void AWorkZoneCpp::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
							  class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AMyCharacterCpp* Player = Cast<AMyCharacterCpp>(OtherActor);
	if (Player && (OtherActor != this))
	{
		Player->IsInWorkerRange = false;
		WorkActionEnd();
		//Unbind the event
		Player->OnWorkAction.Unbind();
		Player->OnStopWorkAction.Unbind();
		if (WidgetClass) // Vérifier si la classe de widget est définie
		{
			// Si un widget est déjà actif, le supprimer
			if (ActiveWidget)
			{
				ActiveWidget->RemoveFromParent();
				ActiveWidget = nullptr;
				
			}
			UE_LOG(LogTemp , Warning, TEXT("Out WorkZoneCpp"));
		}
		//penser a annuler le travail si il sort de la zone pendant qu'il travaillez
	}
}

void AWorkZoneCpp::WorkActionStart()
{
	isWorking = true;
}

void AWorkZoneCpp::WorkActionEnd()
{
	isWorking = false;
}

// Called every frame
void AWorkZoneCpp::Tick(float DeltaTime)
{
	if (isWorking)
	{
		WorkTime += DeltaTime;
		
		if (WorkTime >= 5.f)
		{
			OnMoneyGenerated.Broadcast();
			WorkTime = 0.0f;
		}
	}
	else
	{
		WorkTime = 0.0f;
	}
	if(ActiveWidget) ActiveWidget->SetProgressBarPercent(WorkTime/5.f);
}



