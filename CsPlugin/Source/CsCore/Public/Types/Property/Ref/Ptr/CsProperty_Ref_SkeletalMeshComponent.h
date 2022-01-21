// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/Property/Ref/Ptr/CsProperty_Ref_Ptr.h"

#pragma once

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