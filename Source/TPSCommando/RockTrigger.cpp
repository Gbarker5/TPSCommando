// Fill out your copyright notice in the Description page of Project Settings.


#include "RockTrigger.h"
#include "Components/BoxComponent.h"

// Sets default values
ARockTrigger::ARockTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	CrackedMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TriggerMesh"));
	SetRootComponent(CrackedMesh);

	//Create Collision box for player to interact with and trigger projectile spawn
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	CollisionBox->SetBoxExtent(FVector(32.0f, 32.0f, 32.0f));
	CollisionBox->SetCollisionProfileName("Trigger");
	CollisionBox->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	CollisionBox->SetupAttachment(CrackedMesh);

	//Set spawn location high above trigger
	projectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Rock Spawn"));
	projectileSpawnPoint->SetupAttachment(CrackedMesh);
	projectileSpawnPoint->SetRelativeLocation(FVector(0, 0, 0));
}


//Called when the game starts or when spawned
void ARockTrigger::BeginPlay()
{
	Super::BeginPlay();
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ARockTrigger::OnOverlapBegin);
}

//Called every frame
void ARockTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//If player steps onto either trapped area boulder is spawned and given initial downward velocity to ensure instant kill on contact
void ARockTrigger::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (hasSpawned <= 0) //Do not allow trap to be triggered more than once (max of 2 boulders rolling around the level)
	{
		hasSpawned++;
		FVector location = projectileSpawnPoint->GetComponentLocation();
		FRotator rotation = projectileSpawnPoint->GetComponentRotation();

		GetWorld()->SpawnActor<ABoulder>(bigBoulder, location, rotation);
		UE_LOG(LogTemp, Warning, TEXT("Spawned Rock"));
	}
}
