// stan

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Input/SotuInputConfig.h"
#include "SotuPlayerController.generated.h"

class USplineComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class IEnemyInterface;
class USotuAbilitySystemComponent;

/**
 * 
 */
UCLASS()
class SOTU_API ASotuPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	//ASotuPlayerController();
	//virtual void PlayerTick(float DeltaTime) override;
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
private:
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputMappingContext> SotuContext;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> MoveAction;
	
	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<USotuInputConfig> InputConfig;

	void Move(const FInputActionValue& InputActionValue);

	void CursorTrace();

	TScriptInterface<IEnemyInterface> LastActor;
	TScriptInterface<IEnemyInterface> ThisActor;
	FHitResult CursorHit;

	UPROPERTY()
	TObjectPtr<USotuAbilitySystemComponent> SotuAbilitySystemComponent;
	
	USotuAbilitySystemComponent* GetAbilitySystemComponent();
};