// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "Collision/CsTypes_Collision.h"
#include "Collision/CsBeam_CollisionShape.h"
// Log
#include "Utility/CsBeamLog.h"
// Data
#include "Data/Collision/CsData_Beam_Collision.h"

#include "CsData_Beam_CollisionImplSlice.generated.h"

class UObject;

// NCsBeam::NData::NCollision::FImplSlice
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsBeam, NData, NCollision, FImplSlice)

/**
* Represents a "slice" of data, CollisionDataType (NCsBeam::NData::NCollision::ICollision).
* The idea behind this struct is to "build" the data via composition of separate objects that each implementation
* a specific interface. The whole data will be constructed elsewhere in native (usually a manager).
*/
USTRUCT(BlueprintType)
struct CSBEAM_API FCsData_Beam_CollisionImplSlice
{
	GENERATED_USTRUCT_BODY()

public:

// CollisionDataType (NCsBeam::NData::NCollision::IData)

	/** Collision information (i.e. response, overlap, hit events, ... etc) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsBeam|Data|Collision")
	FCsCollisionPreset Preset;

	/** Describes the shape of the collision (i.e. Line, Box, Capsule, ... etc) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsBeam|Data|Collision")
	FCsBeamCollisionShape Shape;

	/** Describes the rate at which collision 'passes' (sweep or trace) should be performed. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsBeam|Data|Collision")
	FCsBeamCollisionFrequencyParams FrequencyParams;

	/** Number of collisions before the beam is Off (and / or deallocated if pooled).
		NOTE:
		- If a StaticMesh is used for collision,
			Collision detection is captured via MeshComponent->OnComponentHit.
			GetCollisionPreset().bSimulationGeneratesHitEvents MUST be true for the count to be meaningful. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsBeam|Data|Collision", meta = (UIMin = "0", ClampMin = "0"))
	int32 CollisionCount;

	/** Whether to ignore an object (AActor or UPrimitiveComponent) the beam has collided with after
		the first collision. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsBeam|Data|Collision")
	bool bIgnoreCollidingObjectAfterCollision;

	/** List of classes to ignore for colliding objects. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsBeam|Data|Collision")
	TArray<TSubclassOf<UObject>> IgnoreCollidingObjectClasses;

	FCsData_Beam_CollisionImplSlice() :
		Preset(),
		Shape(),
		FrequencyParams(),
		CollisionCount(0),
		bIgnoreCollidingObjectAfterCollision(false),
		IgnoreCollidingObjectClasses()
	{
	}

#define SliceType NCsBeam::NData::NCollision::FImplSlice

	SliceType* AddSafeSlice(const FString& Context, const UObject* WorldContext, const FName& Name, void(*Log)(const FString&) = &NCsBeam::FLog::Warning);
	SliceType* AddSafeSliceAsValue(const FString& Context, const UObject* WorldContext, const FName& Name, void(*Log)(const FString&) = &NCsBeam::FLog::Warning) const;

private:

	SliceType* AddSafeSlice_Internal(const FString& Context, const UObject* WorldContext, const FName& Name, void(*Log)(const FString&) = &NCsBeam::FLog::Warning) const;

public:

	void CopyToSlice(SliceType* Slice);
	void CopyToSliceAsValue(SliceType* Slice) const;

#undef SliceType

	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsBeam::FLog::Warning) const;
};

struct FCsInterfaceMap;
class UObject;

namespace NCsBeam
{
	namespace NData
	{
		namespace NCollision
		{
		#define CollisionDataType NCsBeam::NData::NCollision::ICollision

			/**
			* Represents a "slice" of data, CollisionDataType (NCsBeam::NData::NCollision::ICollision).
			* 
			* If members are set via points to an "owning" data, then
			* "Emulates" CollisionDataType (NCsBeam::NData::NCollision::ICollision) by mimicking 
			* the interfaces and having pointers to the appropriate members. 
			* 
			* The idea behind this struct is to "build" the data via composition of separate objects that each implementation
			* a specific interface. The whole data will be constructed elsewhere in native (usually a manager).
			*/
			struct CSBEAM_API FImplSlice final : public CollisionDataType
			{
			public:

				static const FName Name;

			#define ShapeType NCsBeam::NCollision::NShape::FShape
			#define FrequencyParamsType NCsBeam::NCollision::NParams::FFrequency

			private:
			
				// ICsGetInterfaceMap

				/** Pointer to the "root" object for all "Impl Slices". That object acts as the hub for the separate objects (via composition) 
					that describe the data. */
				FCsInterfaceMap* InterfaceMap;

				// CollisionDataType (NCsBeam::NData::NCollision::ICollision)

				CS_DECLARE_MEMBER_WITH_PROXY(CollisionPreset, FCsCollisionPreset)
				CS_DECLARE_MEMBER_WITH_PROXY(CollisionShape, ShapeType*)

				FrequencyParamsType CollisionFrequencyParams;

				CS_DECLARE_MEMBER_WITH_PROXY(CollisionCount, int32)
				CS_DECLARE_MEMBER_WITH_PROXY(bIgnoreCollidingObjectAfterCollision, bool)
				CS_DECLARE_MEMBER_WITH_PROXY(IgnoreCollidingObjectClasses, TArray<TSubclassOf<UObject>>)

			public:

				FImplSlice() :
					CS_CTOR_INIT_MEMBER_STRUCT_WITH_PROXY(CollisionPreset),
					CS_CTOR_INIT_MEMBER_WITH_PROXY(CollisionShape, nullptr),
					CollisionFrequencyParams(),
					CS_CTOR_INIT_MEMBER_WITH_PROXY(CollisionCount, 0),
					CS_CTOR_INIT_MEMBER_WITH_PROXY(bIgnoreCollidingObjectAfterCollision, false),
					CS_CTOR_INIT_MEMBER_ARRAY_WITH_PROXY(IgnoreCollidingObjectClasses)
				{
					CS_CTOR_SET_MEMBER_PROXY(CollisionPreset);
					CS_CTOR_SET_MEMBER_PROXY(CollisionShape);
					CS_CTOR_SET_MEMBER_PROXY(CollisionCount);
					CS_CTOR_SET_MEMBER_PROXY(bIgnoreCollidingObjectAfterCollision);
					CS_CTOR_SET_MEMBER_PROXY(IgnoreCollidingObjectClasses);
				}

				~FImplSlice()
				{
					delete CollisionShape;
				}

				FORCEINLINE UObject* _getUObject() const { return nullptr; }

			public:

				FORCEINLINE void SetInterfaceMap(FCsInterfaceMap* Map) { InterfaceMap = Map; }

			// ICsGetInterfaceMap
			#pragma region
			public:

				FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const { return InterfaceMap; }

			#pragma endregion ICsGetInterfaceMap

			public:

				FORCEINLINE void ConditionalSetCollisionShape(ShapeType* Shape)
				{
					if (CollisionShape)
						delete CollisionShape;

					CollisionShape = Shape;
					CollisionShape_Proxy = &CollisionShape;
				}

				FORCEINLINE FrequencyParamsType* GetCollisionFrequencyParamsPtr() { return &CollisionFrequencyParams; }
				FORCEINLINE void SetIgnoreCollidingObjectAfterCollision(const bool& Value)
				{
					bIgnoreCollidingObjectAfterCollision = Value;
					bIgnoreCollidingObjectAfterCollision_Proxy = &bIgnoreCollidingObjectAfterCollision;
				}
				FORCEINLINE void SetIgnoreCollidingObjectAfterCollision(bool* Value) { check(Value); bIgnoreCollidingObjectAfterCollision_Proxy = Value; }

			// CollisionDataType (NCsBeam::NData::NCollision::ICollision)
			#pragma region
			public:

				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(CollisionPreset, FCsCollisionPreset)

				FORCEINLINE const ShapeType* GetCollisionShape() const { return *CollisionShape_Proxy; }
				FORCEINLINE const FrequencyParamsType& GetCollisionFrequencyParams() const { return CollisionFrequencyParams; }

				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(CollisionCount, int32)

				FORCEINLINE const bool& IgnoreCollidingObjectAfterCollision() const { return *bIgnoreCollidingObjectAfterCollision_Proxy; }

				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(IgnoreCollidingObjectClasses, TArray<TSubclassOf<UObject>>)

			#pragma endregion CollisionDataType (NCsBeam::NData::NCollision::ICollision)

			public:

				static void Deconstruct(void* Ptr)
				{
					delete static_cast<NCsBeam::NData::NCollision::FImplSlice*>(Ptr);
				}

				static FImplSlice* AddSafeSlice(const FString& Context, const UObject* WorldContext, const FName& DataName, UObject* Object, void(*Log)(const FString&) = &NCsBeam::FLog::Warning);

				bool IsValidChecked(const FString& Context) const;
				bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsBeam::FLog::Warning) const;

			#undef ShapeType
			#undef FrequencyParamsType
			};

		#undef CollisionDataType
		}
	}
}