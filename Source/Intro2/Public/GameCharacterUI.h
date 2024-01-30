#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "GameCharacterUI.generated.h"


class UProgressBar;

UCLASS(meta = (BlueprintSpawnableComponent))
class INTRO2_API UGameCharacterUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UGameCharacterUI(const FObjectInitializer&);
	virtual bool Initialize() override;
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* HPMeter;

	UFUNCTION()
	void RenderHP(float Value);

protected:

	void NativeOnInitialized() override;
};
