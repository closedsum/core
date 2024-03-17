// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Types
#include "Types/CsTypes_Macro.h"
#include "Macro/CsMacro_Namespace.h"
// Log
#include "Utility/CsPrjLog.h"

#include "CsParams_Projectile_Launch.generated.h"

// FCsProjectile_Launch_DelayParams
#pragma region

// NCsProjectile::NLaunch::NDelay::FParams
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsProjectile, NLaunch, NDelay, FParams)

USTRUCT(BlueprintType)
struct CSPRJ_API FCsProjectile_Launch_DelayParams
{
	GENERATED_USTRUCT_BODY()

public:

	/** Whether to collision becoming active should be delayed. 
		Delay must be > 0.0f for this to take into effect. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CImpl|Projectile|Launch")
	bool bCollision;

	/** Whether the projectile should "track" (equivalent to homing, but not moving)
		a target before the launch is delayed. 
		Delay must be > 0.0f for this to take into effect. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CImpl|Projectile|Launch")
	bool bTracking;

	FCsProjectile_Launch_DelayParams() :
		bCollision(false),
		bTracking(false)
	{
	}

#define ParamsType NCsProjectile::NLaunch::NDelay::FParams
	void CopyToParams(ParamsType* Params);
	void CopyToParamsAsValue(ParamsType* Params) const;
#undef ParamsType

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning) const;
};

namespace NCsProjectile
{
	namespace NLaunch
	{
		namespace NDelay
		{
			struct CSPRJ_API FParams
			{
			private:

				CS_DECLARE_MEMBER_WITH_PROXY(bCollision, bool)
				CS_DECLARE_MEMBER_WITH_PROXY(bTracking, bool)

			public:

				FParams() :
					CS_CTOR_INIT_MEMBER_WITH_PROXY(bCollision, false),
					CS_CTOR_INIT_MEMBER_WITH_PROXY(bTracking, false)
				{
					CS_CTOR_SET_MEMBER_PROXY(bCollision);
					CS_CTOR_SET_MEMBER_PROXY(bTracking);
				}

				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(bCollision, bool)
				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(bTracking, bool)

				bool IsValidChecked(const FString& Context) const;
				bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning) const;
			};
		}
	}
}

#pragma endregion FCsProjectile_Launch_DelayParams

// FCsProjectile_LaunchParams
#pragma region

// NCsProjectile::NLaunch::FParams
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsProjectile, NLaunch, FParams)

/**
* Describes any launch information associated with a Projectile.
*  Projectile is an object that implements the interface: ICsProjectile.
*/
USTRUCT(BlueprintType)
struct CSPRJ_API FCsProjectile_LaunchParams
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CImpl|Projectile|Launch", meta = (UIMin = "0.0", ClampMin = "0.0"))
	float Delay;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CImpl|Projectile|Launch")
	FCsProjectile_Launch_DelayParams DelayParams;

	FCsProjectile_LaunchParams() :
		Delay(0.0f),
		DelayParams()
	{
	}

#define ParamsType NCsProjectile::NLaunch::FParams
	void CopyToParams(ParamsType* Params);
	void CopyToParamsAsValue(ParamsType* Params) const;
#undef ParamsType

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning) const;
};

namespace NCsProjectile
{
	namespace NLaunch
	{
		/**
		* Describes any launch information associated with a Projectile.
		*  Projectile is an object that implements the interface: ICsProjectile.
		*/
		struct CSPRJ_API FParams
		{
		#define DelayParamsTypes NCsProjectile::NLaunch::NDelay::FParams

		private:

			CS_DECLARE_MEMBER_WITH_PROXY(Delay, float)

		public:

			DelayParamsTypes DelayParams;

		public:

			FParams() :
				CS_CTOR_INIT_MEMBER_WITH_PROXY(Delay, 0.0f),
				DelayParams()
			{
				CS_CTOR_SET_MEMBER_PROXY(Delay);
			}

			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Delay, float)

			FORCEINLINE const DelayParamsTypes& GetDelayParams() const { return DelayParams; }
			FORCEINLINE DelayParamsTypes* GetDelayParamsPtr() { return &DelayParams; }

			bool IsValidChecked(const FString& Context) const;
			bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning) const;

		#undef DelayParamsTypes
		};
	}
}

#pragma endregion FCsProjectile_LaunchParams