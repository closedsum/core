// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.

#pragma once

// FCsScopedInteractiveObjectHoldParams
#pragma region

class UObject;
struct FCsResource_InteractiveObjectHoldParams;
struct ICsInteractiveObjectHoldParams;

struct FCsScopedInteractiveObjectHoldParams
{
private:

	UObject* Root;
	FCsResource_InteractiveObjectHoldParams* ResourceContainer;

public:

	FCsScopedInteractiveObjectHoldParams();
	FCsScopedInteractiveObjectHoldParams(UObject* InRoot);
	~FCsScopedInteractiveObjectHoldParams();

	ICsInteractiveObjectHoldParams* Get() const;

	template<typename ParamType>
	FORCEINLINE ParamType* Get() const
	{
		static_assert(std::is_base_of<ICsInteractiveObjectHoldParams, ParamType>(), "FCsScopedInteractiveObjectHoldParams::Get: ParamType does NOT implement interface: ICsInteractiveObjectHoldParams.");

		return static_cast<ParamType*>(ResourceContainer->Get());
	}

	FORCEINLINE ICsInteractiveObjectHoldParams& GetRef() const
	{
		return *Get();
	}

	template<typename ParamType>
	FORCEINLINE ParamType* GetRef() const
	{
		static_assert(std::is_base_of<ICsInteractiveObjectHoldParams, ParamType>(), "FCsScopedInteractiveObjectHoldParams::GetRef: ParamType does NOT implement interface: ICsInteractiveObjectHoldParams.");

		return *Get<ParamType>();
	}
};

#pragma endregion FCsScopedInteractiveObjectHoldParams