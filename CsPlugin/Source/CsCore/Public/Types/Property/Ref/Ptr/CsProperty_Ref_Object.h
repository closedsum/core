// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/Property/Ref/Ptr/CsProperty_Ref_Ptr.h"

#pragma once

class UObject;

struct FCsProperty_Ref_Object : public TCsProperty_Ref_Ptr<UObject>
{
private:
	typedef TCsProperty_Ref_Ptr<UObject> Super;

public:

	FCsProperty_Ref_Object() : Super() {}
	~FCsProperty_Ref_Object() {}
};

typedef FCsProperty_Ref_Object TCsObject_Ref;