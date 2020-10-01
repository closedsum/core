// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Interfaces
#include "Projectile/Params/Launch/CsParams_ProjectileWeapon_Launch.h"
#include "Projectile/Params/Launch/CsParams_ProjectileWeapon_LaunchTrace.h"
// Types
#include "Projectile/Params/Launch/CsTypes_Params_ProjectileWeapon_LaunchTrace.h"

namespace NCsWeapon
{
	namespace NProjectile
	{
		namespace NParams
		{
			namespace NLaunch
			{
				/**
				*/
				struct CSWP_API FTraceEmu : public ILaunch,
											public ITrace
				{
				public:

					static const FName Name;

				private:

					// ILaunch

					ELocation* LocationType;

					EDirection* DirectionType;

					// ITrace

					ECsTraceType* TraceType;

					ECsTraceMethod* TraceMethod;

					ETraceStart* TraceStartType;

					ETraceDirection* TraceDirectionType;

					float* TraceDistance;

				public:

					FTraceEmu() :
						LocationType(nullptr),
						DirectionType(nullptr),
						TraceType(nullptr),
						TraceMethod(nullptr),
						TraceStartType(nullptr),
						TraceDirectionType(nullptr),
						TraceDistance(nullptr)
					{
					}

					~FTraceEmu(){}

				// ILaunch
				#pragma region
				public:

					FORCEINLINE const ELocation& GetLocationType() const
					{
						return *LocationType;
					}

					FORCEINLINE const EDirection& GetDirectionType() const
					{
						return *DirectionType;
					}

				#pragma endregion ILaunch

				public:

					FORCEINLINE void SetLocationType(ELocation* Value)
					{
						LocationType = Value;
					}

					FORCEINLINE void SetDirectionType(EDirection* Value)
					{
						DirectionType = Value;
					}

				// ITrace
				#pragma region
				public:

					FORCEINLINE const ECsTraceType& GetTraceType() const
					{
						return *TraceType;
					}

					FORCEINLINE const ECsTraceMethod& GetTraceMethod() const
					{
						return *TraceMethod;
					}

					FORCEINLINE const ETraceStart& GetTraceStartType() const
					{
						return *TraceStartType;
					}

					FORCEINLINE const ETraceDirection& GetTraceDirectionType() const
					{
						return *TraceDirectionType;
					}

					FORCEINLINE const float& GetTraceDistance() const
					{
						return *TraceDistance;
					}
		
				#pragma endregion ITrace

				public:

					FORCEINLINE void SetTraceType(ECsTraceType* Value)
					{
						TraceType = Value;
					}

					FORCEINLINE void SetTraceMethod(ECsTraceMethod* Value)
					{
						TraceMethod = Value;
					}

					FORCEINLINE void SetTraceStartType(ECsProjectileWeaponLaunchTraceStart* Value)
					{
						TraceStartType = (ETraceStart*)Value;
					}

					FORCEINLINE void SetTraceDirectionType(ETraceDirection* Value)
					{
						TraceDirectionType = Value;
					}

					FORCEINLINE void SetTraceDistance(float* Value)
					{
						TraceDistance = Value;
					}
				};
			}
		}
	}
}