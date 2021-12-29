// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Payload/Modifier/CsPayload_Projectile_Modifier.h"
#include "Reset/CsReset.h"

class UObject;
struct FCsInterfaceMap;

// NCsDamage::NModifier::IModifier
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsDamage, NModifier, IModifier)

namespace NCsProjectile
{
	namespace NPayload
	{
		namespace NModifier
		{
			/**
			* 
			*/
			struct CSPRJ_API FImplSlice : public IModifier,
										  public ICsReset
			{
			public:

				static const FName Name;

			#define ModifierType NCsProjectile::NModifier::IModifier

			private:

				// ICsGetInterfaceMap

				FCsInterfaceMap* InterfaceMap;

			public:

				// IModifier

				TArray<ModifierType*> Modifiers;

				UObject* Root;

			public:

				FImplSlice();

			// ICsGetInterfaceMap
			#pragma region
			public:

				FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const { return InterfaceMap; }

			#pragma endregion ICsGetInterfaceMap

			public:

				void SetInterfaceMap(FCsInterfaceMap* InInterfaceMap);

			// IModifier
			#pragma region
			public:

				FORCEINLINE const TArray<ModifierType*>& GetModifiers() const { return Modifiers; }

			#pragma endregion IModifier

			// ICsReset
			#pragma region
			public:

				void Reset();

			#pragma endregion ICsReset

			public:

				bool CopyFrom(const FImplSlice* From);

				FORCEINLINE static void Deconstruct(void* Ptr)
				{
					delete static_cast<NCsProjectile::NPayload::NModifier::FImplSlice*>(Ptr);
				}

			#undef ModifierType
			};
		}
	}
}