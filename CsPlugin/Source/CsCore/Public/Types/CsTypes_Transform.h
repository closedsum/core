// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Types/Enum/CsEnumMap.h"
// Log
//#include "Utility/CsLog.h"

//#include "CsTypes_Interpolation.generated.h"

// Transform
#pragma region

/**
* Describes the members of FTransform.
*/
UENUM(BlueprintType)
enum class ECsTransform : uint8
{
	Translation			UMETA(DisplayName = "Translation"),
	Rotation			UMETA(DisplayName = "Rotation"),
	Scale				UMETA(DisplayName = "Scale"),
	ECsTransform_MAX	UMETA(Hidden),
};

struct CSCORE_API EMCsTransform : public TCsEnumMap<ECsTransform>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsTransform, ECsTransform)
};

namespace NCsTransform
{
	namespace Ref
	{
		typedef ECsTransform Type;

		extern CSCORE_API const Type Translation;
		extern CSCORE_API const Type Rotation;
		extern CSCORE_API const Type Scale;
		extern CSCORE_API const Type ECsTransform_MAX;
	}
}

#pragma endregion Transform

// TransformSpace
#pragma region

/**
* Describes how the member of FTransform is modified (Relative, World, ... etc)
*/
UENUM(BlueprintType)
enum class ECsTransformSpace : uint8
{
	Relative				UMETA(DisplayName = "Relative"),
	World					UMETA(DisplayName = "World"),
	ECsTransformSpace_MAX	UMETA(Hidden),
};

struct CSCORE_API EMCsTransformSpace : public TCsEnumMap<ECsTransformSpace>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsTransformSpace, ECsTransformSpace)
};

namespace NCsTransformSpace
{
	namespace Ref
	{
		typedef ECsTransformSpace Type;

		extern CSCORE_API const Type Relative;
		extern CSCORE_API const Type World;
		extern CSCORE_API const Type ECsTransformSpace_MAX;
	}
}

#pragma endregion TransformSpace