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
// 	template<class UserObject,typename CallbackFunc>
// 	void BindNativeInputAction(const USotuInputConfig* InInputConfig,const FGameplayTag& InInputTag,ETriggerEvent TriggerEvent,UserObject* ContextObject,CallbackFunc Func);
// };
//
// template<class UserObject, typename CallbackFunc>
// void USotuInputComponent::BindNativeInputAction(const USotuInputConfig* InInputConfig, const FGameplayTag& InInputTag, ETriggerEvent TriggerEvent, UserObject* ContextObject, CallbackFunc Func)
// {
// 	checkf(InInputConfig,TEXT("Input config data asset is null,can not proceed with binding"));
//
// 	if (UInputAction* FoundAction = InInputConfig->FindNativeInputActionByTag(InInputTag))
// 	{
// 		BindAction(FoundAction, TriggerEvent, ContextObject, Func);
// 	}
public:
	template<class UserClass, typename PressedFuncType, typename ReleasedFuncType, typename HeldFuncType>
	void BindAbilityActions(const USotuInputConfig* InputConfig, UserClass* Object, PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc, HeldFuncType HeldFunc);
};

template <class UserClass, typename PressedFuncType, typename ReleasedFuncType, typename HeldFuncType>
void USotuInputComponent::BindAbilityActions(const USotuInputConfig* InputConfig, UserClass* Object, PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc, HeldFuncType HeldFunc)
{
	check(InputConfig);

	for (const FSotuInputAction& Action : InputConfig->AbilityInputActions)
	{
		if (Action.InputAction && Action.InputTag.IsValid())
		{
			if (PressedFunc)
			{
				BindAction(Action.InputAction, ETriggerEvent::Started, Object, PressedFunc, Action.InputTag);
			}

			if (ReleasedFunc)
			{
				BindAction(Action.InputAction, ETriggerEvent::Completed, Object, ReleasedFunc, Action.InputTag);
			}
			
			if (HeldFunc)
			{
				BindAction(Action.InputAction, ETriggerEvent::Triggered, Object, HeldFunc, Action.InputTag);
			}
		}
	}
}
