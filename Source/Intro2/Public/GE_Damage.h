// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "GameplayEffectTypes.h"
#include "BaseAttributeSet.h"
#include "GameplayEffectComponents/TargetTagsGameplayEffectComponent.h"
#include "GE_Damage.generated.h"

/**
 * 
 */
UCLASS()
class INTRO2_API UGE_Damage : public UGameplayEffect
{
	GENERATED_BODY()
public:
	UGE_Damage(const FObjectInitializer &ObjectInitializer);

	//UPROPERTY(BlueprintReadOnly, EditAnywhere, category = "Effects")
	//	FName EffectName;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, category = "Effects")
		UTargetTagsGameplayEffectComponent* TTGEC_Damage;
	
	virtual void PostInitProperties() override;
};
