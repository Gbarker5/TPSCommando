// Fill out your copyright notice in the Description page of Project Settings.


#include "Boulder.h"
#include"Soldier.h"

// Sets default values
ABoulder::ABoulder()
{
	// Set this actor to call Tick() every frame. You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Setup the Boulder
	RockMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RockMesh"));
	SetRootComponent(RockMesh);

	//Allow Boulder to influenced by physics
	RockMesh->SetSimulatePhysics(true);
	RockMesh->SetNotifyRigidBodyCollision(true);

	//Give Boulder initial velocity when player steps in "trap" to make it more difficult to avoid
	MVComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("PMVComponent"));
	MVComponent->MaxSpeed = MOVEMENT_SPEED;
	MVComponent->InitialSpeed = MOVEMENT_SPEED;
}

// Called when the game starts or when spawned
void ABoulder::BeginPlay()
{
	Super::BeginPlay();
	OnActorHit.AddDynamic(this, &ABoulder::HandleHit); //Allow Boulder to apply damage on collisions

}

// Called every frame
void ABoulder::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Workaround to deal with a lack of friction
	if (MVComponent->Velocity.IsNearlyZero())
	{
		MVComponent->Velocity = FVector(0, 0, 0);
	}

}

void ABoulder::HandleHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	//If boulder hits player or enemy apply damage scaled by the impulse
	if (OtherActor->GetClass()->IsChildOf(ASoldier::StaticClass()))
	{
		//abs prevents negative values "adding health"
		float normalImpulseAvg = abs(NormalImpulse.X) + abs(NormalImpulse.Y) + abs(NormalImpulse.Z) / 3.0f;
		float damagetoApply = 0.00005f * normalImpulseAvg;

		if (damagetoApply < 0)
		{
			damagetoApply = 0;
		}

		UGameplayStatics::ApplyDamage(OtherActor, damagetoApply, this->GetInstigatorController(), this, UDamageType::StaticClass());
	}
}

