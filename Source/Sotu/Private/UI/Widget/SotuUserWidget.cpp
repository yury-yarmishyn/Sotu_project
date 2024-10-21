// stan


#include "UI/Widget/SotuUserWidget.h"

void USotuUserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	WidgetControllerSet();
}
