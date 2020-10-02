// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Interfaces
#include "Projectile/Params/Launch/CsParams_ProjectileWeapon_Launch.h"
#include "Projectile/Params/Launch/CsParams_ProjectileWeapon_LaunchTrace.h"

struct FCsInterfaceMap;
enum class ECsProjectileWeaponLaunchLocation : uint8;
enum class ECsProjectileWeaponLaunchDirection : uint8;
enum class ECsProjectileWeaponLaunchTraceStart : uint8;
enum class ECsProjectileWeaponLaunchTraceDirection : uint8;

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

					// ICsGetInterfaceMap

					FCsInterfaceMap* InterfaceMap;

					// ILaunch

					ELocation* LocationType;

					EDirection* DirectionType;

					int32* DirectionRules;

					// ITrace

					ECsTraceType* TraceType;

					ECsTraceMethod* TraceMethod;

					ETraceStart* TraceStartType;

					ETraceDirection* TraceDirectionType;

					float* TraceDistance;

				public:

					FTraceEmu();
					~FTraceEmu();

				// ICsGetInterfaceMap
				#pragma region
				public:

					FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const
					{
						return InterfaceMap;
					}

				#pragma endregion ICsGetInterfaceMap

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

					FORCEINLINE const int32& GetDirectionRules() const 
					{
						return *DirectionRules;
					}

				#pragma endregion ILaunch

				public:

					FORCEINLINE void SetLocationType(ECsProjectileWeaponLaunchLocation* Value)
					{
						LocationType = (ELocation*)Value;
					}

					FORCEINLINE void SetDirectionType(ECsProjectileWeaponLaunchDirection* Value)
					{
						DirectionType = (EDirection*)Value;
					}

					FORCEINLINE void SetDirectionRules(int32* Value)
					{
						DirectionRules = Value;
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

					FORCEINLINE void SetTraceDirectionType(ECsProjectileWeaponLaunchTraceDirection* Value)
					{
						TraceDirectionType = (ETraceDirection*)Value;
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