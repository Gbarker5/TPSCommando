// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TitlePawn.generated.h"

UCLASS()
class TPSCOMMANDO_API ATitlePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATitlePawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void StartGame();

	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> StartClass;
	UPROPERTY()
		UUserWidget* TitleUI;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
