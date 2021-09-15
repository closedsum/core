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

		CSBEAM_API CS_ADD_TO_ENUM_MAP(Fixed);
		CSBEAM_API CS_ADD_TO_ENUM_MAP(Scaled);
		CSBEAM_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsBeamCollisionShapeLength_MAX, "MAX");
	}

	CSBEAM_API const uint8 MAX = (uint8)Type::ECsBeamCollisionShapeLength_MAX;
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

					CSBEAM_API CS_ADD_TO_ENUM_MAP(Fixed);
					CSBEAM_API CS_ADD_TO_ENUM_MAP(Scaled);
					CSBEAM_API CS_ADD_TO_ENUM_MAP_CUSTOM(ELength_MAX, "MAX");
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

ShapeType* FCsBeamCollisionShape::ConstructShapeAsValue() const
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

bool FCsBeamCollisionShape::IsValidChecked(const FString& Context) const
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
				check(EMLength::Get().IsValidEnumChecked(Context, GetLengthType()));

				CS_IS_FLOAT_GREATER_THAN_CHECKED(GetLength(), 0.0f);
				return true;
			}

			bool FLine::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsBeam::FLog::Warning*/) const
			{
				CS_IS_ENUM_VALID(EMLength, ELength, GetLengthType())

				CS_IS_FLOAT_GREATER_THAN(GetLength(), 0.0f);
				return true;
			}

			#define ResponseType NCsTrace::NResponse::FResponse
			#define RequestType NCsTrace::NRequest::FRequest
			ResponseType* FLine::TraceChecked(const FString& Context, const UObject* WorldContext, RequestType* Request) const
			{
			#undef ResponseType
			#undef RequestType

				if (GetLengthType() == ELength::Fixed)
				{
					const FVector Dir = (Request->End - Request->Start).GetSafeNormal();
					Request->End	  = Request->Start + GetLength() * Dir;
				}

				typedef NCsTrace::NManager::FLibrary TraceManagerLibrary;

				return TraceManagerLibrary::TraceChecked(Context, WorldContext, Request);
			}

		#pragma endregion FLine

		// FBox
		#pragma region

			bool FBox::IsValidChecked(const FString& Context) const
			{
				check(EMLength::Get().IsValidEnumChecked(Context, GetLengthType()));

				CS_IS_VECTOR_ZERO_CHECKED(GetHalfExtents())
				return true;
			}

			bool FBox::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsBeam::FLog::Warning*/) const
			{
				CS_IS_ENUM_VALID(EMLength, ELength, GetLengthType())

				CS_IS_VECTOR_ZERO(GetHalfExtents())
				return true;
			}

			#define ResponseType NCsTrace::NResponse::FResponse
			#define RequestType NCsTrace::NRequest::FRequest
			ResponseType* FBox::TraceChecked(const FString& Context, const UObject* WorldContext, RequestType* Request) const
			{
			#undef ResponseType
			#undef RequestType

				if (GetLengthType() == ELength::Fixed)
				{
					//const FVector Dir = (Request->End - Request->Start).GetSafeNormal();
					//Request->End	  = Request->Start + GetLength() * Dir;
				}

				typedef NCsTrace::NManager::FLibrary TraceManagerLibrary;

				return TraceManagerLibrary::TraceChecked(Context, WorldContext, Request);
			}

		#pragma endregion FBox

		// FCapsule
		#pragma region

			bool FCapsule::IsValidChecked(const FString& Context) const
			{
				check(EMLength::Get().IsValidEnumChecked(Context, GetLengthType()));

				CS_IS_FLOAT_GREATER_THAN_CHECKED(GetRadius(), 0.0f);

				CS_IS_FLOAT_GREATER_THAN_CHECKED(GetHalfHeight(), 0.0f);
				return true;
			}

			bool FCapsule::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsBeam::FLog::Warning*/) const
			{
				CS_IS_ENUM_VALID(EMLength, ELength, GetLengthType())

				CS_IS_FLOAT_GREATER_THAN(GetRadius(), 0.0f);

				CS_IS_FLOAT_GREATER_THAN(GetHalfHeight(), 0.0f);
				return true;
			}

			#define ResponseType NCsTrace::NResponse::FResponse
			#define RequestType NCsTrace::NRequest::FRequest
			ResponseType* FCapsule::TraceChecked(const FString& Context, const UObject* WorldContext, RequestType* Request) const
			{
			#undef ResponseType
			#undef RequestType

				if (GetLengthType() == ELength::Fixed)
				{
					//const FVector Dir = (Request->End - Request->Start).GetSafeNormal();
					//Request->End	  = Request->Start + GetLength() * Dir;
				}

				typedef NCsTrace::NManager::FLibrary TraceManagerLibrary;

				return TraceManagerLibrary::TraceChecked(Context, WorldContext, Request);
			}

		#pragma endregion FCapsule
		}
	}
}

#pragma endregion FCsBeamCollisionShape