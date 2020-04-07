#pragma once

#include "Components/CsWidgetComponent.h"
#include "CsHealthBarComponent.generated.h"

UCLASS(meta = (BlueprintSpawnableComponent))
class CSCOREDEPRECATED_API UCsHealthBarComponent : public UCsWidgetComponent
{
	GENERATED_UCLASS_BODY()

	void OnChange_Health(const uint8 &MappingId, const float &CurrentHealth, const float &CurrentMaxHealth);
	void OnLocalClientSeesMe(const uint64 &ObserverId, const uint64& ObserveeId, const bool& Value);
};