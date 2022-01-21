// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

// Interfaces
#include "Containers/CsGetInterfaceMap.h"

#include "CsData_Skin_VisualSkeletalMesh.generated.h"

class USkeletalMesh;
struct FCsInterfaceMap;

namespace NCsSkin
{
	namespace NData
	{
		namespace NVisual
		{
			namespace NSkeletalMesh
			{
				/**
				* Interface of a Skin using a Skeletal Mesh as a visual representation.
				*/
				struct CSCORE_API ISkeletalMesh : public ICsGetInterfaceMap
				{
				public:

					static const FName Name;

				public:

					virtual ~ISkeletalMesh() {}

					/**
					*/
					virtual USkeletalMesh* GetSkeletalMesh() const = 0;
				};

				/**
				*/
				struct CSCORE_API FProxy : public ISkeletalMesh
				{
				public:

					static const FName Name;

				private:

					// ICsGetInterfaceMap

					FCsInterfaceMap* InterfaceMap;

					// ISkeletalMesh

					USkeletalMesh** Mesh;

				public:

					FProxy();
					~FProxy();

					FORCEINLINE UObject* _getUObject() const { return nullptr; }

				// ICsGetInterfaceMap
				#pragma region

					FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const { return InterfaceMap; }

				#pragma endregion ICsGetInterfaceMap

					FORCEINLINE void SetSkeletalMesh(USkeletalMesh** Value) { Mesh = Value; };

				// ISkeletalMesh
				#pragma region

					FORCEINLINE USkeletalMesh* GetSkeletalMesh() const { return *Mesh; }

				#pragma endregion ISkeletalMesh
				};
			}
		}
	}
}

UINTERFACE(BlueprintType)
class CSCORE_API UCsData_Skin_VisualSkeletalMesh : public UCsGetInterfaceMap
{
	GENERATED_UINTERFACE_BODY()
};

class USkeletalMesh;

/**
* Interface of a Skin using a Skeletal Mesh as a visual representation.
*/
class CSCORE_API ICsData_Skin_VisualSkeletalMesh : public ICsGetInterfaceMap
{
	GENERATED_IINTERFACE_BODY()

public:

	static const FName Name;

public:

	/**
	*/
	virtual USkeletalMesh* GetSkeletalMesh() const = 0;
};