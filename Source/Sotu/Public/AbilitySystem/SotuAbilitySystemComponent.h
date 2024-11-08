// stan

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "SotuAbilitySystemComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FEffectAssetTags, const FGameplayTagContainer)

/**
 * 
 */
UCLASS()
class SOTU_API USotuAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	void AbilityActorInfoSet();
	
	FEffectAssetTags EffectAssetTags;

	void AddCharacterAbilities(TArray<TSubclassOf<UGameplayAbility>>& StartupAbilities);
	
protected:
	void EffectApplied(UAbilitySystemComponent* AbilitySystemComponent,
		const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle EffectHandle);
	
};
