// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Containers
#include "Containers/CsGetInterfaceMap.h"

struct FCsInterfaceMap;
class UObject;

namespace NCsWeapon
{
	namespace NPayload
	{
		/**
		* Structure for holding the InterfaceMap reference to any objects
		* that implement an interface "slice" related to objects of the same category
		* (payload and projectile).
		* This interface map serves as the "root" to route all the interface slices.
		* This interface map allows other (to "layer") additional objects of the same category 
		* (implementing interfaces related to payload and weapon).
		*/
		struct CSWP_API FInterfaceMap final : public ICsGetInterfaceMap
		{
		public:

			static const FName Name;

		private:

			// ICsGetInterfaceMap

			FCsInterfaceMap* InterfaceMap;
		
			TMap<FName, void(*)(void *)> DeconstructFnPtrByNameMap;

		public:

			FInterfaceMap();
			~FInterfaceMap();

			FORCEINLINE UObject* _getUObject() const { return nullptr; }

		// ICsGetInterfaceMap
		#pragma region
		public:

			FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const { return InterfaceMap; }

		#pragma endregion ICsGetInterfaceMap

		public:

			FORCEINLINE void AddDeconstruct(const FName& SliceName, void(*Fn)(void*))
			{
				DeconstructFnPtrByNameMap.Add(SliceName, Fn);
			}
		};
	}
}