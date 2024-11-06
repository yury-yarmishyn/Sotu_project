// stan

#pragma once

#include "UI/WidgetController/AttributeMenuWidgetController.h"
#include "GameplayTagContainer.h"
#include "GameplayTagsManager.h"
#include "SotuGameplayTags.h"


void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
	USotuAttributeSet* AS = CastChecked<USotuAttributeSet>(AttributeSet);
	for (auto& Pair : AS->TagsToAttributes)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Pair.Value()).AddLambda(
		[this, Pair, AS](const FOnAttributeChangeData& Data)
		{
			FSotuAttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(Pair.Key);
			Info.AttributeValue = Pair.Value().GetNumericValue(AS);
			AttributeInfoDelegate.Broadcast(Info);
		}
	);
	}
}

void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	USotuAttributeSet* AS = CastChecked<USotuAttributeSet>(AttributeSet);

	check(AttributeInfo);
	
	for (auto& Pair : AS->TagsToAttributes)
	{
		FSotuAttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(Pair.Key);
		Info.AttributeValue = Pair.Value().GetNumericValue(AS);
		AttributeInfoDelegate.Broadcast(Info);
	}
}

TArray<FGameplayTag> UAttributeMenuWidgetController::GetAllChildrenTags(FGameplayTag ParentTag)
{
	FGameplayTagContainer ChildrenTags = UGameplayTagsManager::Get().RequestGameplayTagChildren(ParentTag);
	
	TArray<FGameplayTag> TagArray;
	ChildrenTags.GetGameplayTagArray(TagArray);
	
	return TagArray;
}
