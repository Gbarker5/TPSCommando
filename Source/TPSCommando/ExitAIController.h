// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "GameFramework/Actor.h"
#include "ExitAIController.generated.h"


/**
 * 
 */
UCLASS()
class TPSCOMMANDO_API AExitAIController : public AAIController
{
	GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement variables")
    AActor* PlayerPawn;
protected:
    virtual void BeginPlay() override;
private:
    UPROPERTY()
        TArray<AActor*>exitPawns; //Allows use of GetAllActorsWithTag
};
