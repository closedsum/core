// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

#include "UObject/Interface.h"
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "Collision/CsTypes_Collision.h"
#include "Collision/CsTypes_Beam_Collision.h"

#include "CsData_Beam_Collision.generated.h"

class UObject;

// NCsBeam::NCollision::NShape::FShape
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsBeam, NCollision, NShape, FShape)

namespace NCsBeam
{
	namespace NData
	{
		namespace NCollision
		{
			/**
			* Interface for describing any collision associated with a Beam.
			*/
			struct CSBEAM_API ICollision : public ICsGetInterfaceMap
			{
			public:

				static const FName Name;

			public:

				virtual ~ICollision() {}

				/**
				* Get the collision information (i.e. response, overlap, hit events, ... etc)
				*
				* return Preset
				*/
				virtual const FCsCollisionPreset& GetCollisionPreset() const = 0;

			#define ShapeType NCsBeam::NCollision::NShape::FShape

				/**
				* Get the collision shape
				* 
				* return Shape
				*/
				virtual const ShapeType* GetCollisionShape() const = 0;

			#undef ShapeType

			#define FrequencyParamsType NCsBeam::NCollision::NParams::FFrequency

				/**
				*/
				virtual const FrequencyParamsType& GetCollisionFrequencyParams() const = 0;

			#undef FrequencyParamsType

				/**
				* Get the number of collisions before the beam
				* is Off (and / or deallocated if pooled).
				* NOTE:
				* - If a StaticMesh is used for collision,
				*	 Collision detection is captured via MeshComponent->OnComponentHit.
				*	 GetCollisionPreset().bSimulationGeneratesHitEvents MUST be true for the count to be meaningful.
				* 
				* return Count
				*/
				virtual const int32& GetCollisionCount() const = 0;

				/**
				* Whether to ignore an object (AActor or UPrimitiveComponent) the beam has collided with after
				* the first collision.
				* 
				* return
				*/
				virtual const bool& IgnoreCollidingObjectAfterCollision() const = 0;

				/**
				* Get the list of classes to ignore for colliding objects.
				* 
				* return
				*/
				virtual const TArray<TSubclassOf<UObject>>& GetIgnoreCollidingObjectClasses() const = 0;
			};
		}
	}
}

UINTERFACE(BlueprintType)
class CSBEAM_API UCsData_Beam_Collision : public UCsGetInterfaceMap
{
	GENERATED_UINTERFACE_BODY()
};

class UObject;

// NCsBeam::NCollision::NShape::FShape
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsBeam, NCollision, NShape, FShape)

/**
* Interface for describing any collision associated with a Beam.
*/
class CSBEAM_API ICsData_Beam_Collision : public ICsGetInterfaceMap
{
	GENERATED_IINTERFACE_BODY()

public:

	static const FName Name;

	/**
	* Get the collision information (i.e. response, overlap, hit events, ... etc)
	*
	* return Preset
	*/
	virtual const FCsCollisionPreset& GetCollisionPreset() const = 0;

#define CollisionShapeType NCsBeam::NCollision::NShape::FShape

	/**
	* Get the collision shape
	* 
	* return Radius
	*/
	virtual const CollisionShapeType* GetCollisionShape() const = 0;

#undef CollisionShapeType

#define FrequencyParamsType NCsBeam::NCollision::NParams::FFrequency

	/**
	*/
	virtual const FrequencyParamsType& GetCollisionFrequencyParams() const = 0;

#undef FrequencyParamsType

	/**
	* Get the number of collisions before the beam
	* is Off (and / or deallocated if pooled).
	* NOTE:
	* - If a StaticMesh is used for collision,
	*	 Collision detection is captured via MeshComponent->OnComponentHit.
	*	 GetCollisionPreset().bSimulationGeneratesHitEvents MUST be true for the count to be meaningful.
	*
	* return Count
	*/
	virtual const int32& GetCollisionCount() const = 0;

	/**
	* Whether to ignore an object (AActor or UPrimitiveComponent) the beam has collided with after
	* the first collision.
	*
	* return
	*/
	virtual const bool& IgnoreCollidingObjectAfterCollision() const = 0;

	/**
	* Get the list of classes to ignore for colliding objects.
	*
	* return
	*/
	virtual const TArray<TSubclassOf<UObject>>& GetIgnoreCollidingObjectClasses() const = 0;
};