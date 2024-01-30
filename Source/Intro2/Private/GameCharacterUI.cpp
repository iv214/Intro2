#include "GameCharacterUI.h"
UGameCharacterUI::UGameCharacterUI(const FObjectInitializer& ObjectInitializer) : UUserWidget(ObjectInitializer)
{
	HPMeter = CreateDefaultSubobject<UProgressBar>(TEXT("HPBar"));
	HPMeter->SetBorderPadding(FVector2D(80, 10));
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

void UGameCharacterUI::RenderHP(float Value) {
    HPMeter->SetPercent(Value/100.0);
}