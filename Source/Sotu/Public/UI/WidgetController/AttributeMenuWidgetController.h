// stan

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/SotuWidgetController.h"
#include "AttributeMenuWidgetController.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class SOTU_API UAttributeMenuWidgetController : public USotuWidgetController
{
	GENERATED_BODY()

public:
	virtual void BindCallbacksToDependencies() override;
	virtual void BroadcastInitialValues() override;
};
