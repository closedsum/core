// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_Interpolation.h"

// BlendDirection
EMCsBlendDirection* EMCsBlendDirection::Instance;

EMCsBlendDirection& EMCsBlendDirection::Get()
{
	if (!Instance)
		Instance = new EMCsBlendDirection();
	return *Instance;
}

namespace NCsBlendDirection
{
	namespace Ref
	{
		CSCORE_API const Type In = EMCsBlendDirection::Get().Add(Type::In, TEXT("In"));
		CSCORE_API const Type Out = EMCsBlendDirection::Get().Add(Type::Out, TEXT("Out"));
		CSCORE_API const Type ECsBlendDirection_MAX = EMCsBlendDirection::Get().Add(Type::ECsBlendDirection_MAX, TEXT("ECsBlendDirection_MAX"), TEXT("MAX"));
	}
}