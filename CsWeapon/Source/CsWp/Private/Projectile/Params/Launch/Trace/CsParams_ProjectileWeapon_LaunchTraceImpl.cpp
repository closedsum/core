// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "Projectile/Params/Launch/Trace/CsParams_ProjectileWeapon_LaunchTraceImpl.h"

// Types
#include "CsMacro_Misc.h"
#include "CsMacro_Interface.h"
// Library
#include "Managers/Weapon/CsLibrary_Manager_Weapon.h"
	// Data
#include "Data/CsLibrary_Data_Weapon.h"
	// Common
#include "Library/CsLibrary_Property.h"
#include "Library/CsLibrary_Valid.h"
// Containers
#include "Containers/CsInterfaceMap.h"
// Data
#include "Projectile/Data/CsData_ProjectileWeaponImplSlice.h"

CS_STRUCT_DEFINE_STATIC_CONST_FNAME(NCsWeapon::NProjectile::NParams::NLaunch::NTrace::NImpl::FImpl);

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
						namespace NCached
						{
							namespace Str
							{
								const FString CsProjectileWeaponLaunchLocation = TEXT("ECsProjectileWeaponLaunchLocation");
								const FString CsProjectileWeaponLaunchDirection = TEXT("ECsProjectileWeaponLaunchDirection");
								const FString CsTraceType = TEXT("ECsTraceType");
								const FString CsTraceMethod = TEXT("ECsTraceMethod");
								const FString CsProjectileWeaponLaunchTraceStart = TEXT("ECsProjectileWeaponLaunchTraceStart");
								const FString CsProjectileWeaponLaunchTraceDirection = TEXT("ECsProjectileWeaponLaunchTraceDirection");
							}

							namespace Name
							{
								const FName LaunchParams = FName("LaunchParams");

								const FName LocationType = FName("LocationType");
								const FName LocationOffset = FName("LocationOffset");
								const FName DirectionType = FName("DirectionType");
								const FName DirectionOffset = FName("DirectionOffset");
								const FName bInvertDirection = FName("bInvertDirection");
								const FName DirectionRules = FName("DirectionRules");
								const FName TraceType = FName("TraceType");
								const FName TraceMethod = FName("TraceMethod");
								const FName TraceStartType = FName("TraceStartType");
								const FName TraceDirectionType = FName("TraceDirectionType");
								const FName TraceDistance = FName("TraceDistance");
							}
						}

						FImpl::FImpl() :
							// ICsGetInterfaceMap
							InterfaceMap(nullptr),
							// LaunchParamsType (NCsWeapon::NProjectile::NParams::NLaunch::ILaunch)
							LocationParams(),
							DirectionParams(),
							// LaunchTraceParamsType (NCsWeapon::NProjectile::NParams::NLaunch::NTrace::ITrace)
							TraceParams()
						{
							InterfaceMap = new FCsInterfaceMap();

							CS_INTERFACE_MAP_SET_ROOT(FImpl);

							CS_INTERFACE_MAP_ADD(LaunchParamsType);
							CS_INTERFACE_MAP_ADD(LaunchTraceParamsType);
						}

						FImpl::~FImpl()
						{
							delete InterfaceMap;
						}

						using PrjWeaponDataType = NCsWeapon::NProjectile::NData::IData;
						using PrjWeaponDataImplType = NCsWeapon::NProjectile::NData::FImplSlice;

						/*static*/ FImpl* FImpl::AddSafeToSlice(const FString& Context, const UObject* WorldContext, const FName& DataName, UObject* Object, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/)
						{
							using namespace NCsWeapon::NProjectile::NParams::NLaunch::NTrace::NImpl::NCached;

							CsWeaponDataType* Data = CsWeaponManagerLibrary::GetSafeData(Context, WorldContext, DataName, Log);

							if (!Data)
								return nullptr;

							PrjWeaponDataType* PrjWeaponData = CsWeaponDataLibrary::GetSafeInterfaceChecked<PrjWeaponDataType>(Context, Data);

							if (!PrjWeaponData)
							{
								CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Data: %s does NOT implement the interface: %s."), *Context, *(DataName.ToString()), *(PrjWeaponDataType::Name.ToString())));
								return nullptr;
							}

							PrjWeaponDataImplType* PrjWeaponDataImpl = NCsInterfaceMap::SafeStaticCastChecked<PrjWeaponDataImplType, PrjWeaponDataType>(Context, PrjWeaponData);

							if (!PrjWeaponDataImpl)
							{
								CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Data: %s does NOT contain the slice: %s."), *Context, *(DataName.ToString()), *(PrjWeaponDataImplType::Name.ToString())));
								return nullptr;
							}

							FImpl* Params = PrjWeaponDataImpl->ConstructLaunchParams<FImpl>();

							// Check for properties matching interfaces:
							//  LaunchParamsType (NCsWeapon::NProjectile::NParams::NLaunch::ILaunch)
							//  LaunchTraceParamsType (NCsWeapon::NProjectile::NParams::NLaunch::NTrace::ITrace)
							bool Success = false;

							// Try FCsProjectileWeapon_LaunchTraceParams
							if (FCsProjectileWeapon_LaunchTraceParams* SliceAsStruct = CsPropertyLibrary::GetStructPropertyValuePtr<FCsProjectileWeapon_LaunchTraceParams>(Context, Object, Object->GetClass(), Name::LaunchParams, nullptr))
							{
								SliceAsStruct->CopyToParams(Params);
								Success = true;
							}
							// Try individual properties
							else
							{
								#define CS_TEMP_GET_SAFE_ENUM_PTR(__EnumType, __PropertyName) CsPropertyLibrary::GetEnumPropertyValuePtr<E##__EnumType>(Context, Object, Object->GetClass(), Name::__PropertyName, Str::__EnumType, nullptr)
								#define CS_TEMP_GET_SAFE_BOOL_PTR(__PropertyName) CsPropertyLibrary::GetBoolPropertyValuePtr(Context, Object, Object->GetClass(), Name::__PropertyName, nullptr)
								#define CS_TEMP_GET_SAFE_INT_PTR(__PropertyName) CsPropertyLibrary::GetIntPropertyValuePtr(Context, Object, Object->GetClass(), Name::__PropertyName, nullptr)
								#define CS_TEMP_GET_SAFE_FLOAT_PTR(__PropertyName) CsPropertyLibrary::GetFloatPropertyValuePtr(Context, Object, Object->GetClass(), Name::__PropertyName, nullptr)

								ECsProjectileWeaponLaunchLocation* LocationTypePtr				= CS_TEMP_GET_SAFE_ENUM_PTR(CsProjectileWeaponLaunchLocation, LocationType);
								// NOTE: This may need to fixed. FVector3f might not be treated as a Struct Property
								//FVector* LocationOffsetPtr									= CsPropertyLibrary::GetStructPropertyValuePtr<FVector3f>(Context, Object, Object->GetClass(), Name::LocationOffset, nullptr);
								ECsProjectileWeaponLaunchDirection* DirectionTypePtr			= CS_TEMP_GET_SAFE_ENUM_PTR(CsProjectileWeaponLaunchDirection, DirectionType);
								// NOTE: This may need to fixed. FRotator might not be treated as a Struct Property
								//FRotator* DirectionOffsetPtr									= CsPropertyLibrary::GetStructPropertyValuePtr<FRotator>(Context, Object, Object->GetClass(), Name::DirectionOffset, nullptr);
								bool* bInvertDirectionPtr										= CS_TEMP_GET_SAFE_BOOL_PTR(bInvertDirection);
								int32* DirectionRulesPtr										= CS_TEMP_GET_SAFE_INT_PTR(DirectionRules);
								ECsTraceType* TraceTypePtr										= CS_TEMP_GET_SAFE_ENUM_PTR(CsTraceType, TraceType);
								ECsTraceMethod* TraceMethodPtr									= CS_TEMP_GET_SAFE_ENUM_PTR(CsTraceMethod, TraceMethod);
								ECsProjectileWeaponLaunchTraceStart* TraceStartTypePtr			= CS_TEMP_GET_SAFE_ENUM_PTR(CsProjectileWeaponLaunchTraceStart, TraceStartType);
								ECsProjectileWeaponLaunchTraceDirection* TraceDirectionTypePtr	= CS_TEMP_GET_SAFE_ENUM_PTR(CsProjectileWeaponLaunchTraceDirection, TraceDirectionType);
								float* TraceDistancePtr											= CS_TEMP_GET_SAFE_FLOAT_PTR(TraceDistance);

								#undef CS_TEMP_GET_SAFE_ENUM_PTR
								#undef CS_TEMP_GET_SAFE_INT_PTR
								#undef CS_TEMP_GET_SAFE_FLOAT_PTR

								if (LocationTypePtr &&
									//LocationOffsetPtr &&
									DirectionTypePtr &&
									//DirectionOffsetPtr &&
									bInvertDirectionPtr &&
									DirectionRulesPtr &&
									TraceTypePtr &&
									TraceMethodPtr &&
									TraceStartTypePtr &&
									TraceDirectionTypePtr &&
									TraceDistancePtr)
								{
									typedef NCsWeapon::NProjectile::NParams::NLaunch::ELocation LaunchLocationType;
									typedef NCsWeapon::NProjectile::NParams::NLaunch::NLocation::EOffsetSpace LaunchLocationOffsetSpace;
									typedef NCsWeapon::NProjectile::NParams::NLaunch::EDirection LaunchDirectionType;
									typedef NCsWeapon::NProjectile::NParams::NLaunch::NTrace::EStart LaunchTraceStartType;
									typedef NCsWeapon::NProjectile::NParams::NLaunch::NTrace::EDirection LaunchTraceDirectionType;

									Params->GetLocationParamsPtr()->SetType((LaunchLocationType*)LocationTypePtr);
									//Params->SetLocationOffset(LocationOffsetPtr);
									Params->GetDirectionParamsPtr()->SetType((LaunchDirectionType*)DirectionTypePtr);
									Params->GetDirectionParamsPtr()->SetbInvert(bInvertDirectionPtr);
									Params->GetDirectionParamsPtr()->SetRules(DirectionRulesPtr);
									Params->GetTraceParamsPtr()->SetType(TraceTypePtr);
									Params->GetTraceParamsPtr()->SetMethod(TraceMethodPtr);
									Params->GetTraceParamsPtr()->SetStart((LaunchTraceStartType*)TraceStartTypePtr);
									Params->GetTraceParamsPtr()->SetDirection((LaunchTraceDirectionType*)TraceDirectionTypePtr);
									Params->GetTraceParamsPtr()->SetDistance(TraceDistancePtr);
									Success = true;
								}
							}

							if (!Success)
							{
								if (Log)
								{
									Log(FString::Printf(TEXT("%s: Failed to find any properties from Object: %s with Class: %s for launch params implementing interfaces:"), *Context));
									Log(FString::Printf(TEXT("%s: - LaunchParamsType(NCsWeapon::NProjectile::NParams::NLaunch::ILaunch)"), *Context));
									Log(FString::Printf(TEXT("%s: - LaunchTraceParamsType(NCsWeapon::NProjectile::NParams::NLaunch::NTrace::ITrace)"), *Context));
									Log(FString::Printf(TEXT("%s: - Failed to get struct property of type: FCsProjectileWeapon_LaunchTraceParams with name: LaunchParams."), *Context));
									Log(FString::Printf(TEXT("%s: - OR"), *Context));
									Log(FString::Printf(TEXT("%s: - Failed to get byte property of enum type: ECsProjectileWeaponLaunchLocation with name: LocationType."), *Context));
									//Log(FString::Printf(TEXT("%s: - Failed to get struct property of type: FVector3f with name: LocationOffset."), *Context));
									Log(FString::Printf(TEXT("%s: - Failed to get byte property of enum type: ECsProjectileWeaponLaunchDirection with name: DirectionType."), *Context));
									//Log(FString::Printf(TEXT("%s: - Failed to get struct property of type: FRotator with name: DirectionOffset."), *Context));
									Log(FString::Printf(TEXT("%s: - Failed to get bool property with name: bInvertDirection."), *Context));
									Log(FString::Printf(TEXT("%s: - Failed to get int property with name: DirectionRules."), *Context));
									Log(FString::Printf(TEXT("%s: - Failed to get byte property of enum type: ECsTraceType with name: TraceType."), *Context));
									Log(FString::Printf(TEXT("%s: - Failed to get byte property of enum type: ECsTraceMethod with name: TraceMethod."), *Context));
									Log(FString::Printf(TEXT("%s: - Failed to get byte property of enum type: ECsProjectileWeaponLaunchTraceStart with name: TraceStartType."), *Context));
									Log(FString::Printf(TEXT("%s: - Failed to get byte property of enum type: ECsProjectileWeaponLaunchTraceDirection with name: TraceDirectionType."), *Context));
									Log(FString::Printf(TEXT("%s: - Failed to get float property with name: TraceDistance."), *Context));
								}
							}
							return Params;
						}

						bool FImpl::IsValidChecked(const FString& Context) const
						{
							CS_IS_VALID_CHECKED(GetLocationParams());
							CS_IS_VALID_CHECKED(GetDirectionParams());
							CS_IS_VALID_CHECKED(GetTraceParams());
							return true;
						}

						bool FImpl::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/) const
						{
							CS_IS_VALID(GetLocationParams())
							CS_IS_VALID(GetDirectionParams())
							CS_IS_VALID(GetTraceParams())
							return true;
						}
					}
				}
			}
		}
	}
}