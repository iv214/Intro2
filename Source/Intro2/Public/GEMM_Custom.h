// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "GameplayEffectTypes.h"
#include "GEMM_Custom.generated.h"

/**
 * 
 */
USTRUCT()
struct INTRO2_API FGEMM_Custom : public FGameplayEffectModifierMagnitude
{
	GENERATED_USTRUCT_BODY()
public:
    FGEMM_Custom();
    FGEMM_Custom(FName tagName);
};
