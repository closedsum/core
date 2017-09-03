#pragma once

#include "Runtime/UMG/Public/Components/WidgetComponent.h"
#include "CsTypes.h"
#include "CsWidgetComponent.generated.h"

UCLASS(meta = (BlueprintSpawnableComponent))
class CSCORE_API UCsWidgetComponent : public UWidgetComponent
{
	GENERATED_UCLASS_BODY()

	UFUNCTION()
	class UCsUserWidget* GetWidget();

	UFUNCTION(BlueprintCallable, Category = "Widget")
	void SetInfo(const FCsWidgetActorInfo &Info);

	UFUNCTION(BlueprintCallable, Category = "Widget")
	void Show();
	UFUNCTION(BlueprintCallable, Category = "Widget")
	void Hide();
};