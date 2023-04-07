#include "Containers/CsUniformGrid.h"
#include "CsCore.h"

// Library
#include "Library/CsLibrary_Valid.h"

namespace NCsGrid
{
	namespace NUniform
	{
		FGrid::FGrid() :
			Manager_ID(),
			Width(0.0f),
			WidthBy2(0.0f),
			NumColumns(0),
			NumColumnsMinusOne(0),
			CellWidth(0.0f),
			InverseCellWidth(0.0f),
			MaxStride(0),
			StartingIndices(),
			Strides(),
			IDs(),
			FreeIndex(0),
			DeallocatedIndices(),
			Centers(),
			Radii()
		{
		}

		void FGrid::Create(const float& InGridWidth, const float& InCellWidth, const int32& InMaxElements, const int32& InMaxStride)
		{

			Width	 = InGridWidth;
			WidthBy2 = 0.5f * Width;

			CellWidth		 = InCellWidth;
			InverseCellWidth = 1.0f / CellWidth;

			NumColumns			   = NCsGrid::NUniform::FHelper::CeilDiv(Width, CellWidth);
			NumColumnsMinusOne	   = NumColumns - 1;
			const int32 CellCount  = NumColumns * NumColumns;

			// Initialize Cells
			Manager_ID.CreatePool(CellCount);

			StartingIndices.Reset(CellCount);
			Strides.Reset(CellCount);
			Resources.Reset(CellCount);

			for (int32 I = 0; I < CellCount; ++I)
			{
				StartingIndices.Add(INDEX_NONE);
				Strides.Add(0);
				Resources.Add(nullptr);
			}

			// Initialize Element IDs for All Cells
			MaxStride = InMaxStride;

			const int32 IDCount = InMaxElements * 16;

			IDs.Reset(IDCount);

			for (int32 I = 0; I < IDCount; ++I)
			{
				IDs.Add(INDEX_NONE);
			}

			// Initialize Element "Data"
			Centers.Reset(InMaxElements);
			Radii.Reset(InMaxElements);

			for (int32 I = 0; I < InMaxElements; ++I)
			{
				Centers.Add(FVector2D::ZeroVector);
				Radii.Add(0.0f);
			}

			FreeIndex = 0;
		}

		void FGrid::Insert_Internal(const int32& ID, const float& CenterX, const float& CenterY, const float& Radius)
		{
			// TODO: Checks

			// Compute the Cell extents [min_tx, min_ty, max_tx, max_ty].
			const FVector4 qrect	= FVector4(CenterX - Radius, CenterY - Radius, CenterX + Radius, CenterY + Radius);
			FVector4 qrect_vec		= qrect;
			const FIntVector4 trect = GetCellIndex4(qrect_vec);

			// Check intersecting Cells
			int32 IDIndex = INDEX_NONE;

			for (int32 Row = trect.Y; Row <= trect.W; ++Row)
			{
				for (int32 Column = trect.X; Column <= trect.Z; ++Column)
				{
					const int32 CellIndex = Row * NumColumns + Column;

					if (StartingIndices[CellIndex] == INDEX_NONE)
					{
						StartingIndices[CellIndex] = AllocateStartingIndex();

						check(Resources[CellIndex] == nullptr);

						Resources[CellIndex]		   = Manager_ID.Allocate();
						Resources[CellIndex]->GetRef() = CellIndex;
					}

					const int32& StartingIndex = StartingIndices[CellIndex];
					IDIndex					   = StartingIndex + Strides[CellIndex];

					IDs[IDIndex] = ID;

					++(Strides[CellIndex]);

					//UE_LOG(LogCs, Warning, TEXT("Adding ID: %d to Cell: %d."), ID, CellIndex);

					check(Strides[CellIndex] <= MaxStride);
				}
			}

			Centers[ID].X = CenterX;
			Centers[ID].Y = CenterY;
			Radii[ID]	  = Radius;
		}

		void FGrid::Remove_Internal(const int32& ID, const float& CenterX, const float& CenterY)
		{
			// TODO: Checks
			
			// Compute the Cell extents [min_tx, min_ty, max_tx, max_ty].
			const float& Radius		= Radii[ID];
			const FVector4 qrect	= FVector4(CenterX - Radius, CenterY - Radius, CenterX + Radius, CenterY + Radius);
			FVector4 qrect_vec		= qrect;
			const FIntVector4 trect = GetCellIndex4(qrect_vec);

			// Check intersecting Cells
			int32 End = INDEX_NONE;

			for (int32 Row = trect.Y; Row <= trect.W; ++Row)
			{
				for (int32 Column = trect.X; Column <= trect.Z; ++Column)
				{
					const int32 CellIndex = Row * NumColumns + Column;

					// If Cell is NOT Empty, then iterate through elements
					if (StartingIndices[CellIndex] != INDEX_NONE)
					{
						const int32& StartingIndex = StartingIndices[CellIndex];
						const int32& Stride		   = Strides[CellIndex];

						End = StartingIndex + Stride;

						for (int32 I = StartingIndex; I < End; ++I)
						{
							// If NOT End of Stride, then Swap 'I' with 'End - 1' and remove 'End - 1'
							if (I < (End - 1))
							{
								IDs[I] = IDs[End - 1];
							}

							IDs[End - 1] = INDEX_NONE;

							--(Strides[CellIndex]);

							check(Strides[CellIndex] >= 0);

							//UE_LOG(LogCs, Warning, TEXT("Removing ID: %d from Cell: %d."), ID, CellIndex);

							// If ID was the LAST element for the Cell, then "Deallocate" the Cell. 
							if (Strides[CellIndex] == 0)
							{
								//UE_LOG(LogCs, Warning, TEXT("Deallocating Cell: %d."), CellIndex);

								DeallocatedIndices.Add(StartingIndex);

								check(Resources[CellIndex]);

								StartingIndices[CellIndex] = INDEX_NONE;
								Strides[CellIndex] = 0;

								Manager_ID.Deallocate(Resources[CellIndex]);

								Resources[CellIndex] = nullptr;
							}
						}
					}
				}
			}

			// Sanity Check
			/*
			const int32 Count = StartingIndices.Num();

			for (int32 I = 0; I < Count; ++I)
			{
				const int32& _StartingIndex = StartingIndices[I];

				if (_StartingIndex != INDEX_NONE)
				{
					const int32 _End = _StartingIndex + Strides[I];

					for (int32 J = _StartingIndex; J < _End; ++J)
					{
						if (IDs[J] == ID)
						{
							UE_LOG(LogCs, Warning, TEXT("ID: %d found in Cell: %d."), ID, I);
							check(0);
						}
					}
				}
			}
			*/
		}

		void FGrid::Move_Internal(const int32& ID, const float& PrevCenterX, const float& PrevCenterY, float CenterX, float CenterY)
		{
			Remove_Internal(ID, PrevCenterX, PrevCenterY);
			Insert_Internal(ID, CenterX, CenterY, Radii[ID]);
		}

		#define QueryResultType NCsGrid::NUniform::FGrid::FQuery::FResult
		void FGrid::Query_Internal(float CenterX, float CenterY, float HalfWidth, float HalfHeight, const int32& OmitID, QueryResultType& OutResult) const
		{
		#undef QueryResultType

			static TSet<int32> TempQueryIDs;
			TempQueryIDs.Reset();

			OutResult.Count = 0;
			OutResult.InterationCount = 0;

			// Compute the Cell extents [min_tx, min_ty, max_tx, max_ty].
			const FVector4 qrect	= FVector4(CenterX - HalfWidth, CenterY - HalfHeight, CenterX + HalfWidth, CenterY + HalfHeight);
			FVector4 qrect_vec		= qrect;
			const FIntVector4 trect = GetCellIndex4(qrect_vec);

			// Check intersecting Cells
			int32 End = INDEX_NONE;

			for (int32 Row = trect.Y; Row <= trect.W; ++Row)
			{
				for (int32 Column = trect.X; Column <= trect.Z; ++Column)
				{
					const int32 CellIndex = Row * NumColumns + Column;

					// If Cell is NOT Empty, then iterate through elements
					if (StartingIndices[CellIndex] != INDEX_NONE)
					{
						const int32& StartingIndex = StartingIndices[CellIndex];
						const int32& Stride		   = Strides[CellIndex];

						End = StartingIndex + Stride;

						for (int32 I = StartingIndex; I < End; ++I)
						{
							const int32& ID = IDs[I];

							if (ID != OmitID)
							{
								if ((FMath::Abs(Centers[ID].X - CenterX) < (Radii[ID] + HalfWidth)) &&
									(FMath::Abs(Centers[ID].Y - CenterY) < (Radii[ID] + HalfHeight)))
								{
									TempQueryIDs.Add(ID);
									//OutResult.IDs.Add(ID);
									//++OutResult.Count;
								}
							}
							++OutResult.InterationCount;
						}
					}
					++OutResult.InterationCount;
				}
			}

			for (const int32& ID : TempQueryIDs)
			{
				OutResult.IDs.Add(ID);

				++OutResult.Count;
				++OutResult.InterationCount;
			}
		}

		void FGrid::Reset()
		{
			typedef NCsResource::NManager::NValue::NFixed::NInt32::FResource ResourceType;

			TCsDoubleLinkedList<ResourceType*>* Current = Manager_ID.GetAllocatedHead();
			TCsDoubleLinkedList<ResourceType*>* Next	= Current;

			int32 End = INDEX_NONE;

			while (Next)
			{
				Current			= Next;
				ResourceType* C = **Current;
				Next			= Current->GetNextLink();

				int32& CellIndex = C->GetRef();

				const int32& StartingIndex = StartingIndices[CellIndex];
				const int32& Stride		   = Strides[CellIndex];

				for (int32 I = StartingIndex; I < End; ++I)
				{
					IDs[I] = INDEX_NONE;
				}
				StartingIndices[CellIndex] = INDEX_NONE;
				Strides[CellIndex]		   = 0;
				Resources[CellIndex]	   = nullptr;
			}

			Manager_ID.DeallocateAll();

			FreeIndex = 0;
			DeallocatedIndices.Reset(DeallocatedIndices.Max());
		}
	}
}