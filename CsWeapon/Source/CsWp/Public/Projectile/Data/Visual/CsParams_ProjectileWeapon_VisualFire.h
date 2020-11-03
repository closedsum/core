// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Managers/FX/CsTypes_FX.h"

enum class ECsProjectileWeaponVisualFireAttach : uint8;

namespace NCsWeapon
{
	namespace NProjectile
	{
		namespace NData
		{
			namespace NVisual
			{
				namespace NFire
				{
					// Attach
					#pragma region

					/**
					*/
					enum class EAttach
					{
						None,
						Owner,
						Component,
						Custom
					};

					#pragma endregion Attach

					/**
					*/
					struct CSWP_API FParams
					{
					private:

						FCsFX FX;

						FCsFX* FX_Emu;

						EAttach Attach;

						EAttach* Attach_Emu;

					public:

						FParams() :
							FX(),
							FX_Emu(nullptr),
							Attach(EAttach::None),
							Attach_Emu(nullptr)
						{
							FX_Emu = &FX;
							Attach_Emu = &Attach;
						}

					public:

						FORCEINLINE void SetFX(FCsFX* Value) { FX_Emu = Value; }
						FORCEINLINE void SetAttachType(ECsProjectileWeaponVisualFireAttach* Value) { Attach_Emu = (EAttach*)Value; }

						FORCEINLINE const FCsFX& GetFX() const { return *FX_Emu; }
						FORCEINLINE const EAttach& GetAttachType() const { return *Attach_Emu; }
					};
				}
			}
		}
	}
}