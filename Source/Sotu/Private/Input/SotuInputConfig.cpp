// stan


#include "Input/SotuInputConfig.h"

UInputAction* USotuInputConfig::FindNativeInputActionByTag(const FGameplayTag& InInputTag) const
{
	for (const FSotuInputAction& InputActionConfig : AbilityInputActions)
	{
		if (InputActionConfig.InputTag == InInputTag && InputActionConfig.InputAction)
		{
			return InputActionConfig.InputAction;
		}
	}

	return nullptr;
}
