// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "TitlePawn.h"

// Sets default values
ATitlePawn::ATitlePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATitlePawn::BeginPlay()
{
	Super::BeginPlay();
	TitleUI = CreateWidget(GetWorld(), StartClass);

	if (TitleUI != nullptr)
	{
		TitleUI->AddToViewport();
	}
}

// Called every frame
void ATitlePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATitlePawn::StartGame() //Pawn that is autopossesed by player at title, game starts on player input
{
	UGameplayStatics::OpenLevel(GetWorld(), "main");
}

// Called to bind functionality to input
void ATitlePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) //Start Game on spacebar press
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &ATitlePawn::StartGame);

}

