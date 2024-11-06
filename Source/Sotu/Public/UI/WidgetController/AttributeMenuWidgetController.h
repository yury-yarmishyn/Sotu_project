// stan

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagsManager.h"
#include "AbilitySystem/Data/AttributeInfo.h"
#include "UI/WidgetController/SotuWidgetController.h"
#include "AttributeMenuWidgetController.generated.h"

struct FSotuAttributeInfo;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAttributeInfoSignature, const FSotuAttributeInfo&, Info);

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
	
	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FAttributeInfoSignature AttributeInfoDelegate;
	
	UFUNCTION(BlueprintPure, Category = "Gameplay Tags")
	static TArray<FGameplayTag> GetAllChildrenTags(FGameplayTag ParentTag);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UAttributeInfo> AttributeInfo;

private:
	void BroadcastAttributeInfo(const FGameplayTag& AttributeTag, const FGameplayAttribute& Attribute) const;
};



