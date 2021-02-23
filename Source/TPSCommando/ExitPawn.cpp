// Fill out your copyright notice in the Description page of Project Settings.


#include "ExitPawn.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TPSCommandoGameModeBase.h"

// Sets default values
AExitPawn::AExitPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ExitMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ExitMesh"));
	SetRootComponent(ExitMesh);

	//Create a Trigger for the player to interact/overlap with
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	CollisionBox->SetBoxExtent(FVector(32.0f, 50.0f, 50.0f));
	CollisionBox->SetCollisionProfileName("Trigger");
	CollisionBox->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f));
	CollisionBox->SetupAttachment(ExitMesh);
}

//Called when the game starts or when spawned
void AExitPawn::BeginPlay()
{
	Super::BeginPlay();

	//Get reference to Game Mode class to access amount of enemies
	GameModeRef = Cast<ATPSCommandoGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AExitPawn::OnOverlapBegin);
}

//Player must kill all enemies such that enemyCount = 0, otherwise they cannot escape
void AExitPawn::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag(FName("CONTROLLER"))) 
	{
		if (GameModeRef->enemyCount <= 0)
		{
			//Player wins upon reaching exit with all targets elminated
			UE_LOG(LogTemp, Warning, TEXT("Win?"));
			UGameplayStatics::OpenLevel(GetWorld(), "Win");
		}
	}
}

