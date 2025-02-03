// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
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
					namespace NImpl
					{
						using LaunchParamsType = NCsWeapon::NProjectile::NParams::NLaunch::ILaunch;
						using LaunchTraceParamsType = NCsWeapon::NProjectile::NParams::NLaunch::NTrace::ITrace;

						/**
						*/
						struct CSWP_API FImpl : public LaunchParamsType,
												public LaunchTraceParamsType
						{
						public:

							static const FName Name;

						private:

							using LocationParamsType = NCsWeapon::NProjectile::NParams::NLaunch::NLocation::FParams;
							using DirectionParamsType = NCsWeapon::NProjectile::NParams::NLaunch::NDirection::FParams;
							using TraceParamsType = NCsWeapon::NProjectile::NParams::NLaunch::NTrace::FParams;
							using LaunchLocationType = NCsWeapon::NProjectile::NParams::NLaunch::ELocation;
							using LaunchLocationOffsetSpace = NCsWeapon::NProjectile::NParams::NLaunch::NLocation::EOffsetSpace;
							using LaunchDirectionType = NCsWeapon::NProjectile::NParams::NLaunch::EDirection;
							using LaunchTraceStartType = NCsWeapon::NProjectile::NParams::NLaunch::NTrace::EStart;
							using LaunchTraceDirectionType = NCsWeapon::NProjectile::NParams::NLaunch::NTrace::EDirection;

						// ICsGetInterfaceMap

							FCsInterfaceMap* InterfaceMap;

						// LaunchParamsType (NCsWeapon::NProjectile::NParams::NLaunch::ILaunch)

							LocationParamsType LocationParams;
							DirectionParamsType DirectionParams;

						// LaunchTraceParamsType (NCsWeapon::NProjectile::NParams::NLaunch::NTrace::ITrace)

							TraceParamsType TraceParams;

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
					
						public:

							FORCEINLINE const TraceParamsType& GetTraceParams() const { return TraceParams; }
							FORCEINLINE TraceParamsType* GetTraceParamsPtr() { return &TraceParams; }

						// LaunchTraceParamsType (NCsWeapon::NProjectile::NParams::NLaunch::NTrace::ITrace)
						#pragma region
						public:

							FORCEINLINE const ECsTraceType& GetTraceType() const { return GetTraceParams().GetType(); }
							FORCEINLINE const ECsTraceMethod& GetTraceMethod() const { return GetTraceParams().GetMethod(); }
							FORCEINLINE const LaunchTraceStartType& GetTraceStartType() const { return GetTraceParams().GetStart(); }
							FORCEINLINE const LaunchTraceDirectionType& GetTraceDirectionType() const { return GetTraceParams().GetDirection(); }
							FORCEINLINE const float& GetTraceDistance() const { return GetTraceParams().GetDistance(); }
		
						#pragma endregion LaunchTraceParamsType (NCsWeapon::NProjectile::NParams::NLaunch::NTrace::ITrace)
					
						public:

							static FImpl* AddSafeToSlice(const FString& Context, const UObject* WorldContext, const FName& DataName, UObject* Object, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning);

							bool IsValidChecked(const FString& Context) const;
							bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning) const;
						};
					}
				}
			}
		}
	}
}