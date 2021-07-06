// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Projectile/Params/Launch/CsParams_ProjectileWeapon_LaunchTraceImpl.h"

// Types
#include "Projectile/Params/Launch/CsTypes_Params_ProjectileWeapon_LaunchTrace.h"
// Library
#include "Managers/Weapon/CsLibrary_Manager_Weapon.h"
#include "Data/CsLibrary_Data_Weapon.h"
#include "Library/CsLibrary_Property.h"
#include "Library/CsLibrary_Valid.h"
// Data
#include "Projectile/Data/CsData_ProjectileWeaponImplSlice.h"
// Containers
#include "Containers/CsInterfaceMap.h"

const FName NCsWeapon::NProjectile::NParams::NLaunch::NTrace::FImpl::Name = FName("NCsWeapon::NProjectile::NParams::NLaunch::NTrace::FImpl");

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
								const FName DirectionType = FName("DirectionType");
								const FName DirectionRules = FName("DirectionRules");
								const FName TraceType = FName("TraceType");
								const FName TraceMethod = FName("TraceMethod");
								const FName TraceStartType = FName("TraceStartType");
								const FName TraceDirectionType = FName("TraceDirectionType");
								const FName TraceDistance = FName("TraceDistance");
							}
						}
					}

					FImpl::FImpl() :
						// ICsGetInterfaceMap
						InterfaceMap(nullptr),
						// LaunchParamsType (NCsWeapon::NProjectile::NParams::NLaunch::ILaunch)
						LocationType(ELocation::Owner),
						LocationType_Emu(nullptr),
						DirectionType(EDirection::Owner),
						DirectionType_Emu(nullptr),
						DirectionRules(0),
						DirectionRules_Emu(nullptr),
						// LaunchTraceParamsType (NCsWeapon::NProjectile::NParams::NLaunch::NTrace::ITrace)
						TraceType(ECsTraceType::Line),
						TraceType_Emu(nullptr),
						TraceMethod(ECsTraceMethod::Single),
						TraceMethod_Emu(nullptr),
						TraceStartType(ETraceStart::LaunchLocation),
						TraceStartType_Emu(nullptr),
						TraceDirectionType(ETraceDirection::Owner),
						TraceDirectionType_Emu(nullptr),
						TraceDistance(0.0f),
						TraceDistance_Emu(nullptr)
					{
						InterfaceMap = new FCsInterfaceMap();

						InterfaceMap->SetRoot<FImpl>(this);

						typedef NCsWeapon::NProjectile::NParams::NLaunch::ILaunch LaunchParamsType;
						typedef NCsWeapon::NProjectile::NParams::NLaunch::NTrace::ITrace LaunchTraceParamsType;

						InterfaceMap->Add<LaunchParamsType>(static_cast<LaunchParamsType*>(this));
						InterfaceMap->Add<LaunchTraceParamsType>(static_cast<LaunchTraceParamsType*>(this));
					}

					FImpl::~FImpl()
					{
						delete InterfaceMap;
					}

					/*static*/ FImpl* FImpl::AddSafeToSlice(const FString& Context, const UObject* WorldContext, const FName& DataName, UObject* Object, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/)
					{
						using namespace NCsWeapon::NProjectile::NParams::NLaunch::NTrace::NImpl::NCached;

						typedef NCsWeapon::NManager::FLibrary WeaponManagerLibrary;
						typedef NCsWeapon::NData::IData WeaponDataType;

						WeaponDataType* Data = WeaponManagerLibrary::GetSafeData(Context, WorldContext, DataName, Log);

						if (!Data)
							return nullptr;

						typedef NCsWeapon::NData::FLibrary WeaponDataLibrary;
						typedef NCsWeapon::NProjectile::NData::IData PrjWeaponDataType;

						PrjWeaponDataType* PrjWeaponData = WeaponDataLibrary::GetSafeInterfaceChecked<PrjWeaponDataType>(Context, Data);

						if (!PrjWeaponData)
						{
							CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Data: %s does NOT implement the interface: %s."), *Context, *(DataName.ToString()), *(PrjWeaponDataType::Name.ToString())));
							return nullptr;
						}

						typedef NCsWeapon::NProjectile::NData::FImplSlice PrjWeaponDataImplType;

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
						typedef NCsProperty::FLibrary PropertyLibrary;

						bool Success = false;

						// Try FCsProjectileWeaponLaunchTraceParams
						if (FCsProjectileWeaponLaunchTraceParams* SliceAsStruct = PropertyLibrary::GetStructPropertyValuePtr<FCsProjectileWeaponLaunchTraceParams>(Context, Object, Object->GetClass(), Name::LaunchParams, nullptr))
						{
							SliceAsStruct->CopyToParams(Params);
							Success = true;
						}
						// Try individual properties
						else
						{
							#define CS_TEMP_GET_SAFE_ENUM_PTR(__EnumType, __PropertyName) PropertyLibrary::GetEnumPropertyValuePtr<E##__EnumType>(Context, Object, Object->GetClass(), Name::__PropertyName, Str::__EnumType, nullptr)
							#define CS_TEMP_GET_SAFE_INT_PTR(__PropertyName) PropertyLibrary::GetIntPropertyValuePtr(Context, Object, Object->GetClass(), Name::__PropertyName, nullptr)
							#define CS_TEMP_GET_SAFE_FLOAT_PTR(__PropertyName) PropertyLibrary::GetFloatPropertyValuePtr(Context, Object, Object->GetClass(), Name::__PropertyName, nullptr)

							ECsProjectileWeaponLaunchLocation* LocationTypePtr				= CS_TEMP_GET_SAFE_ENUM_PTR(CsProjectileWeaponLaunchLocation, LocationType);
							ECsProjectileWeaponLaunchDirection* DirectionTypePtr			= CS_TEMP_GET_SAFE_ENUM_PTR(CsProjectileWeaponLaunchDirection, DirectionType);
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
								DirectionTypePtr &&
								DirectionRulesPtr &&
								TraceTypePtr &&
								TraceMethodPtr &&
								TraceStartTypePtr &&
								TraceDirectionTypePtr &&
								TraceDistancePtr)
							{
								Params->SetLocationType(LocationTypePtr);
								Params->SetDirectionType(DirectionTypePtr);
								Params->SetDirectionRules(DirectionRulesPtr);
								Params->SetTraceType(TraceTypePtr);
								Params->SetTraceMethod(TraceMethodPtr);
								Params->SetTraceStartType(TraceStartTypePtr);
								Params->SetTraceDirectionType(TraceDirectionTypePtr);
								Params->SetTraceDistance(TraceDistancePtr);
								Success = true;
							}
						}

						if (!Success)
						{
							if (Log)
							{
								Log(FString::Printf(TEXT("%s: Failed to find any properties from Object: %s with Class: %s for launch params implementing interfaces:")));
								Log(FString::Printf(TEXT("%s: - LaunchParamsType(NCsWeapon::NProjectile::NParams::NLaunch::ILaunch)")));
								Log(FString::Printf(TEXT("%s: - LaunchTraceParamsType(NCsWeapon::NProjectile::NParams::NLaunch::NTrace::ITrace)")));
								Log(FString::Printf(TEXT("%s: - Failed to get struct property of type: FCsProjectileWeaponLaunchTraceParams with name: LaunchParams.")));
								Log(FString::Printf(TEXT("%s: - OR")));
								Log(FString::Printf(TEXT("%s: - Failed to get byte property of enum type: ECsProjectileWeaponLaunchLocation with name: LocationType.")));
								Log(FString::Printf(TEXT("%s: - Failed to get byte property of enum type: ECsProjectileWeaponLaunchDirection with name: DirectionType.")));
								Log(FString::Printf(TEXT("%s: - Failed to get int property with name: DirectionRules.")));
								Log(FString::Printf(TEXT("%s: - Failed to get byte property of enum type: ECsTraceType with name: TraceType.")));
								Log(FString::Printf(TEXT("%s: - Failed to get byte property of enum type: ECsTraceMethod with name: TraceMethod.")));
								Log(FString::Printf(TEXT("%s: - Failed to get byte property of enum type: ECsProjectileWeaponLaunchTraceStart with name: TraceStartType.")));
								Log(FString::Printf(TEXT("%s: - Failed to get byte property of enum type: ECsProjectileWeaponLaunchTraceDirection with name: TraceDirectionType.")));
								Log(FString::Printf(TEXT("%s: - Failed to get float property with name: TraceDistance.")));
							}
						}
						return Params;
					}

					bool FImpl::IsValidChecked(const FString& Context) const
					{
						CS_IS_FLOAT_GREATER_THAN_CHECKED(GetTraceDistance(), 0.0f)
						return true;
					}

					bool FImpl::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/) const
					{
						CS_IS_FLOAT_GREATER_THAN(GetTraceDistance(), 0.0f)
						return true;
					}
				}
			}
		}
	}
}