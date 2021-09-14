// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Types
#include "Types/Enum/CsEnumMap.h"
// Log
#include "Utility/CsBeamLog.h"

// BeamCollisionShapeLength
#pragma region

/**
* 
*/
UENUM(BlueprintType)
enum class ECsBeamCollisionShapeLength : uint8
{
	Fixed							UMETA(DisplayName = "Fixed"),
	Scaled							UMETA(DisplayName = "Scaled"),
	ECsBeamCollisionShapeLength_MAX	UMETA(Hidden),
};

struct CSBEAM_API EMCsBeamCollisionShapeLength : public TCsEnumMap<ECsBeamCollisionShapeLength>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsBeamCollisionShapeLength, ECsBeamCollisionShapeLength)
};

namespace NCsBeamCollisionShapeLength
{
	typedef ECsBeamCollisionShapeLength Type;

	namespace Ref
	{
		extern CSBEAM_API const Type Fixed;
		extern CSBEAM_API const Type Scaled;
		extern CSBEAM_API const Type ECsBeamCollisionShapeLength_MAX;
	}

	extern CSBEAM_API const uint8 MAX;
}

namespace NCsBeam
{
	namespace NCollision
	{
		namespace NShape
		{
			enum class ELength : uint8
			{
				Fixed,
				Scaled,
				ELength_MAX
			};

			struct CSBEAM_API EMLength : public TCsEnumMap<ELength>
			{
				CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMLength, ELength)
			};

			namespace NLength
			{
				typedef ELength Type;

				namespace Ref
				{
					extern CSBEAM_API const Type Fixed;
					extern CSBEAM_API const Type Scaled;
					extern CSBEAM_API const Type ECsBeamCollisionShapeLength_MAX;
				}
			}
		}
	}
}

#pragma endregion BeamCollisionShapeLength

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

// NCsBeam::NCollision::Shape::FLine
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsBeam, NCollision, NShape, FLine)

/**
* 
*/
USTRUCT(BlueprintType)
struct CSCORE_API FCsBeamCollisionShape
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ECsBeamCollisionShapeType Type;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ECsBeamCollisionShapeLength LengthType;

	/** Only valid if Type == ECsBeamCollisionShapeLength::Line */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "0.0", UIMin = "0.0"))
	float Length;

	/** Only valid if Type == ECsBeamCollisionShapeLength::Box */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector HalfExtents;

	/** Only valid if Type == ECsBeamCollisionShapeLength::Capsule */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "0.0", UIMin = "0.0"))
	float Radius;

	/** Only valid if Type == ECsBeamCollisionShapeLength::Capsule */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "0.0", UIMin = "0.0"))
	float HalfHeight;

	FCsBeamCollisionShape() :
		Type(ECsBeamCollisionShapeType::Line),
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

#define ShapeType NCsBeam::NCollision::NShape::FShape
	ShapeType* ConstructShape();
	ShapeType* ConstructShapeAsValue();
#undef ShapeType

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsBeam::FLog::Warning) const;
};

class UObject;

// NCsTrace::NResponse::FResponse
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsTrace, NResponse, FResponse)
// NCsTrace::NRequest::FRequest
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsTrace, NResponse, FResponse)

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

				virtual ResponseType* TraceChecked(const FString& Context, const UObject* WorldContext, RequestType* Request) const {};
			};

			struct CSBEAM_API FLine
			{
			private:

				CS_DECLARE_MEMBER_WITH_PROXY(LengthType, ELength)
				CS_DECLARE_MEMBER_WITH_PROXY(Length, float)

			public:

				FLine() :
					CS_CTOR_INIT_MEMBER_WITH_PROXY(LengthType, ELength::Scaled),
					CS_CTOR_INIT_MEMBER_WITH_PROXY(Length, 0.0f)
				{
					CS_CTOR_SET_MEMBER_PROXY(LengthType);
					CS_CTOR_SET_MEMBER_PROXY(Length);
				}

				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(LengthType, ELength)
				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Length, float)

				bool IsValidChecked(const FString& Context) const;
				bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsBeam::FLog::Warning) const;

				virtual ResponseType* TraceChecked(const FString& Context, const UObject* WorldContext, RequestType* Request) const override;
			};

			struct CSBEAM_API FBox
			{
			public:

				CS_DECLARE_MEMBER_WITH_PROXY(LengthType, ELength)

				/** Z component is in the direction of box oriented. 
					(i.e. the Z component will get scaled if LengthType (NCsBeam::NCollision::NShape::ELength) == ELength::Fixed. */
				CS_DECLARE_MEMBER_WITH_PROXY(HalfExtents, FVector)

				FBox() :
					CS_CTOR_INIT_MEMBER_WITH_PROXY(LengthType, ELength::Scaled),
					CS_CTOR_INIT_MEMBER_WITH_PROXY(HalfExtents, FVector::ZeroVector)
				{
					CS_CTOR_SET_MEMBER_PROXY(LengthType);
					CS_CTOR_SET_MEMBER_PROXY(HalfExtents);
				}

				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(LengthType, ELength)
				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(HalfExtents, FVector)
			};

			struct CSBEAM_API FCapsule
			{
			public:

				CS_DECLARE_MEMBER_WITH_PROXY(LengthType, ELength)
				CS_DECLARE_MEMBER_WITH_PROXY(Radius, float)
				CS_DECLARE_MEMBER_WITH_PROXY(HalfHeight, float)

				FCapsule() :
					CS_CTOR_INIT_MEMBER_WITH_PROXY(LengthType, ELength::Scaled),
					CS_CTOR_INIT_MEMBER_WITH_PROXY(Radius, 0.0f),
					CS_CTOR_INIT_MEMBER_WITH_PROXY(HalfHeight, 0.0f)
				{
					CS_CTOR_SET_MEMBER_PROXY(LengthType);
					CS_CTOR_SET_MEMBER_PROXY(Radius);
					CS_CTOR_SET_MEMBER_PROXY(HalfHeight);
				}
			};

			#undef ResponseType
			#undef RequestType
		}
	}
}

#pragma endregion BeamCollisionShape