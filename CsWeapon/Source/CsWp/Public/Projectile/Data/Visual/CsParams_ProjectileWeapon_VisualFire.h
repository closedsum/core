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

						bool bEmulate;

						FCsFX FX;

						FCsFX* Emu_FX;

						EAttach Attach;

						EAttach* Emu_Attach;

					public:

						FParams() :
							bEmulate(false),
							FX(),
							Emu_FX(nullptr),
							Attach(EAttach::None),
							Emu_Attach(nullptr)
						{

						}

					public:

						FORCEINLINE void SetEmulate()
						{
							bEmulate = true;
						}

						FORCEINLINE const FCsFX& GetFX() const 
						{
							return bEmulate ? *Emu_FX : FX;
						}

						FORCEINLINE const EAttach& GetAttachType() const
						{
							return bEmulate ? *Emu_Attach : Attach;
						}

						FORCEINLINE void SetFX(FCsFX* InFX)
						{
							Emu_FX = InFX;
						}

						FORCEINLINE void SetAttachType(ECsProjectileWeaponVisualFireAttach* InAttach)
						{
							Emu_Attach = (EAttach*)InAttach;
						}
					};
				}
			}
		}
	}
}