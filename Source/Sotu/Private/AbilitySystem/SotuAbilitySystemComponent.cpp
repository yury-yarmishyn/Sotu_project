// stan

#include "AbilitySystem/SotuAbilitySystemComponent.h"

#include "SotuGameplayTags.h"
#include "AbilitySystem/Abilities/SotuGameplayAbility.h"

void USotuAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &USotuAbilitySystemComponent::EffectApplied);
}

void USotuAbilitySystemComponent::AddCharacterAbilities(TArray<TSubclassOf<UGameplayAbility>>& StartupAbilities)
{
	for (const TSubclassOf<UGameplayAbility> AbilityClass : StartupAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, 1);

		if (const USotuGameplayAbility* SotuAbility = Cast<USotuGameplayAbility>(AbilitySpec.Ability))
		{
			AbilitySpec.DynamicAbilityTags.AddTag(SotuAbility->StartupInputTag);
			GiveAbility(AbilitySpec);
		}
	}
}

void USotuAbilitySystemComponent::AbilityInputTagHeld(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid()) return;

	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag))
		{
			AbilitySpecInputPressed(AbilitySpec);
			if (!AbilitySpec.IsActive())
			{
				TryActivateAbility(AbilitySpec.Handle);
			}
		}
	}
}

void USotuAbilitySystemComponent::AbilityInputTagReleased(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid()) return;

	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag))
		{
			AbilitySpecInputReleased(AbilitySpec);
		}
	}
}

void USotuAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* AbilitySystemComponent,
                                                const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle EffectHandle)
{
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);
	
	EffectAssetTags.Broadcast(TagContainer);
}
