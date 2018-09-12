// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_Math.h"

// ParametricFunctionType
EMCsParametricFunctionType* EMCsParametricFunctionType::Instance;

EMCsParametricFunctionType& EMCsParametricFunctionType::Get()
{
	if (!Instance)
		Instance = new EMCsParametricFunctionType();
	return *Instance;
}

namespace ECsParametricFunctionType
{
	namespace Ref
	{
		CSCORE_API const Type Linear = EMCsParametricFunctionType::Get().Add(Type::Linear, TEXT("Linear"));
		CSCORE_API const Type Quadratic = EMCsParametricFunctionType::Get().Add(Type::Quadratic, TEXT("Quadratic"));
		CSCORE_API const Type Sine = EMCsParametricFunctionType::Get().Add(Type::Sine, TEXT("Sine"));
		CSCORE_API const Type ECsParametricFunctionType_MAX = EMCsParametricFunctionType::Get().Add(Type::ECsParametricFunctionType_MAX, TEXT("ECsParametricFunctionType_MAX"), TEXT("MAX"));
	}
}