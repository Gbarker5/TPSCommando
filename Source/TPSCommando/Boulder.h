// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Boulder.generated.h"

class UBoxComponent;
UCLASS()
class TPSCOMMANDO_API ABoulder : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABoulder();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* RockMesh;
	UPROPERTY(EditAnywhere)
		UBoxComponent* CollisionBox;
	UPROPERTY()
		float MOVEMENT_SPEED = 1500.0f; //if labeled const editor gets unhappy...
	UPROPERTY(EditAnywhere)
		UProjectileMovementComponent* MVComponent;
	UFUNCTION()
		void HandleHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);
};
