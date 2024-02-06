// Fill out your copyright notice in the Description page of Project Settings.


#include "GE_Healing.h"
#include "GEMM_Custom.h"


UGE_Healing::UGE_Healing(const FObjectInitializer &ObjectInitializer)
{
    TTGEC_Healing = CreateDefaultSubobject<UTargetTagsGameplayEffectComponent>("TTGEC_Healing");
}
void UGE_Healing::PostInitProperties()
{
    Super::PostInitProperties();
    
    FInheritedTagContainer TC_Healing;
    TC_Healing.AddTag(FGameplayTag::RequestGameplayTag(FName("Effect.Positive.Healing")));
    TTGEC_Healing->SetAndApplyTargetTagChanges(TC_Healing);
    DurationPolicy = EGameplayEffectDurationType::Instant;
    FGameplayModifierInfo HealingModifier;
    HealingModifier.Attribute = UBaseAttributeSet::GetHealthAttribute();
    HealingModifier.ModifierOp = EGameplayModOp::Additive;
    FGEMM_Custom FGEMM_Healing(FName("SetByCaller.HealingMagnitude"));
    HealingModifier.ModifierMagnitude = FGEMM_Healing;
    Modifiers.Empty();
    Modifiers.Add(HealingModifier);
}
