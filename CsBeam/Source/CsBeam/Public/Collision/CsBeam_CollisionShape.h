// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "Types/Enum/CsEnumMap.h"
// Log
#include "Utility/CsBeamLog.h"

#include "CsBeam_CollisionShape.generated.h"

// BeamCollisionShapeScale
#pragma region

/**
* 
*/
UENUM(BlueprintType)
enum class ECsBeamCollisionShapeScale : uint8
{
	/** The scale is determined by Beam's collision data (NCsBeam::NData::NCollision::ICollision). */
	Default							UMETA(DisplayName = "Default"),
	/** The scale is determined by the Owner of the Beam. 
		Owner must implement the interface: ICsGetBeamScale. */
	Owner							UMETA(DisplayName = "Owner"),
	/** The scale is the product of a scalar from the Owner of the Beam
		and the Beam's collision data (NCsBeam::NData::NCollision::ICollision).
		Owner must implement the interface: ICsGetBeamScale. */
	OwnerAsScalar					UMETA(DisplayName = "Owner as Scalar"),
	ECsBeamCollisionShapeScale_MAX	UMETA(Hidden),
};

struct CSBEAM_API EMCsBeamCollisionShapeScale : public TCsEnumMap<ECsBeamCollisionShapeScale>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsBeamCollisionShapeScale, ECsBeamCollisionShapeScale)
};

namespace NCsBeamCollisionShapeScale
{
	typedef ECsBeamCollisionShapeScale Type;

	namespace Ref
	{
		extern CSBEAM_API const Type Default;
		extern CSBEAM_API const Type Owner;
		extern CSBEAM_API const Type OwnerAsScale;
		extern CSBEAM_API const Type ECsBeamCollisionShapeScaleMAX;
	}

	extern CSBEAM_API const uint8 MAX;
}

namespace NCsBeam
{
	namespace NCollision
	{
		namespace NShape
		{
			enum class EScale : uint8
			{
				Default,
				Owner,
				OwnerAsScalar,
				EScale_MAX
			};

			struct CSBEAM_API EMScale : public TCsEnumMap<EScale>
			{
				CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMScale, EScale)
			};

			namespace NScale
			{
				typedef EScale Type;

				namespace Ref
				{
					/** The scale is determined by Beam's collision data (NCsBeam::NData::NCollision::ICollision). */
					extern CSBEAM_API const Type Default;
					/** The scale is determined by the Owner of the Beam.
						Owner must implement the interface: ICsGetBeamScale. */
					extern CSBEAM_API const Type Owner;
					/** The scale is the product of a scalar from the Owner of the Beam
		`				and the Beam's collision data (NCsBeam::NData::NCollision::ICollision).
						Owner must implement the interface: ICsGetBeamScale. */
					extern CSBEAM_API const Type OwnerAsScalar;
					extern CSBEAM_API const Type EScale_MAX;
				}
			}
		}
	}
}

#pragma endregion BeamCollisionShapeScale

// BeamCollisionShapeType 
#pragma region

/**
*
*/
UENUM(BlueprintType)
enum class ECsBeamCollisionShapeType : uint8
{
	Line							UMETA(DisplayName = "Line"),
	Box								UMETA(DisplayName = "Box"),
	Capsule							UMETA(DisplayName = "Capsule"),
	ECsBeamCollisionShapeType_MAX	UMETA(Hidden),
};

struct CSBEAM_API EMCsBeamCollisionShapeType : public TCsEnumMap<ECsBeamCollisionShapeType>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsBeamCollisionShapeType, ECsBeamCollisionShapeType)
};

namespace NCsBeamCollisionShapeType
{
	typedef ECsBeamCollisionShapeType Type;

	namespace Ref
	{
		extern CSBEAM_API const Type Line;
		extern CSBEAM_API const Type Box;
		extern CSBEAM_API const Type Capsule;
		extern CSBEAM_API const Type ECsBeamCollisionShapeLength_MAX;
	}

	extern CSBEAM_API const uint8 MAX;
}

#pragma endregion BeamCollisionShapeType 

// FCsBeamCollisionShape
#pragma region

// NCsBeam::NCollision::Shape::FShape
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsBeam, NCollision, NShape, FShape)
// NCsBeam::NCollision::Shape::FLine
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsBeam, NCollision, NShape, FLine)
// NCsBeam::NCollision::Shape::FBox
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsBeam, NCollision, NShape, FBox)
// NCsBeam::NCollision::Shape::FCapsule
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsBeam, NCollision, NShape, FCapsule)

/**
* 
*/
USTRUCT(BlueprintType)
struct CSBEAM_API FCsBeamCollisionShape
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ECsBeamCollisionShapeType Type;

	/** Describes how the dimesions of the collision shape will be scaled. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ECsBeamCollisionShapeScale ScaleType;

	/** Only valid if Type == ECsBeamCollisionShapeLength::Line */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "0.0", UIMin = "0.0"))
	float Length;

	/** Only valid if Type == ECsBeamCollisionShapeLength::Box */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector3f HalfExtents;

	/** Only valid if Type == ECsBeamCollisionShapeLength::Capsule */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "0.0", UIMin = "0.0"))
	float Radius;

	/** Only valid if Type == ECsBeamCollisionShapeLength::Capsule */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "0.0", UIMin = "0.0"))
	float HalfHeight;

	FCsBeamCollisionShape() :
		Type(ECsBeamCollisionShapeType::Line),
		ScaleType(ECsBeamCollisionShapeScale::Default),
		Length(0.0f),
		HalfExtents(0.0f),
		Radius(0.0f),
		HalfHeight(0.0f)
	{
	}

#define LineType NCsBeam::NCollision::NShape::FLine
	void CopyToShape(LineType* Shape);
	void CopyToShapeAsValue(LineType* Shape) const;
#undef LineType

#define BoxType NCsBeam::NCollision::NShape::FBox
	void CopyToShape(BoxType* Shape);
	void CopyToShapeAsValue(BoxType* Shape) const;
#undef BoxType

#define CapsuleType NCsBeam::NCollision::NShape::FCapsule
	void CopyToShape(CapsuleType* Shape);
	void CopyToShapeAsValue(CapsuleType* Shape) const;
#undef CapsuleType

#define ShapeType NCsBeam::NCollision::NShape::FShape
	ShapeType* ConstructShape();
	ShapeType* ConstructShapeAsValue() const;
#undef ShapeType

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsBeam::FLog::Warning) const;
};

class UObject;

// NCsTrace::NResponse::FResponse
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsTrace, NResponse, FResponse)
// NCsTrace::NRequest::FRequest
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsTrace, NRequest, FRequest)

namespace NCsBeam
{
	namespace NCollision
	{
		namespace NShape
		{
			#define ResponseType NCsTrace::NResponse::FResponse
			#define RequestType NCsTrace::NRequest::FRequest

			/**
			* 
			*/
			struct CSBEAM_API FShape
			{
			public:

				FShape(){}
				virtual ~FShape(){}

				virtual bool IsValidChecked(const FString& Context) const { return false; };
				virtual bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsBeam::FLog::Warning) const { return false; };

				virtual ResponseType* TraceChecked(const FString& Context, const UObject* WorldContext, RequestType* Request, const FVector3f& Direction, const FVector3f& Scale) const { return nullptr; };
			};

			struct CSBEAM_API FLine : public FShape
			{
			private:

				CS_DECLARE_MEMBER_WITH_PROXY(ScaleType, EScale)
				CS_DECLARE_MEMBER_WITH_PROXY(Length, float)

			public:

				FLine() :
					CS_CTOR_INIT_MEMBER_WITH_PROXY(ScaleType, EScale::Default),
					CS_CTOR_INIT_MEMBER_WITH_PROXY(Length, 0.0f)
				{
					CS_CTOR_SET_MEMBER_PROXY(ScaleType);
					CS_CTOR_SET_MEMBER_PROXY(Length);
				}

				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(ScaleType, EScale)
				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Length, float)

				virtual bool IsValidChecked(const FString& Context) const override;
				virtual bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsBeam::FLog::Warning) const override;

				virtual ResponseType* TraceChecked(const FString& Context, const UObject* WorldContext, RequestType* Request, const FVector3f& Direction, const FVector3f& Scale) const override;
			};

			struct CSBEAM_API FBox : public FShape
			{
			public:

				CS_DECLARE_MEMBER_WITH_PROXY(ScaleType, EScale)

				/** Z component is in the direction of box oriented. 
					(i.e. the Z component will get scaled if LengthType (NCsBeam::NCollision::NShape::ELength) == ELength::Fixed. */
				CS_DECLARE_MEMBER_WITH_PROXY(HalfExtents, FVector3f)

				FBox() :
					CS_CTOR_INIT_MEMBER_WITH_PROXY(ScaleType, EScale::Default),
					CS_CTOR_INIT_MEMBER_WITH_PROXY(HalfExtents, FVector3f::ZeroVector)
				{
					CS_CTOR_SET_MEMBER_PROXY(ScaleType);
					CS_CTOR_SET_MEMBER_PROXY(HalfExtents);
				}

				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(ScaleType, EScale)
				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(HalfExtents, FVector3f)

				virtual bool IsValidChecked(const FString& Context) const override;
				virtual bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsBeam::FLog::Warning) const override;

				virtual ResponseType* TraceChecked(const FString& Context, const UObject* WorldContext, RequestType* Request, const FVector3f& Direction, const FVector3f& Scale) const override;
			};

			struct CSBEAM_API FCapsule : public FShape
			{
			public:

				CS_DECLARE_MEMBER_WITH_PROXY(ScaleType, EScale)
				CS_DECLARE_MEMBER_WITH_PROXY(Radius, float)
				CS_DECLARE_MEMBER_WITH_PROXY(HalfHeight, float)

				FCapsule() :
					CS_CTOR_INIT_MEMBER_WITH_PROXY(ScaleType, EScale::Default),
					CS_CTOR_INIT_MEMBER_WITH_PROXY(Radius, 0.0f),
					CS_CTOR_INIT_MEMBER_WITH_PROXY(HalfHeight, 0.0f)
				{
					CS_CTOR_SET_MEMBER_PROXY(ScaleType);
					CS_CTOR_SET_MEMBER_PROXY(Radius);
					CS_CTOR_SET_MEMBER_PROXY(HalfHeight);
				}

				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(ScaleType, EScale)
				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Radius, float)
				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(HalfHeight, float)

				virtual bool IsValidChecked(const FString& Context) const override;
				virtual bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsBeam::FLog::Warning) const override;

				virtual ResponseType* TraceChecked(const FString& Context, const UObject* WorldContext, RequestType* Request, const FVector3f& Direction, const FVector3f& Scale) const override;
			};

			#undef ResponseType
			#undef RequestType
		}
	}
}

#pragma endregion BeamCollisionShape