// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Actor.h"
#include "ExitPawn.generated.h"

class UBoxComponent;
class ATPSCommandoGameModeBase;

UCLASS()
class TPSCOMMANDO_API AExitPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AExitPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* ExitMesh;
	UPROPERTY(EditAnywhere)
		UBoxComponent* CollisionBox;
	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	UPROPERTY()
		ATPSCommandoGameModeBase* GameModeRef;
};
