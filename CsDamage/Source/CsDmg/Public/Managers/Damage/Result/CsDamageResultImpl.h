// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Managers/Damage/Result/CsDamageResult.h"

class UObject;
struct FCsInterfaceMap;

namespace NCsDamage
{
	namespace NResult
	{
		/**
		*/
		struct CSDMG_API FImpl final : public IResult
		{
		public:

			static const FName Name;

		private:

			FCsInterfaceMap* InterfaceMap;

		public:

			// IResult

			float Damage;

			UObject* Instigator;

			UObject* Causer;

			UObject* Victim;
	
			FECsDamageType DamageType;

			FECsHitType HitType;

			bool bImpulse;

			FHitResult HitResult;

		public:

			FImpl();
			~FImpl();

		// ICsGetInterfaceMap
		#pragma region
		public:

			FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const
			{
				return InterfaceMap;
			}

		#pragma endregion ICsGetInterfaceMap

		// IResult
		#pragma region
		public:

			FORCEINLINE const float& GetDamage() const
			{
				return Damage;
			}

			FORCEINLINE UObject* GetInstigator() const
			{
				return Instigator;
			}

			FORCEINLINE UObject* GetCauser() const
			{
				return Causer;
			}

			FORCEINLINE UObject* GetVictim() const
			{
				return Victim;
			}

			FORCEINLINE const FECsDamageType& GetDamageType() const
			{
				return DamageType;
			}

			FORCEINLINE const FECsHitType& GetHitType() const
			{
				return HitType;
			}

			FORCEINLINE const bool& HasImpulse() const
			{
				return bImpulse;
			}

			FORCEINLINE const FHitResult& GetHitResult() const
			{
				return HitResult;
			}

		#pragma endregion IResult

		public:

			template<typename T>
			FORCEINLINE T* GetInstigator() const
			{
				return Cast<T>(GetInstigator());
			}

			template<typename T>
			FORCEINLINE T* GetCauser() const
			{
				return Cast<T>(GetCauser());
			}

			template<typename T>
			FORCEINLINE T* GetVictim() const
			{
				return Cast<T>(GetVictim());
			}

			void Reset();
		};
	}
}