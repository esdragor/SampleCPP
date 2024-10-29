// Fill out your copyright notice in the Description page of Project Settings.


#include "DropZoneCpp.h"

#include "Apple_Cpp.h"
#include "MarketCPP.h"
#include "Blueprint/UserWidget.h"
#include "Components/BoxComponent.h"

// Sets default values
ADropZoneCpp::ADropZoneCpp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	RootComponent = BoxComp;
	BoxComp->SetBoxExtent(FVector(100.f, 100.f, 100.f));
	BoxComp->SetCollisionProfileName(TEXT("Trigger"));
	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &ADropZoneCpp::OnOverlapBegin); // Déclencheur d'entrée

}

// Called when the game starts or when spawned
void ADropZoneCpp::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADropZoneCpp::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
	class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AApple_Cpp* Apple = Cast<AApple_Cpp>(OtherActor);
	if (Apple && (OtherActor != this))
	{
		//add a log
		UE_LOG(LogTemp, Warning, TEXT("Apple is in the drop zone"));
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

// Called every frame
void ADropZoneCpp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

