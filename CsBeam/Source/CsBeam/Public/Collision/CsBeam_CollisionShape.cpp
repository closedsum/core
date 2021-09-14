// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Collision/CsBeam_CollisionShape.h"

// Library
#include "Managers/Trace/CsLibrary_Manager_Trace.h"
#include "Library/CsLibrary_Valid.h"
// Trace
#include "Managers/Trace/CsTraceRequest.h"

// BeamCollisionShapeLength
#pragma region

namespace NCsBeamCollisionShapeLength
{
	namespace Ref
	{
		typedef EMCsBeamCollisionShapeLength EnumMapType;

		CSCORE_API CS_ADD_TO_ENUM_MAP(Fixed);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Scaled);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsBeamCollisionShapeLength_MAX, "MAX");
	}

	CSCORE_API const uint8 MAX = (uint8)Type::ECsBeamCollisionShapeLength_MAX;
}

namespace NCsBeam
{
	namespace NCollision
	{
		namespace NShape
		{
			namespace NLength
			{
				namespace Ref
				{
					typedef EMLength EnumMapType;

					CSCORE_API CS_ADD_TO_ENUM_MAP(Fixed);
					CSCORE_API CS_ADD_TO_ENUM_MAP(Count);
					CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ELength_MAX, "MAX");
				}
			}
		}
	}
}

#pragma endregion BeamCollisionShapeLength

// BeamCollisionShapeType
#pragma region

namespace NCsBeamCollisionShapeType
{
	namespace Ref
	{
		typedef EMCsBeamCollisionShapeType EnumMapType;

		CSCORE_API CS_ADD_TO_ENUM_MAP(Line);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Box);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Capsule);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsBeamCollisionShapeType_MAX, "MAX");
	}

	CSCORE_API const uint8 MAX = (uint8)Type::ECsBeamCollisionShapeType_MAX;
}

#pragma endregion BeamCollisionShapeType

// FCsBeamCollisionShape
#pragma region

#define LineType NCsBeam::NCollision::NShape::FLine

void FCsBeamCollisionShape::CopyToShape(LineType* Shape)
{
	Shape->SetLengthType((NCsBeam::NCollision::NShape::ELength*)&LengthType);
	Shape->SetLength(&Length);
}

void FCsBeamCollisionShape::CopyToShapeAsValue(LineType* Shape) const
{
	Shape->SetLengthType((NCsBeam::NCollision::NShape::ELength)LengthType);
	Shape->SetLength(Length);
}

#undef LineType

#define ShapeType NCsBeam::NCollision::NShape::FShape

ShapeType* FCsBeamCollisionShape::ConstructShape()
{
	if (Type == ECsBeamCollisionShapeType::Line)
	{
		typedef NCsBeam::NCollision::NShape::FLine LineType;

		LineType* Shape = new LineType();
		CopyToShape(Shape);
		return Shape;
	}
	return nullptr;
}

ShapeType* FCsBeamCollisionShape::ConstructShapeAsValue()
{
	if (Type == ECsBeamCollisionShapeType::Line)
	{
		typedef NCsBeam::NCollision::NShape::FLine LineType;

		LineType* Shape = new LineType();
		CopyToShapeAsValue(Shape);
		return Shape;
	}
	return nullptr;
}

#undef ShapeType

bool IsValidChecked(const FString& Context) const
{
	check(EMCsBeamCollisionShapeLength::Get().IsValidEnumChecked(Context, LengthType));

	check(EMCsBeamCollisionShapeType::Get().IsValidEnumChecked(Context, Type));

	// Line
	if (Type == ECsBeamCollisionShapeType::Line)
	{
		CS_IS_FLOAT_GREATER_THAN_CHECKED(Length, 0.0f);
	}
	// Box
	else
	if (Type == ECsBeamCollisionShapeType::Box)
	{
		checkf(HalfExtents != FVector::ZeroVector, TEXT("%s: HalfExtents == (0.0f, 0.0f, 0.0f) is NOT Valid."));
	}
	// Capsule
	else
	if (Type == ECsBeamCollisionShapeType::Capsule)
	{
		CS_IS_FLOAT_GREATER_THAN_CHECKED(Radius, 0.0f);

		CS_IS_FLOAT_GREATER_THAN_CHECKED(HalfHeight, 0.0f);
	}
	return true;
}

bool IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsBeam::FLog::Warning*/) const
{
	CS_IS_ENUM_VALID(EMCsBeamCollisionShapeLength, ECsBeamCollisionShapeLength, LengthType)

	CS_IS_ENUM_VALID(EMCsBeamCollisionShapeType, ECsBeamCollisionShapeType, Type)

	// Line
	if (Type == ECsBeamCollisionShapeType::Line)
	{
		CS_IS_FLOAT_GREATER_THAN(Length, 0.0f);
	}
	// Box
	else
	if (Type == ECsBeamCollisionShapeType::Box)
	{
		if (HalfExtents == FVector::ZeroVector)
		{
			CS_CONDITIONAL_LOG(TEXT("%s: HalfExtents == (0.0f, 0.0f, 0.0f) is NOT Valid.")));
			return false;
		}
	}
	// Capsule
	else
	if (Type == ECsBeamCollisionShapeType::Capsule)
	{
		CS_IS_FLOAT_GREATER_THAN(Radius, 0.0f);

		CS_IS_FLOAT_GREATER_THAN(HalfHeight, 0.0f);
	}
	return true;
}

namespace NCsBeam
{
	namespace NCollision
	{
		namespace NShape
		{
			bool FLine::IsValidChecked(const FString& Context) const
			{
				check(EMLength::Get().IsValidEnumChecked(Context, LengthType));

				CS_IS_FLOAT_GREATER_THAN_CHECKED(GetLength(), 0.0f);
			}

			bool FLine::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsBeam::FLog::Warning*/) const
			{
				CS_IS_ENUM_VALID(EMLength, ELength, LengthType)

				CS_IS_FLOAT_GREATER_THAN(GetLength(), 0.0f);
			}

			ResponseType* FLine::TraceChecked(const FString& Context, const UObject* WorldContext, RequestType* Request) const
			{
				if (LengthType == ELength::Fixed)
				{
					const FVector Dir = (RequestType->End - RequestType->Start).GetSafeNormal();
					Request->End	  = RequestType->Start + Length * Dir;					
				}

				typedef NCsTrace::NManager::FLibrary TraceManagerLibrary;

				return TraceManagerLibrary::TraceChecked(Context, WorldContext, Request);
			}
		}
	}
}

#pragma endregion FCsBeamCollisionShape