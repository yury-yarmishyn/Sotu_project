// stan

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "SotuGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class SOTU_API USotuGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category="Input")
	FGameplayTag StartupInputTag;
};
