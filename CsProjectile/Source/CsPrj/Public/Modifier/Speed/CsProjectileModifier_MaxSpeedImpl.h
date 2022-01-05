// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Interfaces
#include "Modifier/CsModifier.h"
#include "Modifier/CsProjectileModifier.h"
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
			namespace NMax
			{
			#define ModifierType NCsModifier::IModifier
			#define PrjModifierType NCsProjectile::NModifier::IModifier

				struct CSPRJ_API FImpl : public ModifierType,
										 public PrjModifierType,
										 public ICsReset
				{
				public:

					static const FName Name;

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

				// PrjModifierType (NCsProjectile::NModifier::IModifier)
				#pragma region
				public:

					void Modify(ICsProjectile* Projectile);

				#pragma endregion PrjModifierType (NCsProjectile::NModifier::IModifier)

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

					void CopyTo(FImpl* To) const;

					bool IsValidChecked(const FString& Context) const;
					bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning) const;

				#undef ApplicationType
				};

			#undef ModifierType
			#undef PrjModifierType
			}
		}
	}
}