// stan

#pragma once

#include "UI/WidgetController/AttributeMenuWidgetController.h"
#include "GameplayTagContainer.h"
#include "GameplayTagsManager.h"
#include "SotuGameplayTags.h"


void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
	USotuAttributeSet* AS = CastChecked<USotuAttributeSet>(AttributeSet);
	
	check(AttributeInfo);
	
	for (auto& Pair : AS->TagsToAttributes)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Pair.Value()).AddLambda(
		[this, Pair](const FOnAttributeChangeData& Data)
		{
			BroadcastAttributeInfo(Pair.Key, Pair.Value());
		}
	);
	}
}

void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	USotuAttributeSet* AS = CastChecked<USotuAttributeSet>(AttributeSet);

	check(AttributeInfo);
	
	for (auto& Pair: AS->TagsToAttributes)
	{
		BroadcastAttributeInfo(Pair.Key, Pair.Value());
	}
}

TArray<FGameplayTag> UAttributeMenuWidgetController::GetAllChildrenTags(FGameplayTag ParentTag)
{
	FGameplayTagContainer ChildrenTags = UGameplayTagsManager::Get().RequestGameplayTagChildren(ParentTag);
	
	TArray<FGameplayTag> TagArray;
	ChildrenTags.GetGameplayTagArray(TagArray);
	
	return TagArray;
}

void UAttributeMenuWidgetController::BroadcastAttributeInfo(const FGameplayTag& AttributeTag,
	const FGameplayAttribute& Attribute) const
{
	FSotuAttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(AttributeTag);
	Info.AttributeValue = Attribute.GetNumericValue(AttributeSet);
	AttributeInfoDelegate.Broadcast(Info);
}
