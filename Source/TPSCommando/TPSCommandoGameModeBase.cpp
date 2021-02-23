

#include "TPSCommandoGameModeBase.h"
#include "SoldierPlayerController.h"
#include "Kismet/GameplayStatics.h"

ATPSCommandoGameModeBase::ATPSCommandoGameModeBase()
{
	PlayerControllerClass = ASoldierPlayerController::StaticClass();
}

void ATPSCommandoGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);	
}

void ATPSCommandoGameModeBase::SubtractEnemy() //subtract enemy from enemyCount
{
	enemyCount -= 1;
}

void ATPSCommandoGameModeBase::TimerOver() //If time runs out (5 minutes) player auto-lose, transition to lose Scene
{
	UE_LOG(LogTemp, Warning, TEXT("Lose?"));
	UGameplayStatics::OpenLevel(GetWorld(), "Lose");
}

void ATPSCommandoGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimer(EndGameTimer, this, &ATPSCommandoGameModeBase::TimerOver, GameLength, false);
	
}
