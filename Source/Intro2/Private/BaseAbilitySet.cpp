// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAbilitySet.h"

TArray<FGameplayAbilitySpecHandle> UBaseAbilitySet::GiveAbilities(UAbilitySystemComponent* AbilitySystemComponent) const {
    TArray<FGameplayAbilitySpecHandle> abilityHandleArray;
    abilityHandleArray.Reserve(Abilities.Num());
    for (const auto ability: Abilities)
    {
        abilityHandleArray.AddUnique(
            AbilitySystemComponent->GiveAbility(
                FGameplayAbilitySpec(
                    ability.GameplayAbility, 0, ability.InInputID
                )
            )
        );
    }
    return abilityHandleArray;
}