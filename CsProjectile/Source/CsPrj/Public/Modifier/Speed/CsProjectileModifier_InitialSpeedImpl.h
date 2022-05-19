// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Interfaces
#include "Modifier/CsModifier.h"
#include "Modifier/CsProjectileModifier.h"
#include "Modifier/Types/CsGetProjectileModifierType.h"
#include "Valid/CsIsValid.h"
#include "Modifier/Copy/CsProjectileModifier_Copy.h"
#include "Reset/CsReset.h"
// Types
#include "Modifier/CsTypes_Modifier.h"
// Log
#include "Utility/CsPrjLog.h"

class ICsProjectile;

namespace NCsProjectile
{
	namespace NModifier
	{
		namespace NSpeed
		{
			namespace NInitial
			{
			#define ModifierType NCsModifier::IModifier
			#define PrjModifierType NCsProjectile::NModifier::IModifier
			#define CopyType NCsProjectile::NModifier::NCopy::ICopy

				struct CSPRJ_API FImpl : public ModifierType,
										 public PrjModifierType,
										 public ICsGetProjectileModifierType,
										 public ICsIsValid,
										 public CopyType,
										 public ICsReset
				{
				public:

					static const FName Name;

				#define ApplicationType NCsModifier::NValue::NNumeric::EApplication

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

				// PrjModifierType (NCsProjectile::NModifier::IModifier)
				#pragma region
				public:

					void Modify(ICsProjectile* Projectile);

				#pragma endregion PrjModifierType (NCsProjectile::NModifier::IModifier)

				// ICsGetProjectileModifierType
				#pragma region
				public:

					FORCEINLINE const FECsProjectileModifier& GetProjectileModifierType() const { return NCsProjectileModifier::InitialSpeed; }

				#pragma endregion ICsGetProjectileModifierType

				// ICsIsValid
				#pragma region
				public:

					bool IsValidChecked(const FString& Context) const;
					bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning) const;

				#pragma endregion ICsIsValid

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

				#undef ApplicationType
				};

			#undef ModifierType
			#undef PrjModifierType
			#undef CopyType
			}
		}
	}
}