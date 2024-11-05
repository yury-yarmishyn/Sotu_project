// stan


#include "UI/HUD/SotuHUD.h"
#include "UI/Widget/SotuUserWidget.h"
#include "UI/WidgetController/AttributeMenuWidgetController.h"
#include "UI/WidgetController/OverlayWidgetController.h"

UOverlayWidgetController* ASotuHUD::GetOverlayWidgetController(const FWidgetControllerParams& WCParams)
{
	OverlayWidgetController = GetWidgetController(OverlayWidgetController, OverlayWidgetControllerClass, WCParams);
	return OverlayWidgetController; 
}

UAttributeMenuWidgetController* ASotuHUD::GetAttributeMenuWidgetController(const FWidgetControllerParams& WCParams)
{
	AttributeMenuWidgetController = GetWidgetController(AttributeMenuWidgetController, AttributeMenuWidgetControllerClass, WCParams);
	return AttributeMenuWidgetController; 
}

void ASotuHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	checkf(OverlayWidgetClass, TEXT("Overlay Widget Class uninitialized, please fill out BP_SotuHUD"));
	checkf(OverlayWidgetControllerClass, TEXT("Overlay Widget Controller Class uninitialized, please fill out BP_SotuHUD"));
	
	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	OverlayWidget = Cast<USotuUserWidget>(Widget);
	
	const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
	UOverlayWidgetController* WidgetController = GetOverlayWidgetController(WidgetControllerParams);

	OverlayWidget->SetWidgetController(WidgetController);
	WidgetController->BroadcastInitialValues();
	Widget->AddToViewport();
}