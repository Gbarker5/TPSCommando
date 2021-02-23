// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Boulder.h"
#include "RockTrigger.generated.h"


class UBoxComponent;
UCLASS()
class TPSCOMMANDO_API ARockTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARockTrigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere)
		USceneComponent* projectileSpawnPoint;
	UPROPERTY(EditAnywhere)
		TSubclassOf<ABoulder> bigBoulder;
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* CrackedMesh;
	UPROPERTY(EditAnywhere)
		UBoxComponent* CollisionBox;
	UPROPERTY(EditAnywhere)
		int hasSpawned = 0;
	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
