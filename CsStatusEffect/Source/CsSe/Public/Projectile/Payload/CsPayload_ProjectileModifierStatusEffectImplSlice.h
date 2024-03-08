// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "Projectile/Payload/CsPayload_ProjectileModifierStatusEffect.h"
#include "Reset/CsReset.h"

#pragma once

class UObject;
struct FCsInterfaceMap;

namespace NCsStatusEffect {
	namespace NModifier { 
		struct IModifier; } }

namespace NCsProjectile
{
	namespace NPayload
	{
		namespace NModifier
		{
			namespace NStatusEffect
			{
				/**
				* 
				*/
				struct CSSE_API FImplSlice : public IStatusEffect,
											 public ICsReset
				{
				public:

					static const FName Name;

				private:

					typedef NCsStatusEffect::NModifier::IModifier ModifierType;

					// ICsGetInterfaceMap

					FCsInterfaceMap* InterfaceMap;

				public:

					// IStatusEffect

					TArray<ModifierType*> Modifiers;

				public:

					FImplSlice();

				// ICsGetInterfaceMap
				#pragma region
				public:

					FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const
					{
						return InterfaceMap;
					}

				#pragma endregion ICsGetInterfaceMap

				public:

					void SetInterfaceMap(FCsInterfaceMap* InInterfaceMap);

				// IStatusEffect
				#pragma region
				public:

					FORCEINLINE const TArray<ModifierType*>& GetDamageModifiers() const
					{
						return Modifiers;
					}

				#pragma endregion IStatusEffect

				// ICsReset
				#pragma region
				public:

					void Reset();

				#pragma endregion ICsReset

				public:

					bool CopyFrom(const FImplSlice* From);
				};
			}
		}
	}
}