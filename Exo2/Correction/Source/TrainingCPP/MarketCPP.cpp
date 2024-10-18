// Fill out your copyright notice in the Description page of Project Settings.


#include "MarketCPP.h"

#include "Blueprint/UserWidget.h"
#include "Components/BoxComponent.h"

// Sets default values
AMarketCPP::AMarketCPP()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	RootComponent = BoxComp;
	BoxComp->SetBoxExtent(FVector(100.f, 100.f, 100.f));
	BoxComp->SetCollisionProfileName(TEXT("Trigger"));
	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &AMarketCPP::OnOverlapBegin); // Déclencheur d'entrée
	BoxComp->OnComponentEndOverlap.AddDynamic(this, &AMarketCPP::OnOverlapEnd); // Déclencheur de sortie
}

// Called when the game starts or when spawned
void AMarketCPP::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMarketCPP::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
	class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//Log
	if (OtherActor && (OtherActor != this))
	{
		if (WidgetClass) // Vérifier si la classe de widget est définie
		{
			// Si un widget est déjà actif, le supprimer
			if (ActiveWidget)
			{
				ActiveWidget->RemoveFromParent();
				ActiveWidget = nullptr;
			}

			// Créer le widget et l'ajouter à l'écran
			ActiveWidget = CreateWidget<UUserWidget>(GetWorld(), WidgetClass);
			if (ActiveWidget)
			{
				ActiveWidget->AddToViewport(); // Ajouter le widget à l'écran
			}
		}
	}
}

void AMarketCPP::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
                              class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && (OtherActor != this))
	{
		if (WidgetClass) // Vérifier si la classe de widget est définie
		{
			// Si un widget est déjà actif, le supprimer
			if (ActiveWidget)
			{
				ActiveWidget->RemoveFromParent();
				ActiveWidget = nullptr;
			}
		}
	}
}



