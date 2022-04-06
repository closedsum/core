// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Containers/CsGetInterfaceMap.h"
#include "Containers/CsDeconstructInterfaceSliceMap.h"

struct FCsInterfaceMap;
class UObject;

namespace NCsUserWidget
{
	namespace NPayload
	{
		/**
		* Structure for holding the InterfaceMap reference to any objects
		* that implement an interface "slice" related to objects of the same category
		* (data).
		* This interface map serves as the "root" to route all the interface slices.
		* This interface map allows other "layer" additional objects of the same category
		* (implementing interfaces related to data).
		*/
		struct CSUI_API FInterfaceMap final : public ICsGetInterfaceMap,
											  public ICsDeconstructInterfaceSliceMap
		{
		public:

			static const FName Name;

		private:

			// ICsGetInterfaceMap

			FCsInterfaceMap* InterfaceMap;

			// ICsDeconstructInterfaceSliceMap

			TMap<FName, void*> SliceByNameMap;

			TMap<FName, void(*)(void*)> DeconstructSliceImplByNameMap;

		public:

			FInterfaceMap();
			~FInterfaceMap();


			FORCEINLINE UObject* _getUObject() const { return nullptr; }

		// ICsGetInterfaceMap
		#pragma region
		public:

			FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const { return InterfaceMap; }

		#pragma endregion ICsGetInterfaceMap

		// ICsDeconstructInterfaceSliceMap
		#pragma region
		public:

			void AddSlice(const FName& SliceName, void* Slice)
			{
				checkf(SliceName != NAME_None, TEXT("%s::AddSlice: SliceName: None is NOT Valid."), *(Name.ToString()));

				checkf(Slice, TEXT("%s::AddSlice: Slice is NULL."), *(Name.ToString()));

				checkf(SliceByNameMap.Find(SliceName) == nullptr, TEXT("%s::AddSlice: Slice: %s has ALREADY been added."), *(Name.ToString()), *(SliceName.ToString()));

				SliceByNameMap.Add(SliceName, Slice);
			}

			void AddDeconstructSliceImpl(const FName& SliceName, void(*DeconstructImpl)(void*))
			{
				checkf(SliceName != NAME_None, TEXT("%s::AddDeconstructSliceImpl: SliceName: None is NOT Valid."), *(Name.ToString()));

				checkf(DeconstructImpl, TEXT("%s::AddDeconstructSliceImpl: DeconstructImpl is NULL."), *(Name.ToString()));

				checkf(DeconstructSliceImplByNameMap.Find(SliceName) == nullptr, TEXT("%s::AddSlice: DeconstructImpl has ALREADY been added for Slice: %s."), *(Name.ToString()), *(SliceName.ToString()));

				DeconstructSliceImplByNameMap.Add(SliceName, DeconstructImpl);
			}

		#pragma endregion ICsDeconstructInterfaceSliceMap
		};
	}
}