// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "Collision/CsBeam_CollisionShape.h"

// Library
#include "Managers/Trace/CsLibrary_Manager_Trace.h"
#include "Library/CsLibrary_Valid.h"
// Trace
#include "Managers/Trace/CsTraceRequest.h"

// BeamCollisionShapeLength
#pragma region

namespace NCsBeamCollisionShapeScale
{
	namespace Ref
	{
		typedef EMCsBeamCollisionShapeScale EnumMapType;

		CSBEAM_API CS_ADD_TO_ENUM_MAP(Default);
		CSBEAM_API CS_ADD_TO_ENUM_MAP(Owner);
		CSBEAM_API CS_ADD_TO_ENUM_MAP_CUSTOM(OwnerAsScalar, "Owner as Scalar");
		CSBEAM_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsBeamCollisionShapeScale_MAX, "MAX");
	}

	CSBEAM_API const uint8 MAX = (uint8)Type::ECsBeamCollisionShapeScale_MAX;
}

namespace NCsBeam
{
	namespace NCollision
	{
		namespace NShape
		{
			namespace NScale
			{
				namespace Ref
				{
					typedef EMScale EnumMapType;

					CSBEAM_API CS_ADD_TO_ENUM_MAP(Default);
					CSBEAM_API CS_ADD_TO_ENUM_MAP(Owner);
					CSBEAM_API CS_ADD_TO_ENUM_MAP(OwnerAsScalar);
					CSBEAM_API CS_ADD_TO_ENUM_MAP_CUSTOM(EScale_MAX, "MAX");
				}
			}
		}
	}
}

#pragma endregion BeamCollisionShapeScale

// BeamCollisionShapeType
#pragma region

namespace NCsBeamCollisionShapeType
{
	namespace Ref
	{
		typedef EMCsBeamCollisionShapeType EnumMapType;

		CSBEAM_API CS_ADD_TO_ENUM_MAP(Line);
		CSBEAM_API CS_ADD_TO_ENUM_MAP(Box);
		CSBEAM_API CS_ADD_TO_ENUM_MAP(Capsule);
		CSBEAM_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsBeamCollisionShapeType_MAX, "MAX");
	}

	CSBEAM_API const uint8 MAX = (uint8)Type::ECsBeamCollisionShapeType_MAX;
}

#pragma endregion BeamCollisionShapeType

// FCsBeamCollisionShape
#pragma region

#define LineType NCsBeam::NCollision::NShape::FLine

void FCsBeamCollisionShape::CopyToShape(LineType* Shape)
{
	Shape->SetScaleType((NCsBeam::NCollision::NShape::EScale*)&ScaleType);
	Shape->SetLength(&Length);
}

void FCsBeamCollisionShape::CopyToShapeAsValue(LineType* Shape) const
{
	Shape->SetScaleType((NCsBeam::NCollision::NShape::EScale)ScaleType);
	Shape->SetLength(Length);
}

#undef LineType

#define BoxType NCsBeam::NCollision::NShape::FBox

void FCsBeamCollisionShape::CopyToShape(BoxType* Shape)
{
	Shape->SetScaleType((NCsBeam::NCollision::NShape::EScale*)&ScaleType);
	Shape->SetHalfExtents(&HalfExtents);
}

void FCsBeamCollisionShape::CopyToShapeAsValue(BoxType* Shape) const
{
	Shape->SetScaleType((NCsBeam::NCollision::NShape::EScale)ScaleType);
	Shape->SetHalfExtents(HalfExtents);
}

#undef BoxType

#define CapsuleType NCsBeam::NCollision::NShape::FCapsule

void FCsBeamCollisionShape::CopyToShape(CapsuleType* Shape)
{
	Shape->SetScaleType((NCsBeam::NCollision::NShape::EScale*)&ScaleType);
	Shape->SetRadius(&Radius);
	Shape->SetHalfHeight(&HalfHeight);
}

void FCsBeamCollisionShape::CopyToShapeAsValue(CapsuleType* Shape) const
{
	Shape->SetScaleType((NCsBeam::NCollision::NShape::EScale)ScaleType);
	Shape->SetRadius(Radius);
	Shape->SetHalfHeight(HalfHeight);
}

#undef CapsuleType

#define ShapeType NCsBeam::NCollision::NShape::FShape

ShapeType* FCsBeamCollisionShape::ConstructShape()
{
	// Line
	if (Type == ECsBeamCollisionShapeType::Line)
	{
		typedef NCsBeam::NCollision::NShape::FLine LineType;

		LineType* Shape = new LineType();
		CopyToShape(Shape);
		return Shape;
	}
	// Box
	if (Type == ECsBeamCollisionShapeType::Box)
	{
		typedef NCsBeam::NCollision::NShape::FBox BoxType;

		BoxType* Shape = new BoxType();
		CopyToShape(Shape);
		return Shape;
	}
	// Capsule
	if (Type == ECsBeamCollisionShapeType::Capsule)
	{
		typedef NCsBeam::NCollision::NShape::FCapsule CapsuleType;

		CapsuleType* Shape = new CapsuleType();
		CopyToShape(Shape);
		return Shape;
	}
	return nullptr;
}

ShapeType* FCsBeamCollisionShape::ConstructShapeAsValue() const
{
	// Line
	if (Type == ECsBeamCollisionShapeType::Line)
	{
		typedef NCsBeam::NCollision::NShape::FLine LineType;

		LineType* Shape = new LineType();
		CopyToShapeAsValue(Shape);
		return Shape;
	}
	// Box
	if (Type == ECsBeamCollisionShapeType::Box)
	{
		typedef NCsBeam::NCollision::NShape::FBox BoxType;

		BoxType* Shape = new BoxType();
		CopyToShapeAsValue(Shape);
		return Shape;
	}
	// Capsule
	if (Type == ECsBeamCollisionShapeType::Capsule)
	{
		typedef NCsBeam::NCollision::NShape::FCapsule CapsuleType;

		CapsuleType* Shape = new CapsuleType();
		CopyToShapeAsValue(Shape);
		return Shape;
	}
	return nullptr;
}

#undef ShapeType

bool FCsBeamCollisionShape::IsValidChecked(const FString& Context) const
{
	check(EMCsBeamCollisionShapeScale::Get().IsValidEnumChecked(Context, ScaleType));

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
		CS_IS_VECTOR_ZERO_CHECKED(HalfExtents)
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

bool FCsBeamCollisionShape::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsBeam::FLog::Warning*/) const
{
	CS_IS_ENUM_VALID(EMCsBeamCollisionShapeScale, ECsBeamCollisionShapeScale, ScaleType)

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
		CS_IS_VECTOR_ZERO(HalfExtents)
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
		// FLine
		#pragma region

			bool FLine::IsValidChecked(const FString& Context) const
			{
				check(EMScale::Get().IsValidEnumChecked(Context, GetScaleType()));

				CS_IS_FLOAT_GREATER_THAN_CHECKED(GetLength(), 0.0f);
				return true;
			}

			bool FLine::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsBeam::FLog::Warning*/) const
			{
				CS_IS_ENUM_VALID(EMScale, EScale, GetScaleType())

				CS_IS_FLOAT_GREATER_THAN(GetLength(), 0.0f);
				return true;
			}

			#define ResponseType NCsTrace::NResponse::FResponse
			#define RequestType NCsTrace::NRequest::FRequest
			ResponseType* FLine::TraceChecked(const FString& Context, const UObject* WorldContext, RequestType* Request, const FVector& Direction, const FVector& Scale) const
			{
			#undef ResponseType
			#undef RequestType

				typedef NCsTrace::NManager::FLibrary TraceManagerLibrary;

				return TraceManagerLibrary::TraceChecked(Context, WorldContext, Request);
			}

		#pragma endregion FLine

		// FBox
		#pragma region

			bool FBox::IsValidChecked(const FString& Context) const
			{
				check(EMScale::Get().IsValidEnumChecked(Context, GetScaleType()));

				CS_IS_VECTOR_ZERO_CHECKED(GetHalfExtents())
				return true;
			}

			bool FBox::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsBeam::FLog::Warning*/) const
			{
				CS_IS_ENUM_VALID(EMScale, EScale, GetScaleType())

				CS_IS_VECTOR_ZERO(GetHalfExtents())
				return true;
			}

			#define ResponseType NCsTrace::NResponse::FResponse
			#define RequestType NCsTrace::NRequest::FRequest
			ResponseType* FBox::TraceChecked(const FString& Context, const UObject* WorldContext, RequestType* Request, const FVector& Direction, const FVector& Scale) const
			{
			#undef ResponseType
			#undef RequestType

				typedef NCsTrace::NManager::FLibrary TraceManagerLibrary;

				return TraceManagerLibrary::TraceChecked(Context, WorldContext, Request);
			}

		#pragma endregion FBox

		// FCapsule
		#pragma region

			bool FCapsule::IsValidChecked(const FString& Context) const
			{
				check(EMScale::Get().IsValidEnumChecked(Context, GetScaleType()));

				CS_IS_FLOAT_GREATER_THAN_CHECKED(GetRadius(), 0.0f);

				CS_IS_FLOAT_GREATER_THAN_CHECKED(GetHalfHeight(), 0.0f);
				return true;
			}

			bool FCapsule::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsBeam::FLog::Warning*/) const
			{
				CS_IS_ENUM_VALID(EMScale, EScale, GetScaleType())

				CS_IS_FLOAT_GREATER_THAN(GetRadius(), 0.0f);

				CS_IS_FLOAT_GREATER_THAN(GetHalfHeight(), 0.0f);
				return true;
			}

			#define ResponseType NCsTrace::NResponse::FResponse
			#define RequestType NCsTrace::NRequest::FRequest
			ResponseType* FCapsule::TraceChecked(const FString& Context, const UObject* WorldContext, RequestType* Request, const FVector& Direction, const FVector& Scale) const
			{
			#undef ResponseType
			#undef RequestType

				typedef NCsTrace::NManager::FLibrary TraceManagerLibrary;

				return TraceManagerLibrary::TraceChecked(Context, WorldContext, Request);
			}

		#pragma endregion FCapsule
		}
	}
}

#pragma endregion FCsBeamCollisionShape