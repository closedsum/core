// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Types
#include "Modifier/CsProjectileModifierImpl.h"
// Log
#include "Utility/CsPrjLog.h"

#include "CsParams_Projectile_OnHit_Ricochet.generated.h"

// FCsProjectile_OnHit_RicochetParams
#pragma region

// NCsProjectile::NOnHit::NRicochet::FParams
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsProjectile, NOnHit, NRicochet, FParams)

/**
* Describes any ricochet collision associated with a Projectile.
*  Projectile is an object that implements the interface: ICsProjectile.
*/
USTRUCT(BlueprintType)
struct CSPRJ_API FCsProjectile_OnHit_RicochetParams
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CImpl|Projectile|Collision", meta = (UIMin = "0.0", ClampMin = "0.0"))
	float Radius;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CImpl|Projectile|Collision")
	bool bInheritModifiers;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CImpl|Projectile|Collision")
	FCsProjectileModifierInfo Modifiers;

	FCsProjectile_OnHit_RicochetParams() :
		Radius(false),
		bInheritModifiers(false),
		Modifiers()
	{
	}

#define ParamsType NCsProjectile::NOnHit::NRicochet::FParams
	void CopyToParams(ParamsType* Params);
	void CopyToParamsAsValue(ParamsType* Params) const;
#undef ParamsType

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning) const;
};

namespace NCsProjectile
{
	namespace NOnHit
	{
		namespace NRicochet
		{
			/**
			* Describes any ricochet collision associated with a Projectile.
			*  Projectile is an object that implements the interface: ICsProjectile.
			*/
			struct CSPRJ_API FParams
			{
			#define ModifierInfoType NCsProjectile::NModifier::FInfo

			private:

				CS_DECLARE_MEMBER_WITH_PROXY(Radius, float)
				CS_DECLARE_MEMBER_WITH_PROXY(bInheritModifiers, bool)

			public:

				ModifierInfoType Modifiers;

			public:

				FParams() :
					CS_CTOR_INIT_MEMBER_WITH_PROXY(Radius, 0.0f),
					CS_CTOR_INIT_MEMBER_WITH_PROXY(bInheritModifiers, false),
					Modifiers()
				{
					CS_CTOR_SET_MEMBER_PROXY(Radius);
					CS_CTOR_SET_MEMBER_PROXY(bInheritModifiers);
				}

				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Radius, float)
				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(bInheritModifiers, bool)

				FORCEINLINE const ModifierInfoType& GetModifiers() const { return Modifiers; }
				FORCEINLINE ModifierInfoType* GetModifiersPtr() { return &Modifiers; }

				bool IsValidChecked(const FString& Context) const;
				bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning) const;

			#undef ModifierInfoType
			};
		}
	}
}

#pragma endregion FCsProjectile_OnHit_RicochetParams