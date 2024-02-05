// Fill out your copyright notice in the Description page of Project Settings.


#include "GameAIController.h"
#include "../Intro2Character.h"


AGameAIController::AGameAIController(FObjectInitializer const& ObjectInitializer)
{
    SetupPerceptionSystem();
}
void AGameAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);
    if (ANPC* const npc = Cast<ANPC>(InPawn))
    {
        if (UBehaviorTree* const tree = npc->GetBehaviorTree())
        {
            UBlackboardComponent* b;
            UseBlackboard(tree->BlackboardAsset, b);
            Blackboard = b;
            RunBehaviorTree(tree);
        }
    }
}
void AGameAIController::EQSf()
{
    FEnvQueryRequest AIC_QueryRequest = FEnvQueryRequest(AIC_EQS, GetPawn());
	AIC_QueryRequest.Execute(EEnvQueryRunMode::SingleResult, this, &AGameAIController::MoveToQueryResult);
}
void AGameAIController::MoveToQueryResult(TSharedPtr<FEnvQueryResult> result)
{
	if (result->IsSuccessful()) {
		MoveToLocation(result->GetItemAsLocation(0));
	}
}

void AGameAIController::SetupPerceptionSystem() {
    SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Configuration"));
    if (SightConfig)
    {
        SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component")));
        SightConfig->SightRadius = 500.0f;
        SightConfig->LoseSightRadius = SightConfig->SightRadius + 100.0f;
        SightConfig->PeripheralVisionAngleDegrees = 90.f;
        SightConfig->SetMaxAge(5.f);
        SightConfig->AutoSuccessRangeFromLastSeenLocation = 75.f;
        SightConfig->DetectionByAffiliation.bDetectEnemies = true;
        SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
        SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

        GetPerceptionComponent()->SetDominantSense(*SightConfig->GetSenseImplementation());
        GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(
            this, &AGameAIController::OnTargetSeen
        );
        GetPerceptionComponent()->ConfigureSense(*SightConfig);
    }
}

void AGameAIController::OnTargetSeen(AActor* Actor, FAIStimulus const Stimulus)
{
    if (auto const character = Cast<AIntro2Character>(Actor))
    {
        GetBlackboardComponent()->SetValueAsBool("CanSeePlayer", Stimulus.WasSuccessfullySensed());
    }
}