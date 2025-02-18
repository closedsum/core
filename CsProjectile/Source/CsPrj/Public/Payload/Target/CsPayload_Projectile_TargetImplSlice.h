// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Interfaces
#include "Payload/Target/CsPayload_Projectile_Target.h"
#include "Reset/CsReset.h"

class UObject;
struct FCsInterfaceMap;
class USceneComponent;

namespace NCsProjectile
{
	namespace NPayload
	{
		namespace NTarget
		{
			namespace NImplSlice
			{
				using TargetPayloadType = NCsProjectile::NPayload::NTarget::ITarget;

				/**
				* 
				*/
				struct CSPRJ_API FImplSlice : public TargetPayloadType,
											  public ICsReset
				{
				public:

					static const FName Name;

				private:

					using ThisType = NCsProjectile::NPayload::NTarget::NImplSlice::FImplSlice;

				private:

					// ICsGetInterfaceMap

					FCsInterfaceMap* InterfaceMap;

					// TargetPayloadType (NCsProjectile::NPayload::NTarget::ITarget)

				public:

					bool bTarget;

					USceneComponent* Component;

					FVector Location;

					FName Bone;
				
					int32 ID;

				public:

					FImplSlice();

				public:

					FORCEINLINE UObject* _getUObject() const { return nullptr; }

					void SetInterfaceMap(FCsInterfaceMap* InInterfaceMap);

				// ICsGetInterfaceMap
				#pragma region
				public:

					FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const { return InterfaceMap; }

				#pragma endregion ICsGetInterfaceMap

				// TargetPayloadType (NCsProjectile::NPayload::NTarget::ITarget)
				#pragma region
				public:

					FORCEINLINE const bool& HasTarget() const { return bTarget; }
					FORCEINLINE USceneComponent* GetTargetComponent() const { return Component; }
					FORCEINLINE const FVector& GetTargetLocation() const { return Location; }
					FORCEINLINE const FName& GetTargetBone() const { return Bone; }
					FORCEINLINE const int32& GetTargetID() const { return ID; }

				#pragma endregion TargetPayloadType (NCsProjectile::NPayload::NTarget::ITarget)

				// ICsReset
				#pragma region
				public:

					void Reset();

				#pragma endregion ICsReset

				public:

					FORCEINLINE static void Deconstruct(void* Ptr)
					{
						delete static_cast<ThisType*>(Ptr);
					}
				};
			}
		}
	}
}