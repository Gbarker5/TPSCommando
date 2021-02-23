// Fill out your copyright notice in the Description page of Project Settings.


#include "Soldier.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/DamageType.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "TPSCommandoGameModeBase.h"
#include "Components/SceneCaptureComponent2D.h"

// Sets default values
ASoldier::ASoldier()
{
	// Set this character to call Tick() every frame. You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	charMesh = this->GetMesh(); //Get Character Mesh reference to attach components to

	//Setup SpringArm to prevent camera going behind walls 
	springArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	springArmComponent->SetupAttachment(charMesh);
	springArmComponent->bEnableCameraLag = true;
	springArmComponent->TargetArmLength = 300.0f;
	springArmComponent->SetRelativeRotation((new FRotator(-30.0f, 0.0f, 0.0f))->Quaternion());
	springArmComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));

	//Create camera and attack to SpringArm
	camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	camera->SetupAttachment(springArmComponent);

	//Create SpringArm and Camera for MiniMap (RenderTarget2D + UIWidgets)
	MapArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Map Arm"));
	MapArmComponent->SetupAttachment(charMesh);
	MapCamera = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("MapCamera"));
	MapCamera->SetupAttachment(MapArmComponent);
	MapCamera->SetRelativeRotation(FRotator(-90.0f, 0.0f, 0.0f));

	ASoldier::shouldCrouch = false;
	ASoldier::wantsToFire = false;
}

// Called when the game starts or when spawned
void ASoldier::BeginPlay()
{
	Super::BeginPlay();
	GameModeRef = Cast<ATPSCommandoGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	//Make enemies move 2x slower than player to allow for player escape when being chased
	if (this->ActorHasTag(FName("ENEMY")))
	{
		UCharacterMovementComponent* CharMove = this->GetCharacterMovement();
		CharMove->MaxWalkSpeed /= 2;
	}
}

// Called every frame
void ASoldier::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

//Called to bind functionality to input
void ASoldier::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("MoveForwards"), this, &ASoldier::MoveForwards);
	PlayerInputComponent->BindAxis(TEXT("Strafe"), this, &ASoldier::Strafe);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &ASoldier::LookUp);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ASoldier::Turn);
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &ASoldier::DoJump);
	PlayerInputComponent->BindAction(TEXT("Crouch"), IE_Pressed, this, &ASoldier::doCrouch);
}

float ASoldier::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EVentInstigator, AActor* DamageCauser)
{
	if (!isDead) //Prevent undefined behaviour and weird animations caused by playermovement
	{
		if (Health - DamageAmount < 0)
			Health = 0.0f;
		else
			Health -= DamageAmount;

		if (Health <= 0.0f) //Prevent negative health values in UI
		{
			//Kill Character, and call appropriate function if enemy or player
			if (this->ActorHasTag(FName("ENEMY")))
			{
				charMesh->PlayAnimation(Death, false);
				//Prevent undefined behaviour caused by animations still trying to play after character destruction
				GetWorld()->GetTimerManager().SetTimer(DeathTimer, this, &ASoldier::Die, deathTime, false);
			}
			else if (this->ActorHasTag(FName("CONTROLLER")))
			{
				AController* ControllerRef = GetController();
				isDead = true;
				charMesh->PlayAnimation(Death, false);
				GetWorld()->GetTimerManager().SetTimer(DeathTimer, this, &ASoldier::EndGame, deathTimePlayer, false);
			}
		}
	}
	return 0.0;
}

void ASoldier::Die() //Reduce Enemy count by 1 and disable Enemy
{
	for (int i = 0; i < WeaponActors.Num(); i++)
	{
		WeaponActors[i]->SetActorHiddenInGame(true);
		WeaponActors[i]->SetActorEnableCollision(false);
		WeaponActors[i]->Destroy();
	}
	SetActorTickEnabled(false);
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
	GameModeRef->SubtractEnemy();
	Destroy();
}

void ASoldier::EndGame() //Kill player, play death animation then transition to Lose Screen
{
	SetActorTickEnabled(false);
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
	UGameplayStatics::OpenLevel(GetWorld(), "Lose");
}

void ASoldier::DoJump()
{
	if (!isDead)
		Jump();
}


void ASoldier::Fire(FVector Location)
{
	FVector jumpVelocity = this->GetVelocity();
	if (!wantsToFire && !bIsCrouched && jumpVelocity.Z == 0 && !isDead) //Prevent shooting while in air, crouched or falling (obviously if dead too)
	{
		AController* ControllerRef = GetController();
		FVector CameraLocation;
		FRotator CameraRotation;
		ControllerRef->GetPlayerViewPoint(CameraLocation, CameraRotation);

		float CastRange = 10000.0f;
		FVector End = CameraLocation + CameraRotation.Vector() * CastRange;

		FHitResult Hit;
		bool bDidHit = false;

		//Do Raycast on different channel based on player or enemy (prevents raycast hitting back of character head/model)
		if (this->ActorHasTag(FName("CONTROLLER")))
		{
			bDidHit = GetWorld()->LineTraceSingleByChannel(Hit, CameraLocation, End, ECC_GameTraceChannel1);
			UGameplayStatics::PlaySound2D(GetWorld(), shootFX);
		}
		else
		{
			//Give enemies exact player location when doing a cast for maximum accuracy
			bDidHit = GetWorld()->LineTraceSingleByChannel(Hit, CameraLocation, Location, ECC_GameTraceChannel2);
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), shootFX, this->GetActorLocation(), 1.0f, 1.0f);
		}

		if (bDidHit)
		{
			UE_LOG(LogTemp, Warning, TEXT("Hit?"));
			AActor* hitActor;
			if (Hit.GetActor() != nullptr)
			{
				hitActor = Hit.GetActor();
				if (hitActor->IsValidLowLevel()) //prevented editor crashes when hitting brushes without an actor component
				{
					UE_LOG(LogTemp, Warning, TEXT("Hit?: %s"), *hitActor->GetName());
					if (hitActor->GetClass()->IsChildOf(ASoldier::StaticClass())) //if Soldier apply damage
					{
						UGameplayStatics::ApplyDamage
						(
							hitActor,
							20.0f,
							this->GetInstigatorController(),
							this,
							UDamageType::StaticClass()
						);
					}
					else if (hitActor->ActorHasTag(FName("WALL"))) //if wall apply damage via radial method as otherwise destructible objects do not respond
					{
						UE_LOG(LogTemp, Warning, TEXT("Hit a wall?"));
						TArray <AActor*> NoActors;
						//Only Destroyed by radial damage?
						UGameplayStatics::ApplyRadialDamage
						(
							GetWorld(),
							20.0f,
							hitActor->GetActorLocation(),
							10.0f,
							UDamageType::StaticClass(),
							NoActors,
							this,
							this->GetInstigatorController(),
							true
						);
					}
					else if (hitActor->ActorHasTag(FName("ROCK"))) //If shooting boulder add slight amount of impulse
					{
						//Kill enemies by rolling the boulder into them hehe
						UPrimitiveComponent* RootComp = Cast<UPrimitiveComponent>(hitActor->GetRootComponent());
						float ImpulseForce = 50.0f;
						RootComp->AddImpulse(CameraRotation.Vector() * ImpulseForce * RootComp->GetMass());
						TArray <AActor*> NoActors;
						UGameplayStatics::ApplyRadialDamage
						(
							GetWorld(),
							20.0f,
							hitActor->GetActorLocation(),
							10.0f,
							UDamageType::StaticClass(),
							NoActors,
							this,
							this->GetInstigatorController(),
							true
						);
					}
				}
			}

		}
		wantsToFire = true;
	}
}

void ASoldier::MoveForwards(float AxisAmount)
{
	if (!wantsToFire && !isDead)
	{
		AddMovementInput(GetActorForwardVector() * AxisAmount);
	}
}

void ASoldier::Strafe(float AxisAmount)
{
	if (!wantsToFire && !isDead)
	{
		AddMovementInput(GetActorRightVector() * AxisAmount);
	}

}

void ASoldier::LookUp(float AxisAmount)
{
	if (!isDead)
		AddControllerPitchInput(AxisAmount);
}

void ASoldier::Turn(float AxisAmount)
{
	if (!isDead)
		AddControllerYawInput(AxisAmount);
}

void ASoldier::doCrouch() //Toggle crouch state
{
	if (!isDead)
	{
		if (!bIsCrouched)
			Crouch();
		else
			UnCrouch();
	}
}

