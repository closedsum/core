// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Types
#include "CsMacro_Namespace.h"
#include "CsMacro_Proxy.h"
// Log
#include "Utility/CsPrjLog.h"

#include "CsParams_Projectile_Launch.generated.h"

// FCsProjectile_Launch_DelayParams
#pragma region

struct FCsProjectile_Launch_DelayParams;

// ParamsType (NCsProjectile::NLaunch::NDelay::FParams)
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsProjectile, NLaunch, NDelay, FParams)

namespace NCsProjectile_Launch_DelayParams
{
	using ThisType = FCsProjectile_Launch_DelayParams;
	using ParamsType = NCsProjectile::NLaunch::NDelay::FParams;

	// Separate implementation to allow for clearer use of aliases
	struct CSPRJ_API FImpl
	{
	public:

		static void CopyToParams(ThisType* This, ParamsType* Params);
		static void CopyToParamsAsValue(const ThisType* This, ParamsType* Params);
	};
}

// ParamsType (NCsProjectile::NLaunch::NDelay::FParams)
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

	using ParamsType = NCsProjectile::NLaunch::NDelay::FParams;
	using _Impl = NCsProjectile_Launch_DelayParams::FImpl;

	FORCEINLINE void CopyToParams(ParamsType* Params)				{ _Impl::CopyToParams(this, Params); }
	FORCEINLINE void CopyToParamsAsValue(ParamsType* Params) const	{ _Impl::CopyToParamsAsValue(this, Params); }

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

struct FCsProjectile_LaunchParams;

// ParamsType (NCsProjectile::NLaunch::FParams)
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsProjectile, NLaunch, FParams)

namespace NCsProjectile_LaunchParams
{
	using ThisType = FCsProjectile_LaunchParams;
	using ParamsType = NCsProjectile::NLaunch::FParams;

	// Separate implementation to allow for clearer use of aliases
	struct CSPRJ_API FImpl
	{
	public:

		static void CopyToParams(ThisType* This, ParamsType* Params);
		static void CopyToParamsAsValue(const ThisType* This, ParamsType* Params);
	};
}

// ParamsType (NCsProjectile::NLaunch::FParams)
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

	using ParamsType = NCsProjectile::NLaunch::FParams;
	using _Impl = NCsProjectile_LaunchParams::FImpl;

	FORCEINLINE void CopyToParams(ParamsType* Params)				{ _Impl::CopyToParams(this, Params); }
	FORCEINLINE void CopyToParamsAsValue(ParamsType* Params) const	{ _Impl::CopyToParamsAsValue(this, Params); }

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
		private:

			using DelayParamsTypes = NCsProjectile::NLaunch::NDelay::FParams;

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
		};
	}
}

#pragma endregion FCsProjectile_LaunchParams