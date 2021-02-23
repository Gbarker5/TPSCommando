// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindRandomLocation.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTTask_FindRandomLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	//Prevent crash if Enemy referenced is mssing
	if (OwnerComp.GetAIOwner() == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	//Get Enemy associated with script
	AActor* AIActor = OwnerComp.GetAIOwner()->GetPawn();

	
	FNavLocation RandomLocation;

	//using navigation system, get point currently accessible to ai on NavMesh within specified radius
	UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(this);
	NavSys->GetRandomReachablePointInRadius(AIActor->GetActorLocation(), RANDOM_RADIUS, RandomLocation);

	//When not trying to kill the player, patrol at random locations
	OwnerComp.GetBlackboardComponent()->SetValueAsVector(TEXT("RandomPosition"),RandomLocation);

	return EBTNodeResult::Succeeded;
}
