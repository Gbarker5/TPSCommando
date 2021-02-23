// Fill out your copyright notice in the Description page of Project Settings.

//
//
//
//
/*This Actor is exactly as implied. It has no functional purpose other to act as a target for the exit sign
FOr some reason "LookAt" Refuses to work on the main player so this actor is attached and becomes the target instead */
//
//
//

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EmptyActor.generated.h"

UCLASS()
class TPSCOMMANDO_API AEmptyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEmptyActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
