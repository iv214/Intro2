// Fill out your copyright notice in the Description page of Project Settings.


#include "AI_BTTBB_FindTarget.h"
#include "NavigationSystem.h"
#include "Kismet/GameplayStatics.h"
#include "GameAIController.h"

UAI_BTTBB_FindTarget::UAI_BTTBB_FindTarget(FObjectInitializer const& ObjectInitializer)
{
    NodeName = "Find Player";
}
EBTNodeResult::Type UAI_BTTBB_FindTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    if (auto* const Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
    {
        auto const PlayerLocation = Player->GetActorLocation();
        if (SearchRandom)
        {
            if (auto* const NavigationSystem = UNavigationSystemV1::GetCurrent(GetWorld()))
            {
                FNavLocation Location;
                if (NavigationSystem->GetRandomPointInNavigableRadius(PlayerLocation, SearchRadius, Location))
                {
                    OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), Location.Location);
                } 
            }
        }
        else
        {
            OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), PlayerLocation);
        }
        FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
        return EBTNodeResult::Succeeded;
    }
    return EBTNodeResult::Failed;
}

