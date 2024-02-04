// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "Abilities/GameplayAbility.h"
#include "GameplayAbilitySet.h"
#include "BaseAbilitySet.generated.h"

USTRUCT()
struct FGameplayAbilityInfo
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Category = "Abilities")
		TSubclassOf<UGameplayAbility> GameplayAbility;
	UPROPERTY(EditAnywhere, Category = "Abilities")
		uint32 InInputID;

};

UCLASS()
class INTRO2_API UBaseAbilitySet: public UDataAsset
{
	GENERATED_BODY()
	public:
		UPROPERTY(EditAnywhere, Category = "Abilities")
			TArray<FGameplayAbilityInfo> Abilities;
	
		UFUNCTION()
			TArray<FGameplayAbilitySpecHandle> GiveAbilities(UAbilitySystemComponent* AbilitySystemComponent) const;
};
