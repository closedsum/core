// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Interfaces
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "Managers/FX/CsTypes_FX.h"

struct FCsInterfaceMap;

namespace NCsWeapon
{
	namespace NTrace
	{
		namespace NData
		{
			namespace NVisual
			{
				namespace NFire
				{
					namespace NParams
					{
						// Attach
						#pragma region

						/**
						*/
						enum class EAttach
						{
							None,
							Owner,
							Component,
							Custom
						};

						#pragma endregion Attach

						struct CSWP_API IParams : public ICsGetInterfaceMap
						{
						public:

							static const FName Name;

						public:

							virtual ~IParams(){}

							/**
							*/
							virtual const FCsFX& GetFX() const = 0;

							/**
							*/
							virtual const EAttach& GetAttachType() const = 0;
						};

						/**
						*/
						struct CSWP_API FProxy : public IParams
						{
						public:

							static const FName Name;

						private:

							// ICsGetInterfaceMap

							FCsInterfaceMap* InterfaceMap;

							// IParams

							FCsFX* FX;

							EAttach* Attach;

						public:

							FProxy();
							~FProxy();

						public:

							FORCEINLINE UObject* _getUObject() const { return nullptr; }

						// ICsGetInterfaceMap
						#pragma region
						public:

							FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const { return InterfaceMap; }

						#pragma endregion ICsGetInterfaceMap

							FORCEINLINE void SetFX(FCsFX* Value){ FX = Value; }
							FORCEINLINE void SetAttachType(EAttach* Value){ Attach = Value; }

						// IParams
						#pragma region

							FORCEINLINE const FCsFX& GetFX() const { return *FX; }
							FORCEINLINE const EAttach& GetAttachType() const { return *Attach; }

						#pragma endregion IParams
						};
					}
				}
			}
		}
	}
}