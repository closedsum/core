// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Types/Property/Ref/Ptr/CsProperty_Ref_Ptr.h"

class USkeletalMeshComponent;

struct FCsProperty_Ref_SkeletalMeshComponent : public TCsProperty_Ref_Ptr<USkeletalMeshComponent>
{
private:
	typedef TCsProperty_Ref_Ptr<USkeletalMeshComponent> Super;

public:

	FCsProperty_Ref_SkeletalMeshComponent() : Super() {}
	~FCsProperty_Ref_SkeletalMeshComponent() {}
};

typedef FCsProperty_Ref_SkeletalMeshComponent TCsSkeletalMeshComponent_Ref;