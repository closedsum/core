// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Interface.h"
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "Collision/CsTypes_Collision.h"

#include "CsData_Beam_Collision.generated.h"

class UObject;

// NCsBeam::NCollision::NShape::IShape
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsBeam, NCollision, NShape, IShape)

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

			#define CollisionShapeType NCsBeam::NCollision::NShape::IShape

				/**
				* Get the collision shape
				* 
				* return Radius
				*/
				virtual const CollisionShapeType* GetCollisionShape() const = 0;

			#undef CollisionShapeType

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

#define CollisionShapeType NCsBeam::NCollision::NShape::IShape

	/**
	* Get the collision shape
	* 
	* return Radius
	*/
	virtual const CollisionShapeType* GetCollisionShape() const = 0;

#undef CollisionShapeType

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