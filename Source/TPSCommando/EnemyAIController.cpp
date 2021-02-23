// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Soldier.h"

void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();

	//Get Player Character
	PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	if (Cast<ACharacter>(GetCharacter())) //If cast successful
	{
		MySoldier = Cast<ASoldier>(GetCharacter());
	}

	if (EnemyBHVR != nullptr) //Make sure enemy behavior tree exists
	{
		RunBehaviorTree(EnemyBHVR);
	}
}

void AEnemyAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerPosition"), PlayerPawn->GetActorLocation());

	//If Enemy can See player give them location, else clear the key
	if (LineOfSightTo(PlayerPawn))
	{
		GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerPosition"), PlayerPawn->GetActorLocation());
	}
	else
	{
		GetBlackboardComponent()->ClearValue(TEXT("PlayerPosition"));
	}
}

void AEnemyAIController::Fire() //Shoot at player and handle damage calculations in soldier class
{
	if (MySoldier)
	{
		MySoldier->Fire(FVector(0,0,0));
	}
}
