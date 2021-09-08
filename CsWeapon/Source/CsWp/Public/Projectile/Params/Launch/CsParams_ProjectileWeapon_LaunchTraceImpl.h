// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Interfaces
#include "Projectile/Params/Launch/CsParams_ProjectileWeapon_Launch.h"
#include "Projectile/Params/Launch/CsParams_ProjectileWeapon_LaunchTrace.h"
// Types
#include "Types/CsTypes_Macro.h"
// Log
#include "Utility/CsWpLog.h"

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
				namespace NTrace
				{
				#define LaunchParamsType NCsWeapon::NProjectile::NParams::NLaunch::ILaunch
				#define LaunchTraceParamsType NCsWeapon::NProjectile::NParams::NLaunch::NTrace::ITrace

					/**
					*/
					struct CSWP_API FImpl : public LaunchParamsType,
											public LaunchTraceParamsType
					{
					public:

						static const FName Name;

					private:

						// ICsGetInterfaceMap

						FCsInterfaceMap* InterfaceMap;

						// LaunchParamsType (NCsWeapon::NProjectile::NParams::NLaunch::ILaunch)

						CS_DECLARE_MEMBER_WITH_PROXY(LocationType, ELocation)
						CS_DECLARE_MEMBER_WITH_PROXY(DirectionType, EDirection)
						CS_DECLARE_MEMBER_WITH_PROXY(DirectionRules, int32)

						// LaunchTraceParamsType (NCsWeapon::NProjectile::NParams::NLaunch::NTrace::ITrace)

						CS_DECLARE_MEMBER_WITH_PROXY(TraceType, ECsTraceType)
						CS_DECLARE_MEMBER_WITH_PROXY(TraceMethod, ECsTraceMethod)
						CS_DECLARE_MEMBER_WITH_PROXY(TraceStartType, ETraceStart)
						CS_DECLARE_MEMBER_WITH_PROXY(TraceDirectionType, ETraceDirection)
						CS_DECLARE_MEMBER_WITH_PROXY(TraceDistance, float)

					public:

						FImpl();
						~FImpl();

					// ICsGetInterfaceMap
					#pragma region
					public:

						FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const { return InterfaceMap; }

					#pragma endregion ICsGetInterfaceMap

					public:

						FORCEINLINE void SetLocationType(const ECsProjectileWeaponLaunchLocation& Value) 
						{ 
							LocationType = (ELocation)Value;
							LocationType_Proxy = &LocationType;

						}
						FORCEINLINE void SetLocationType(ECsProjectileWeaponLaunchLocation* Value) { LocationType_Proxy = (ELocation*)Value; }

						FORCEINLINE void SetDirectionType(const ECsProjectileWeaponLaunchDirection& Value) 
						{ 
							DirectionType = (EDirection)Value;
							DirectionType_Proxy = &DirectionType;
						}
						FORCEINLINE void SetDirectionType(ECsProjectileWeaponLaunchDirection* Value) { DirectionType_Proxy = (EDirection*)Value; }

					// LaunchParamsType (NCsWeapon::NProjectile::NParams::NLaunch::ILaunch)
					#pragma region
					public:

						CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(LocationType, ELocation)
						CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(DirectionType, EDirection)
						CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(DirectionRules, int32)

					#pragma endregion LaunchParamsType (NCsWeapon::NProjectile::NParams::NLaunch::ILaunch)

					public:

						FORCEINLINE void SetTraceStartType(const ECsProjectileWeaponLaunchTraceStart& Value)
						{
							TraceStartType = (ETraceStart)Value;
							TraceStartType_Proxy = &TraceStartType;
						}
						FORCEINLINE void SetTraceStartType(ECsProjectileWeaponLaunchTraceStart* Value) { TraceStartType_Proxy = (ETraceStart*)Value; }
						
						FORCEINLINE void SetTraceDirectionType(const ECsProjectileWeaponLaunchTraceDirection& Value) 
						{ 
							TraceDirectionType = (ETraceDirection)Value;
							TraceDirectionType_Proxy = &TraceDirectionType;
						}
						FORCEINLINE void SetTraceDirectionType(ECsProjectileWeaponLaunchTraceDirection* Value) { TraceDirectionType_Proxy = (ETraceDirection*)Value; }

					// LaunchTraceParamsType (NCsWeapon::NProjectile::NParams::NLaunch::NTrace::ITrace)
					#pragma region
					public:

						CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(TraceType, ECsTraceType)
						CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(TraceMethod, ECsTraceMethod)
						CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(TraceStartType, ETraceStart)
						CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(TraceDirectionType, ETraceDirection)
						CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(TraceDistance, float)
		
					#pragma endregion LaunchTraceParamsType (NCsWeapon::NProjectile::NParams::NLaunch::NTrace::ITrace)
					
					public:

						static FImpl* AddSafeToSlice(const FString& Context, const UObject* WorldContext, const FName& DataName, UObject* Object, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning);

						bool IsValidChecked(const FString& Context) const;
						bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning) const;
					};

				#undef LaunchParamsType
				#undef LaunchTraceParamsType
				}
			}
		}
	}
}