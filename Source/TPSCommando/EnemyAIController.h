// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Soldier.h"
#include "AIController.h"
#include "GameFramework/Actor.h"
#include "EnemyAIController.generated.h"

class ASoldier;

UCLASS()
class TPSCOMMANDO_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
	APawn* PlayerPawn;

	ASoldier* MySoldier;
	void Fire();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
		UBehaviorTree* EnemyBHVR;
};
