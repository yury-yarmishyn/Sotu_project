// stan

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/SotuGameplayAbility.h"
#include "Actor/SotuProjectile.h"
#include "SotuProjectileSpell.generated.h"

/**
 * 
 */
UCLASS()
class SOTU_API USotuProjectileSpell : public USotuGameplayAbility
{
	GENERATED_BODY()

protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<ASotuProjectile> ProjectileClass;
};
