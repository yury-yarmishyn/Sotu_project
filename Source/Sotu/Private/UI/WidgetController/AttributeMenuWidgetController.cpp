// stan

#pragma once

#include "UI/WidgetController/AttributeMenuWidgetController.h"
#include "GameplayTagContainer.h"
#include "GameplayTagsManager.h"
#include "SotuGameplayTags.h"

void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
	
}

void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	USotuAttributeSet* AS = CastChecked<USotuAttributeSet>(AttributeSet);

	check(AttributeInfo);
	
	FSotuAttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(FSotuGameplayTags::Get().Attributes_Primary_Strength);
	Info.AttributeValue = AS->GetStrength();
	AttributeInfoDelegate.Broadcast(Info);
}
