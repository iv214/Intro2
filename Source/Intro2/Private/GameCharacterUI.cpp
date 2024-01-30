#include "GameCharacterUI.h"
UGameCharacterUI::UGameCharacterUI(const FObjectInitializer& ObjectInitializer) : UUserWidget(ObjectInitializer)
{
	HPMeter = CreateDefaultSubobject<UProgressBar>(TEXT("HPBar"));
}
bool UGameCharacterUI::Initialize() {
	Super::Initialize();
	return true;
}
void UGameCharacterUI::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}
void UGameCharacterUI::NativeConstruct()
{
	Super::NativeConstruct();
}
void UGameCharacterUI::SetHealthPercent(float Value)
{
	HPMeter->SetPercent(Value);
}