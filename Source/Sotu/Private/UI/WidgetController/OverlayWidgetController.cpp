// stan

#include "UI/WidgetController/OverlayWidgetController.h"
#include "AbilitySystem/SotuAbilitySystemComponent.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	const USotuAttributeSet* SotuAttributeSet = CastChecked<USotuAttributeSet>(AttributeSet);

	OnParanoiaChanged.Broadcast(SotuAttributeSet->GetParanoia());
	OnMaxParanoiaChanged.Broadcast(SotuAttributeSet->GetMaxParanoia());
	OnLifeChanged.Broadcast(SotuAttributeSet->GetLife());
	OnMaxLifeChanged.Broadcast(SotuAttributeSet->GetMaxLife());
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	const USotuAttributeSet* SotuAttributeSet = CastChecked<USotuAttributeSet>(AttributeSet);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		SotuAttributeSet->GetParanoiaAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnParanoiaChanged.Broadcast(Data.NewValue);
			}
		);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		SotuAttributeSet->GetMaxParanoiaAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnMaxParanoiaChanged.Broadcast(Data.NewValue);
			}
		);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		SotuAttributeSet->GetLifeAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnLifeChanged.Broadcast(Data.NewValue);
			}
		);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		SotuAttributeSet->GetMaxLifeAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnMaxLifeChanged.Broadcast(Data.NewValue);
			}
		);
	
	Cast<USotuAbilitySystemComponent>(AbilitySystemComponent)->EffectAssetTags.AddLambda(
		[this](const FGameplayTagContainer& AssetTags)
		{
			for (const FGameplayTag& Tag: AssetTags)
			{
				FGameplayTag MessageTag = FGameplayTag::RequestGameplayTag(FName("Message"));
				if (Tag.MatchesTag(MessageTag))
				{
					const FUIWidgetRow* Row =  GetDataTableRowByTag<FUIWidgetRow>(MessageWidgetDataTable, Tag);
					MessageWidgetRowDelegate.Broadcast(*Row);
				}
			}
		}
	);
}
