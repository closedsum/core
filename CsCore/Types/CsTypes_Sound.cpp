// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_Sound.h"
#include "CsCore.h"

EMCsSoundType* EMCsSoundType::Instance;

EMCsSoundType& EMCsSoundType::Get()
{
	if (!Instance)
		Instance = new EMCsSoundType();
	return *Instance;
}

namespace ECsSoundType
{
	namespace Ref
	{
		extern CSCORE_API const Type s2D = EMCsSoundType::Get().Add(Type::s2D, TEXT("s2D"), TEXT("2D"));
		extern CSCORE_API const Type s3D = EMCsSoundType::Get().Add(Type::s3D, TEXT("s3D"), TEXT("3D"));
		extern CSCORE_API const Type ECsSoundType_MAX = EMCsSoundType::Get().Add(Type::ECsSoundType_MAX, TEXT("ECsSoundType_MAX"), TEXT("MAX"));
	}
}