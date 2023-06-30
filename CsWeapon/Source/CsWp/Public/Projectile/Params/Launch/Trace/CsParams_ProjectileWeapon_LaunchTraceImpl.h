// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Interfaces
#include "Projectile/Params/Launch/CsParams_ProjectileWeapon_Launch.h"
#include "Projectile/Params/Launch/Trace/CsParams_ProjectileWeapon_LaunchTrace.h"
// Log
#include "Utility/CsWpLog.h"

struct FCsInterfaceMap;

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

					#define LocationParamsType NCsWeapon::NProjectile::NParams::NLaunch::NLocation::FParams
					#define DirectionParamsType NCsWeapon::NProjectile::NParams::NLaunch::NDirection::FParams
					#define LaunchLocationType NCsWeapon::NProjectile::NParams::NLaunch::ELocation
					#define LaunchLocationOffsetSpace NCsWeapon::NProjectile::NParams::NLaunch::NLocation::EOffsetSpace
					#define LaunchDirectionType NCsWeapon::NProjectile::NParams::NLaunch::EDirection
					#define LaunchTraceStartType NCsWeapon::NProjectile::NParams::NLaunch::NTrace::EStart
					#define LaunchTraceDirectionType NCsWeapon::NProjectile::NParams::NLaunch::NTrace::EDirection

					// ICsGetInterfaceMap

						FCsInterfaceMap* InterfaceMap;

					// LaunchParamsType (NCsWeapon::NProjectile::NParams::NLaunch::ILaunch)

						LocationParamsType LocationParams;
						DirectionParamsType DirectionParams;

					// LaunchTraceParamsType (NCsWeapon::NProjectile::NParams::NLaunch::NTrace::ITrace)

						CS_DECLARE_MEMBER_WITH_PROXY(TraceType, ECsTraceType)
						CS_DECLARE_MEMBER_WITH_PROXY(TraceMethod, ECsTraceMethod)
						CS_DECLARE_MEMBER_WITH_PROXY(TraceStartType, LaunchTraceStartType)
						CS_DECLARE_MEMBER_WITH_PROXY(TraceDirectionType, LaunchTraceDirectionType)
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

						FORCEINLINE const LocationParamsType& GetLocationParams() const { return LocationParams; }
						FORCEINLINE LocationParamsType* GetLocationParamsPtr() { return &LocationParams; }
						FORCEINLINE const DirectionParamsType& GetDirectionParams() const { return DirectionParams; }
						FORCEINLINE DirectionParamsType* GetDirectionParamsPtr() { return &DirectionParams; }

					// LaunchParamsType (NCsWeapon::NProjectile::NParams::NLaunch::ILaunch)
					#pragma region
					public:

						FORCEINLINE const LaunchLocationType& GetLocationType() const { return GetLocationParams().GetType(); }
						FORCEINLINE const LaunchLocationOffsetSpace& GetLocationOffsetSpace() const { return GetLocationParams().GetOffsetSpace(); }
						FORCEINLINE const int32& GetLocationOffsetSpaceRules() const { return GetLocationParams().GetOffsetSpaceRules(); }
						FORCEINLINE const FRotator& GetLocationOffsetSpaceOffset() const { return GetLocationParams().GetOffsetSpaceOffset(); }
						FORCEINLINE const FVector& GetLocationOffset() const { return GetLocationParams().GetOffset(); }
						FORCEINLINE const LaunchDirectionType& GetDirectionType() const { return GetDirectionParams().GetType(); }
						FORCEINLINE const FRotator& GetDirectionOffset() const { return GetDirectionParams().GetOffset(); }
						FORCEINLINE const bool& InvertDirection() const { return GetDirectionParams().GetbInvert(); }
						FORCEINLINE const int32& GetDirectionRules() const { return GetDirectionParams().GetRules(); }

					#pragma endregion LaunchParamsType (NCsWeapon::NProjectile::NParams::NLaunch::ILaunch)

					// LaunchTraceParamsType (NCsWeapon::NProjectile::NParams::NLaunch::NTrace::ITrace)
					#pragma region
					public:

						CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(TraceType, ECsTraceType)
						CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(TraceMethod, ECsTraceMethod)
						CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(TraceStartType, LaunchTraceStartType)
						CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(TraceDirectionType, LaunchTraceDirectionType)
						CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(TraceDistance, float)
		
					#pragma endregion LaunchTraceParamsType (NCsWeapon::NProjectile::NParams::NLaunch::NTrace::ITrace)
					
					public:

						static FImpl* AddSafeToSlice(const FString& Context, const UObject* WorldContext, const FName& DataName, UObject* Object, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning);

						bool IsValidChecked(const FString& Context) const;
						bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning) const;

					#undef LocationParamsType
					#undef DirectionParamsType
					#undef LaunchLocationType
					#undef LaunchLocationOffsetSpace
					#undef LaunchDirectionType
					#undef LaunchTraceStartType
					#undef LaunchTraceDirectionType
					};

				#undef LaunchParamsType
				#undef LaunchTraceParamsType
				}
			}
		}
	}
}