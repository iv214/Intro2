#include "GEMM_Custom.h"

FGEMM_Custom::FGEMM_Custom() {
    MagnitudeCalculationType = EGameplayEffectMagnitudeCalculation::SetByCaller;
}
FGEMM_Custom::FGEMM_Custom(FName tagName) : FGEMM_Custom() {
    SetByCallerMagnitude.DataTag = FGameplayTag::RequestGameplayTag(tagName);
}