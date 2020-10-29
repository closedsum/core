// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Containers
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "Engine/EngineTypes.h"
#include "CollisionShape.h"

namespace NCsWeapon
{
	namespace NTrace
	{
		namespace NParams
		{
			namespace NTrace
			{
			// Location
			#pragma region

				/**
				* Describes the different methods to get the Location from which a trace
				* will be preformed from a weapon of type: ICsTraceWeapon.
				*/
				enum class ELocation : uint8
				{
					/** Root object's Location (usually a SceneComponent). */
					Self,
					/** Owner's Location. If the Owner is of type: AActor, then it will
						be GetActorLocation(). */
					Owner,
					/** If there is a SkeletalMesh that acts as the root object for the 
						Weapon, use the Bone's location. */ 
					Bone,
					/** If there is a SkeletalMesh that acts as the root object for the 
						Weapon, use the Socket's location. */ 
					Socket,
					/** SceneComponent's Location. The Component is marked as the Trace Component Transform. */
					Component,
					/** Owner's Camera's Location. */
					Camera,
					Custom
				};

			#pragma endregion Location

			// Direction
			#pragma region

				/**
				* Describes the different methods to get the Direction from which a trace
				* will be performed from a weapon of type: ICsTraceWeapon.
				*/
				enum class EDirection : uint8
				{
					/** Root object's direction (usually a SceneComponent). */
					Self,
					/** Owner's Rotation. If the Owner is of type: AActor, then it will
						be GetActorRotation(). */
					Owner,
					/** If there is a SkeletalMesh that acts as the root object for the Weapon, 
						use the Bone's rotation. */
					Bone,
					/** If there is a SkeletalMesh that acts as the root object for the Weapon,
						use the Socket's rotation. */
					Socket,
					/** SceneComponent's Rotation. The Component is marked as the Trace Component Transform. */
					Component,
					/** Owner's Camera's Rotation. */
					Camera,
					/** A trace is used to determine the direction. The start and end points of the 
						trace are determined by other parameters. 
						TODO: Have a mechanism to determine start and end points of this trace.
						TEMP: Default behavior is for start of trace to the Owner's Camera's Location and
							  direction to be the Owner's Camera's Direction. */
					Trace,
					Custom
				};
				
			#pragma endregion Direction

				/**
				* Describes Location related information for performing a trace from a 
				* weapon of type: ICsTraceWeapon.
				*/
				struct CSWP_API FLocationInfo
				{
				private:

					ELocation Type;
					ELocation* Type_Emu;

					FName BoneOrSocket;
					FName* BoneOrSocket_Emu;

				public:

					FLocationInfo() :
						Type(ELocation::Self),
						Type_Emu(nullptr),
						BoneOrSocket(NAME_None),
						BoneOrSocket_Emu(nullptr)
					{
						Type_Emu = &Type;
						BoneOrSocket_Emu = &BoneOrSocket;
					}

					FORCEINLINE void SetType(ELocation* Value) { Type_Emu = Value; }
					FORCEINLINE const ELocation& GetType() const { return *Type_Emu; }

					FORCEINLINE void SetBoneOrSocket(FName* Value) { BoneOrSocket_Emu = Value; }

					/**
					* Get the Bone from which Location information is used.
					* Only valid if:
					*  GetType() == ELocation::Bone ||
* 					*  GetType() == ELocation::Socket
					*
					* return Bone or Socket name
					*/
					FORCEINLINE const FName& GetBoneOrSocket() const { return *BoneOrSocket_Emu; }
				};

				/**
				* Describes Direction related information for performing a trace from a 
				* weapon of type: ICsTraceWeapon
				*/
				struct CSWP_API FDirectionInfo 
				{
				private:

					EDirection Type;
					EDirection* Type_Emu;

					FName BoneOrSocket;
					FName* BoneOrSocket_Emu;

					int32 Rules;
					int32* Rules_Emu;

				public:

					FDirectionInfo() :
						Type(EDirection::Self),
						Type_Emu(nullptr),
						BoneOrSocket(NAME_None),
						BoneOrSocket_Emu(nullptr),
						Rules(3), // CS_ROTATION_FLAGS_PITCH_AND_YAW
						Rules_Emu(nullptr)
					{
						Type_Emu = &Type;
						BoneOrSocket_Emu = &BoneOrSocket;
						Rules_Emu = &Rules;
					}

					FORCEINLINE void SetType(EDirection* Value) { Type_Emu = Value; }
					FORCEINLINE const EDirection& GetType() const { return *Type_Emu; }

					FORCEINLINE void SetBoneOrSocket(FName* Value) { BoneOrSocket_Emu = Value; }

					/**
					* Get the Bone from which Direction information is used.
					* Only valid if:
					*  GetType() == EDirection::Bone ||
* 					*  GetType() == EDirection::Socket
					*
					* return Bone or Socket name
					*/
					FORCEINLINE const FName& GetBoneOrSocket() const { return *BoneOrSocket_Emu; }

					FORCEINLINE void SetRules(int32* Value) { Rules_Emu = Value; }

					/**
					* Get the Rules, components (Pitch, Yaw, Roll), to use from a given rotation
					* when calculating the Direction.
					*  See ECsRotationRules
					*
					* return Rules as a mask.
					*/
					FORCEINLINE const int32& GetRules() const { return *Rules_Emu; }
				};

				/**
				* Interface describing the Trace Parameters for a weapon of type: ICsTraceWeapon. The
				* parameters are usually used to location and direction of a projectile being fired from the weapon.
				*/
				struct CSWP_API ITrace : public ICsGetInterfaceMap
				{
				public:

					static const FName Name;

				public:

					virtual ~ITrace() {}

					/**
					* Get the Location related information for performing a trace for a
					* weapon of type: ICsTraceWeapon.
					*
					* return Location Info 
					*/
					virtual const FLocationInfo& GetLocationInfo() const = 0;

					/**
					* Get the Direction related information for performing a trace from a
					* weapon of type: ICsTraceWeapon
					*
					* return Direction Info
					*/
					virtual const FDirectionInfo& GetDirectionInfo() const = 0;

					/**
					* Get the ObjectTypes to perform the trace again.
					*
					* return ObjectTypes 
					*/
					virtual const TArray<ECollisionChannel>& GetObjectTypes() const = 0;

					/**
					* Get the shape of the trace (Box, Sphere, Capsule).
					*
					* return Shape
					*/
					virtual const FCollisionShape& GetShape() const = 0;

					/**
					* Get the length of the trace. 
					*/
					virtual const float& GetDistance() const = 0;
				};
			}
		}
	}
}