// Fill out your copyright notice in the Description page of Project Settings.


#include "AI_BTTBB_Patrol.h"
#include "NavigationSystem.h"
#include "GameAIController.h"

UAI_BTTBB_Patrol::UAI_BTTBB_Patrol(FObjectInitializer const& ObjectInitializer)
{
    NodeName = "Random Location in NavMesh";

}
EBTNodeResult::Type UAI_BTTBB_Patrol::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    if (auto* const Controller = Cast<AGameAIController>(OwnerComp.GetAIOwner()))
    {
        if (auto* const npc = Controller->GetPawn())
        {
            FVector OriginVector = npc->GetActorLocation();
            if (auto* const NavigationSystem = UNavigationSystemV1::GetCurrent(GetWorld()))
            {
                FNavLocation Location;
                if (NavigationSystem->GetRandomPointInNavigableRadius(OriginVector, SearchRadius, Location))
                {
                    OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), Location.Location);
                }
                FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
                return EBTNodeResult::Succeeded;
            }

        }
    }
    return EBTNodeResult::Failed;
}

