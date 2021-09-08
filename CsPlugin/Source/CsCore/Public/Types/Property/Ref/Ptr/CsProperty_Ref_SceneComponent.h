// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/Property/Ref/Ptr/CsProperty_Ref_Ptr.h"

#pragma once

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