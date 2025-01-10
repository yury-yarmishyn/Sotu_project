// stan

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "Camera/CameraComponent.h"
#include "Character/SotuCharacterBase.h"
#include "GameFramework/SpringArmComponent.h"
#include "Input/SotuInputConfig.h"
#include "SotuCharacter.generated.h"

/**
 * 
 */
UCLASS()
class SOTU_API ASotuCharacter : public ASotuCharacterBase
{
	GENERATED_BODY()

public:
	ASotuCharacter();
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

	/** Combat Interface */
	virtual int32 GetPlayerLevel() override;
	/** end Combat Interface */
	
private:
	virtual void InitAbilityActorInfo() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* PlayerCamera;
};