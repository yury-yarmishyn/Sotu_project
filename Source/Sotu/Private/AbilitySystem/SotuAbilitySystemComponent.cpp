// stan

#include "AbilitySystem/SotuAbilitySystemComponent.h"

#include "SotuGameplayTags.h"

void USotuAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &USotuAbilitySystemComponent::EffectApplied);

	const FSotuGameplayTags& GameplayTags = FSotuGameplayTags::Get();
}

void USotuAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* AbilitySystemComponent,
	const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle EffectHandle)
{
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);
	
	EffectAssetTags.Broadcast(TagContainer);
}
