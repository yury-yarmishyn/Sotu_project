// stan


#include "UI/WidgetController/SotuWidgetController.h"

void USotuWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& WidgetControllerParams)
{
	PlayerController = WidgetControllerParams.PlayerController;
	PlayerState = WidgetControllerParams.PlayerState;
	AttributeSet = WidgetControllerParams.AttributeSet;
	AbilitySystemComponent = WidgetControllerParams.AbilitySystemComponent;
}

void USotuWidgetController::BroadcastInitialValues()
{
	
}

void USotuWidgetController::BindCallbacksToDependencies()
{
	
}
