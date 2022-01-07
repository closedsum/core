// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Interfaces
#include "Modifier/CsModifier.h"
#include "Managers/Damage/Modifier/CsDamageModifier.h"
#include "Managers/Damage/Modifier/Value/CsDamageModifier_Value.h"
#include "Managers/Damage/Modifier/Value/Point/CsDamageModifier_ValuePoint.h"
#include "Modifier/CsProjectileModifier.h"
#include "Modifier/Types/CsGetProjectileModifierType.h"
#include "Modifier/Copy/CsProjectileModifier_Copy.h"
#include "Reset/CsReset.h"
// Types
#include "Modifier/CsTypes_Modifier.h"
// Log
#include "Utility/CsPrjLog.h"

class ICsProjectile;

// NCsDamage::NValue::IValue
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsDamage, NValue, IValue)

namespace NCsProjectile
{
	namespace NModifier
	{
		namespace NDamage
		{
			namespace NValue
			{
				namespace NPoint
				{
				#define ModifierType NCsModifier::IModifier
				#define DmgModifierType NCsDamage::NModifier::IModifier
				#define DmgValueModifierType NCsDamage::NModifier::NValue::IValue
				#define DmgValuePointModifierType NCsDamage::NModifier::NValue::NPoint::IPoint
				#define PrjModifierType NCsProjectile::NModifier::IModifier
				#define CopyType NCsProjectile::NModifier::NCopy::ICopy

					struct CSPRJ_API FImpl : public ModifierType,
											 public DmgModifierType,
											 public DmgValueModifierType,
											 public DmgValuePointModifierType,
											 public PrjModifierType,
											 public ICsGetProjectileModifierType,
											 public CopyType,
											 public ICsReset
					{
					public:

						static const FName Name;

					#define ValueType NCsDamage::NValue::IValue
					#define ApplicationType NCsModifier::NValue::NIntegral::EApplication

					private:

						// ICsGetInterfaceMap

						FCsInterfaceMap* InterfaceMap;

					public:

						CS_DECLARE_MEMBER_WITH_PROXY(Value, float)
						CS_DECLARE_MEMBER_WITH_PROXY(Application, ApplicationType)

					public:
						
						FImpl();
						~FImpl();

						FORCEINLINE UObject* _getUObject() const { return nullptr; }

					// ICsGetInterfaceMap
					#pragma region
					public:

						FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const { return InterfaceMap; }

					#pragma endregion ICsGetInterfaceMap

					// PrjModifierType
					#pragma region
					public:

						void Modify(ICsProjectile* Projectile){}

					#pragma endregion PrjModifierType

					// DmgValueModifierType (NCsDamage::NModifier::NValue::IValue)
					#pragma region
					public:

						void Modify(ValueType* InValue) const;

					#pragma endregion DmgValueModifierType (NCsDamage::NModifier::NValue::IValue)

					// ICsGetProjectileModifierType
					#pragma region
					public:

						FORCEINLINE const FECsProjectileModifier& GetProjectileModifierType() const { return NCsProjectileModifier::DamageValuePoint; }

					#pragma endregion ICsGetProjectileModifierType

					// CopyType (NCsProjectile::NModifier::NCopy::ICopy)
					#pragma region
					public:

						void Copy(const PrjModifierType* From);

					#pragma endregion CopyType (NCsProjectile::NModifier::NCopy::ICopy)

					// ICsReset
					#pragma region
					public:

						FORCEINLINE void Reset()
						{
							CS_RESET_MEMBER_WITH_PROXY(Value, 0.0)
							CS_RESET_MEMBER_WITH_PROXY(Application, ApplicationType::EApplication_MAX)
						}

					#pragma endregion ICsReset

					public:

						CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Value, float)
						CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Application, ApplicationType)

						bool IsValidChecked(const FString& Context) const;
						bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning) const;

					#undef ValueType
					#undef ApplicationType
					};
				
				#undef ModifierType
				#undef DmgModifierType
				#undef DmgValueModifierType
				#undef DmgValuePointModifierType
				#undef PrjModifierType
				#undef CopyType
				}
			}
		}
	}
}