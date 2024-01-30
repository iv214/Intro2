// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "NPC.h"
#include "GameAIController.generated.h"


UCLASS()
class INTRO2_API AGameAIController : public AAIController
{
	GENERATED_BODY()
public:
	explicit AGameAIController(FObjectInitializer const& ObjectInitializer);
protected:
	virtual void OnPossess(APawn* InPawn) override;
	
};
