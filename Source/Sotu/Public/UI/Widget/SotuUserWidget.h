// stan

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SotuUserWidget.generated.h"

/**
 * 
 */

UCLASS()
class SOTU_API USotuUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UObject* InWidgetController);
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UObject> WidgetController;
	
protected:
	UFUNCTION(BlueprintImplementableEvent)
	void WidgetControllerSet();
};
