// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Containers/CsGetInterfaceMap.h"

struct FCsInterfaceMap;
class UObject;

namespace NCsProjectile
{
	namespace NData
	{
		/**
		* Structure for holding the InterfaceMap reference to any objects
		* that implement an interface "slice" related to objects of the same category
		* (data and projectile).
		* This interface map serves as the "root" to route all the interface slices.
		* This interface map allows other "layer" additional objects of the same category
		* (implementing interfaces related to data and projectile).
		*/
		struct CSPRJ_API FInterfaceMap final : public ICsGetInterfaceMap
		{
		public:

			static const FName Name;

		private:

			// ICsGetInterfaceMap

			FCsInterfaceMap* InterfaceMap;

		public:

			FInterfaceMap();
			~FInterfaceMap();


			FORCEINLINE UObject* _getUObject() const { return nullptr; }

		// ICsGetInterfaceMap
		#pragma region
		public:

			FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const
			{
				return InterfaceMap;
			}

		#pragma endregion ICsGetInterfaceMap
		};
	}
}