// stan

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "SotuInputConfig.h"
#include "SotuInputComponent.generated.h"

/**
 * 
 */
UCLASS()
class SOTU_API USotuInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()
	
public:
	template<class UserObject,typename CallbackFunc>
	void BindNativeInputAction(const USotuInputConfig* InInputConfig,const FGameplayTag& InInputTag,ETriggerEvent TriggerEvent,UserObject* ContextObject,CallbackFunc Func);
};

template<class UserObject, typename CallbackFunc>
void USotuInputComponent::BindNativeInputAction(const USotuInputConfig* InInputConfig, const FGameplayTag& InInputTag, ETriggerEvent TriggerEvent, UserObject* ContextObject, CallbackFunc Func)
{
	checkf(InInputConfig,TEXT("Input config data asset is null,can not proceed with binding"));

	if (UInputAction* FoundAction = InInputConfig->FindNativeInputActionByTag(InInputTag))
	{
		BindAction(FoundAction, TriggerEvent, ContextObject, Func);
	}
}
