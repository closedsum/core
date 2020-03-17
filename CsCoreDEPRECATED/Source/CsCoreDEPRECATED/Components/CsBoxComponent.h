#pragma once

#include "Components/BoxComponent.h"
#include "CsBoxComponent.generated.h"

UCLASS(ClassGroup = "Collision", hidecategories = (Object, LOD, Lighting, TextureStreaming), editinlinenew, meta = (DisplayName = "Box Collision", BlueprintSpawnableComponent))
class CSCOREDEPRECATED_API UCsBoxComponent : public UBoxComponent
{
	GENERATED_UCLASS_BODY()
};