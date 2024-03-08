// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Types/Property/Ref/Ptr/CsProperty_Ref_Ptr.h"

class USceneComponent;

struct FCsProperty_Ref_SceneComponent : public TCsProperty_Ref_Ptr<USceneComponent>
{
private:
	typedef TCsProperty_Ref_Ptr<USceneComponent> Super;

public:

	FCsProperty_Ref_SceneComponent() : Super() {}
	~FCsProperty_Ref_SceneComponent() {}
};

typedef FCsProperty_Ref_SceneComponent TCsSceneComponent_Ref;