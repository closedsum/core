// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/Property/Ref/Ptr/CsProperty_Ref_Ptr.h"

#pragma once

class USceneComponent;

struct CSCORE_API FCsProperty_Ref_SceneComponent : public TCsProperty_Ref_Ptr<USceneComponent>
{
private:
	typedef TCsProperty_Ref_Ptr<USceneComponent> Super;

public:

	FCsProperty_Ref_SceneComponent() : Super() {}
	~FCsProperty_Ref_SceneComponent() {}
};

typedef FCsProperty_Ref_SceneComponent TCsSceneComponent_Ref;