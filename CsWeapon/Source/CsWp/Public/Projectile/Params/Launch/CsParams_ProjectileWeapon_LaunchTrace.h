// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Managers/Trace/CsTypes_Trace.h"

#include "Containers/CsGetInterfaceMap.h"

namespace NCsWeapon
{
	namespace NProjectile
	{
		namespace NParams
		{
			namespace NLaunch
			{
			// TraceStart
			#pragma region

				/**
				* Describes how the start of a trace should be chosen.
				*/
				enum class ETraceStart : uint8 
				{
					/** The launch location (the result from ILaunch::GetLocationType()) is used. 
						See NCsWeapon::NCsProjectile::NParams::NLaunch::ELocation. */
					LaunchLocation,
					/** Owner's Location. If the Owner is of type: AActor, then it will
						be GetActorLocation(). */
					Owner,
					/** If there is a Skeletal Mesh that acts as the root object for the Weapon,
						use the Bone's location. */
					Bone,
					Component,
					/** Owner's Camera's Location. */
					Camera,
					Custom
				};

			#pragma endregion TraceStart

			// TraceDirection
			#pragma region

				/**
				* Describes how the direction (end) of a trace should be chosen. The normalized
				* direction is used to project outward GetTraceDistance() from the start of the 
				* trace.
				*/
				enum class ETraceDirection : uint8
				{
					/** Owner's Rotation (forward). If the Owner is of type: AActor, then use 
					    get the Owner's forward vector. */
					Owner,
					/** If there is a Skeletal Mesh that acts as the root object for the Weapon,
						then use the Bone's rotation (to normalized vector). */
					Bone,
					Component,
					/** Owner's Camera's Rotation (forward). */
					Camera,
					Custom
				};

			#pragma endregion TraceDirection

				namespace NTrace
				{
					/**
					*/
					struct CSWP_API ITrace : public ICsGetInterfaceMap
					{
					public:

						static const FName Name;

					public:

						virtual ~ITrace() {}

						/**
						*
						*
						* return Trace Type
						*/
						virtual const ECsTraceType& GetTraceType() const = 0;

						/**
						*
						*
						* return Trace Method
						*/
						virtual const ECsTraceMethod& GetTraceMethod() const = 0;

						/**
						*
						*
						* return Trace Start Type
						*/
						virtual const ETraceStart& GetTraceStartType() const = 0;

						/**
						*
						*
						* return Trace Direction Type
						*/
						virtual const ETraceDirection& GetTraceDirectionType() const = 0;

						/**
						*
						*
						* return Distance
						*/
						virtual const float& GetTraceDistance() const = 0;
					};
				}
			}
		}
	}
}