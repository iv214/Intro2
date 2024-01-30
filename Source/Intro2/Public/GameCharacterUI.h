#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/ProgressBar.h"
#include "GameCharacterUI.generated.h"


class UProgressBar;

UCLASS(meta = (BlueprintSpawnableComponent))
class INTRO2_API UGameCharacterUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UGameCharacterUI(const FObjectInitializer&);
	
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* HPMeter;

	UFUNCTION()
	void SetHealthPercent(float Value);

protected:
	virtual bool Initialize() override;
	virtual void NativeConstruct() override;
	void NativeOnInitialized() override;
};
