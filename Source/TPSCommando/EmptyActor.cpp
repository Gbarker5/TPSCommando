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


#include "EmptyActor.h"

// Sets default values
AEmptyActor::AEmptyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AEmptyActor::BeginPlay()
{
	Super::BeginPlay();	
}

// Called every frame
void AEmptyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

