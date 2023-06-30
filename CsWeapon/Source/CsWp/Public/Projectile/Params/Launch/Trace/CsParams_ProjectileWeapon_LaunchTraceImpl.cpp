// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "Projectile/Params/Launch/Trace/CsParams_ProjectileWeapon_LaunchTraceImpl.h"

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
					}

				#define LaunchLocationType NCsWeapon::NProjectile::NParams::NLaunch::ELocation
				#define LaunchLocationOffsetSpace NCsWeapon::NProjectile::NParams::NLaunch::NLocation::EOffsetSpace
				#define LaunchDirectionType NCsWeapon::NProjectile::NParams::NLaunch::EDirection
				#define LaunchTraceStartType NCsWeapon::NProjectile::NParams::NLaunch::NTrace::EStart
				#define LaunchTraceDirectionType NCsWeapon::NProjectile::NParams::NLaunch::NTrace::EDirection

					FImpl::FImpl() :
						// ICsGetInterfaceMap
						InterfaceMap(nullptr),
						// LaunchParamsType (NCsWeapon::NProjectile::NParams::NLaunch::ILaunch)
						LocationParams(),
						DirectionParams(),
						// LaunchTraceParamsType (NCsWeapon::NProjectile::NParams::NLaunch::NTrace::ITrace)
						CS_CTOR_INIT_MEMBER_WITH_PROXY(TraceType, ECsTraceType::Line),
						CS_CTOR_INIT_MEMBER_WITH_PROXY(TraceMethod, ECsTraceMethod::Single),
						CS_CTOR_INIT_MEMBER_WITH_PROXY(TraceStartType, LaunchTraceStartType::LaunchLocation),
						CS_CTOR_INIT_MEMBER_WITH_PROXY(TraceDirectionType, LaunchTraceDirectionType::Owner),
						CS_CTOR_INIT_MEMBER_WITH_PROXY(TraceDistance, 0.0f)
					{
						InterfaceMap = new FCsInterfaceMap();

						InterfaceMap->SetRoot<FImpl>(this);

						typedef NCsWeapon::NProjectile::NParams::NLaunch::ILaunch LaunchParamsType;
						typedef NCsWeapon::NProjectile::NParams::NLaunch::NTrace::ITrace LaunchTraceParamsType;

						InterfaceMap->Add<LaunchParamsType>(static_cast<LaunchParamsType*>(this));
						InterfaceMap->Add<LaunchTraceParamsType>(static_cast<LaunchTraceParamsType*>(this));

						// LaunchParamsType (NCsWeapon::NProjectile::NParams::NLaunch::ILaunch)
						// LaunchTraceParamsType (NCsWeapon::NProjectile::NParams::NLaunch::NTrace::ITrace)
						CS_CTOR_SET_MEMBER_PROXY(TraceType);
						CS_CTOR_SET_MEMBER_PROXY(TraceMethod);
						CS_CTOR_SET_MEMBER_PROXY(TraceStartType);
						CS_CTOR_SET_MEMBER_PROXY(TraceDirectionType);
						CS_CTOR_SET_MEMBER_PROXY(TraceDistance);
					}

				#undef LaunchLocationType
				#undef LaunchLocationOffsetSpace
				#undef LaunchDirectionType
				#undef LaunchTraceStartType
				#undef LaunchTraceDirectionType

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

						// Try FCsProjectileWeapon_LaunchTraceParams
						if (FCsProjectileWeapon_LaunchTraceParams* SliceAsStruct = PropertyLibrary::GetStructPropertyValuePtr<FCsProjectileWeapon_LaunchTraceParams>(Context, Object, Object->GetClass(), Name::LaunchParams, nullptr))
						{
							SliceAsStruct->CopyToParams(Params);
							Success = true;
						}
						// Try individual properties
						else
						{
							#define CS_TEMP_GET_SAFE_ENUM_PTR(__EnumType, __PropertyName) PropertyLibrary::GetEnumPropertyValuePtr<E##__EnumType>(Context, Object, Object->GetClass(), Name::__PropertyName, Str::__EnumType, nullptr)
							#define CS_TEMP_GET_SAFE_BOOL_PTR(__PropertyName) PropertyLibrary::GetBoolPropertyValuePtr(Context, Object, Object->GetClass(), Name::__PropertyName, nullptr)
							#define CS_TEMP_GET_SAFE_INT_PTR(__PropertyName) PropertyLibrary::GetIntPropertyValuePtr(Context, Object, Object->GetClass(), Name::__PropertyName, nullptr)
							#define CS_TEMP_GET_SAFE_FLOAT_PTR(__PropertyName) PropertyLibrary::GetFloatPropertyValuePtr(Context, Object, Object->GetClass(), Name::__PropertyName, nullptr)

							ECsProjectileWeaponLaunchLocation* LocationTypePtr				= CS_TEMP_GET_SAFE_ENUM_PTR(CsProjectileWeaponLaunchLocation, LocationType);
							// NOTE: This may need to fixed. FVector might not be treated as a Struct Property
							//FVector* LocationOffsetPtr									= PropertyLibrary::GetStructPropertyValuePtr<FVector>(Context, Object, Object->GetClass(), Name::LocationOffset, nullptr);
							ECsProjectileWeaponLaunchDirection* DirectionTypePtr			= CS_TEMP_GET_SAFE_ENUM_PTR(CsProjectileWeaponLaunchDirection, DirectionType);
							// NOTE: This may need to fixed. FRotator might not be treated as a Struct Property
							//FRotator* DirectionOffsetPtr									= PropertyLibrary::GetStructPropertyValuePtr<FRotator>(Context, Object, Object->GetClass(), Name::DirectionOffset, nullptr);
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
								Params->SetTraceType(TraceTypePtr);
								Params->SetTraceMethod(TraceMethodPtr);
								Params->SetTraceStartType((LaunchTraceStartType*)TraceStartTypePtr);
								Params->SetTraceDirectionType((LaunchTraceDirectionType*)TraceDirectionTypePtr);
								Params->SetTraceDistance(TraceDistancePtr);
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
								//Log(FString::Printf(TEXT("%s: - Failed to get struct property of type: FVector with name: LocationOffset."), *Context));
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

						typedef NCsWeapon::NProjectile::NParams::NLaunch::NTrace::EMStart LaunchTraceStartMapType;
						typedef NCsWeapon::NProjectile::NParams::NLaunch::NTrace::EMDirection LaunchTraceDirectionMapType;

						CS_IS_ENUM_VALID_CHECKED(LaunchTraceStartMapType, GetTraceStartType())
						CS_IS_ENUM_VALID_CHECKED(LaunchTraceDirectionMapType, GetTraceDirectionType())
						CS_IS_FLOAT_GREATER_THAN_CHECKED(GetTraceDistance(), 0.0f)
						return true;
					}

					bool FImpl::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/) const
					{
						CS_IS_VALID(GetLocationParams())
						CS_IS_VALID(GetDirectionParams())

						typedef NCsWeapon::NProjectile::NParams::NLaunch::NTrace::EMStart LaunchTraceStartMapType;
						typedef NCsWeapon::NProjectile::NParams::NLaunch::NTrace::EStart LaunchTraceStartType;
						typedef NCsWeapon::NProjectile::NParams::NLaunch::NTrace::EMDirection LaunchTraceDirectionMapType;
						typedef NCsWeapon::NProjectile::NParams::NLaunch::NTrace::EDirection LaunchTraceDirectionType;

						CS_IS_ENUM_VALID(LaunchTraceStartMapType, LaunchTraceStartType, GetTraceStartType())
						CS_IS_ENUM_VALID(LaunchTraceDirectionMapType, LaunchTraceDirectionType, GetTraceDirectionType())
						CS_IS_FLOAT_GREATER_THAN(GetTraceDistance(), 0.0f)
						return true;
					}
				}
			}
		}
	}
}