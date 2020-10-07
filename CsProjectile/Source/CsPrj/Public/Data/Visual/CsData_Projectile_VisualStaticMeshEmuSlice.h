// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Data/Visual/CsData_Projectile_VisualStaticMesh.h"

struct FCsInterfaceMap;
struct FCsPrjStaticMesh;

namespace NCsProjectile
{
	namespace NData
	{
		namespace NVisual
		{
			namespace NStaticMesh
			{
				/**
				*/
				struct CSPRJ_API FEmuSlice final : public ICsData_Projectile_VisualStaticMesh
				{
				public:

					static const FName Name;

				private:

					FCsInterfaceMap* InterfaceMap;

					// ICsData_Projectile_VisualStaticMesh

					FCsPrjStaticMesh* StaticMesh;

				public:

					FEmuSlice() : 
						InterfaceMap(nullptr),
						StaticMesh(nullptr)
					{
					}

					~FEmuSlice()
					{
					}

				public:

					FORCEINLINE UObject* _getUObject() const { return nullptr; }

					// ICsGetInterfaceMap
					#pragma region
					public:

						FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const
						{
							return InterfaceMap;
						}

					#pragma endregion ICsGetInterfaceMap

					public:

					FORCEINLINE void SetInterfaceMap(FCsInterfaceMap* Map)
					{
						InterfaceMap = Map;
					}

					// ICsData_Projectile_VisualStaticMesh
					#pragma region
					public:

					FORCEINLINE const FCsPrjStaticMesh& GetStaticMesh() const
					{
						return *StaticMesh;
					}

					#pragma endregion ICsData_Projectile_VisualStaticMesh

					public:

					FORCEINLINE void SetStaticMesh(FCsPrjStaticMesh* Value)
					{
						StaticMesh = Value;
					}
				};
			}
		}
	}
}