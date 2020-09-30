// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Payload/Damage/CsPayload_ProjectileModifierDamage.h"
#include "Reset/CsReset.h"

#pragma once

class UObject;
struct FCsInterfaceMap;

namespace NCsProjectile
{
	namespace NPayload
	{
		namespace NModifier
		{
			namespace NDamage
			{
				/**
				* 
				*/
				struct CSPRJ_API FImplSlice : public IDamage,
											  public ICsReset
				{
				public:

					static const FName Name;

				private:

					// ICsGetInterfaceMap

					FCsInterfaceMap* InterfaceMap;

				public:

					// ICsPayload_ProjectileModifierDamage

					TArray<ICsDamageModifier*> Modifiers;

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

				// ICsPayload_ProjectileModifierDamage
				#pragma region
				public:

					FORCEINLINE const TArray<ICsDamageModifier*>& GetDamageModifiers() const
					{
						return Modifiers;
					}

				#pragma endregion ICsPayload_ProjectileModifierDamage

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