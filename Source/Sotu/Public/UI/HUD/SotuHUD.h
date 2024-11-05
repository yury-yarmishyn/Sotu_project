// stan

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SotuHUD.generated.h"


class UAttributeMenuWidgetController;
class UAttributeSet;
class UAbilitySystemComponent;
class UOverlayWidgetController;
class USotuUserWidget;
struct FWidgetControllerParams;
/**
 * 
 */
UCLASS()
class SOTU_API ASotuHUD : public AHUD
{
	GENERATED_BODY()
public:

	UOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& WCParams);
	UAttributeMenuWidgetController* GetAttributeMenuWidgetController(const FWidgetControllerParams& WCParams);

	void InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS);
	
	template <class T>
	TObjectPtr<T> GetWidgetController(TObjectPtr<T> Controller, TSubclassOf<T> ControllerClass,
	                                  const FWidgetControllerParams& WCParams);

protected:


private:
	UPROPERTY()
	TObjectPtr<USotuUserWidget>  OverlayWidget;	

	UPROPERTY(EditAnywhere)
	TSubclassOf<USotuUserWidget> OverlayWidgetClass;

	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;

	UPROPERTY()
	TObjectPtr<UAttributeMenuWidgetController> AttributeMenuWidgetController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UAttributeMenuWidgetController> AttributeMenuWidgetControllerClass;
};

template <typename T>
TObjectPtr<T> ASotuHUD::GetWidgetController(TObjectPtr<T> Controller, TSubclassOf<T> ControllerClass, const FWidgetControllerParams& WCParams)
{
	if (!Controller) 
	{
		Controller = NewObject<T>(this, ControllerClass); 
		Controller->SetWidgetControllerParams(WCParams);
		Controller->BindCallbacksToDependencies();
	}
	return Controller;
}