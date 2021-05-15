// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Data/CsData_Projectile.h"

struct FCsInterfaceMap;

namespace NCsProjectile
{
	namespace NData
	{
		/**
		* "Emulates" ProjectileDataType (NCsProjectile::NData::IData) by mimicking the interfaces and having pointers to the appropriate
		* members. The idea behind this struct is to "build" the data via composition of separate objects that each implementation
		* a specific interface.
		*/
		struct CSPRJ_API FEmuSlice final : public IData
		{
		public:

			static const FName Name;

		private:
			
			// ICsGetInterfaceMap

			/** Pointer to the "root" object for all "Emu Slices". That object acts as the hub for the separate objects (via composition) 
				that describe the data. */
			FCsInterfaceMap* InterfaceMap;

			// ProjectileDataType (NCsProjectile::NData::IData)

			float* LifeTime;

			float* InitialSpeed;

			float* MaxSpeed;

			float* GravityScale;

		public:

			FEmuSlice() :
				InterfaceMap(nullptr),
				InitialSpeed(nullptr),
				MaxSpeed(nullptr),
				GravityScale(nullptr)
			{
			}

			~FEmuSlice(){}

			FORCEINLINE UObject* _getUObject() const { return nullptr; }

		public:

			FORCEINLINE void SetInterfaceMap(FCsInterfaceMap* Map) { InterfaceMap = Map; }

		// ICsGetInterfaceMap
		#pragma region
		public:

			FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const { return InterfaceMap; }

		#pragma endregion ICsGetInterfaceMap

		public:

			FORCEINLINE void SetLifeTime(float* Value) { LifeTime = Value; }
			FORCEINLINE void SetInitialSpeed(float* Value) { InitialSpeed = Value; }
			FORCEINLINE void SetMaxSpeed(float* Value) { MaxSpeed = Value; }
			FORCEINLINE void SetGravityScale(float* Value) { GravityScale = Value; }

		// ICsData_Projectile
		#pragma region
		public:

			FORCEINLINE const float& GetLifeTime() const { return *LifeTime; }
			FORCEINLINE const float& GetInitialSpeed() const { return *InitialSpeed; }
			FORCEINLINE const float& GetMaxSpeed() const { return *MaxSpeed; }
			FORCEINLINE const float& GetGravityScale() const { return *GravityScale; }

		#pragma endregion ICsData_Projectile
		};
	}
}