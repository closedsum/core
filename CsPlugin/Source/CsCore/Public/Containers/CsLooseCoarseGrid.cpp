#include "Containers/CsLooseCoarseGrid.h"

namespace NCsLooseCoarseGrid
{
	FGrid::FGrid() :
		Tight(),
		Loose(),
		Elements(),
		NumElements(0),
		Left(0.0f),
		Top(0.0f),
		Width(0.0f),
		Height(0.0f)
	{
	}

	void FGrid::Create(const float& LooseCellWidth, const float& LooseCellHeight, const float& TightCellWidth, const float& TightCellHeight,
						const float& InLeft, const float& InTop, const float& Right, const float& Bottom)
	{
		// TODO: Add checks

		// TODO: Check Unreal orientation from Top

		Width		= Right - Left;
		WidthBy2    = 0.5f * Width;
		Height		= Bottom - Top;
		HeightBy2   = 0.5f * Height;
		NumElements = 0;
		Left		= InLeft;
		Top			= InTop;

		const int32 NumLooseColumns = NCsLooseCoarseGrid::FHelper::CeilDiv(Width, LooseCellWidth);
		const int32 NumLooseRows	= NCsLooseCoarseGrid::FHelper::CeilDiv(Height, LooseCellHeight);

		Loose.Init(NumLooseColumns, NumLooseRows, LooseCellWidth, LooseCellHeight);

		const int32 NumTightColumns = NCsLooseCoarseGrid::FHelper::CeilDiv(Width, TightCellWidth);
		const int32 NumTightRows    = NCsLooseCoarseGrid::FHelper::CeilDiv(Height, TightCellHeight);

		Tight.Init(NumTightColumns, NumTightRows, TightCellWidth, TightCellHeight);
	}

	void FGrid::Insert_Internal(const int32& ID, const float& CenterX, const float& CenterY, const float& HalfWidth, const float& HalfHeight)
	{
		// TODO: Checks

		typedef NCsLooseCoarseGrid::NLoose::FCell LooseCellType;

		const int32 Index   = GetCellIndex(CenterX, CenterY);
		LooseCellType& Cell = Loose.Cells[Index];

		// Insert the element to the appropriate loose cell and row.
		const ElementType NewElement = {Cell.Head, ID, CenterX - Left, CenterY - Top, HalfWidth, HalfHeight};
		Cell.Head					 = Elements.insert(NewElement);
		++NumElements;

		// Expand the loose cell's bounding box to fit the new element.
		Expand_AABB(Index, CenterX, CenterY, HalfWidth, HalfHeight);
	}

	void FGrid::Remove_Internal(const int32& ID, const float& CenterX, const float& CenterY)
	{
		// Find the element in the loose cell.
		typedef NCsLooseCoarseGrid::NLoose::FCell LooseCellType;

		LooseCellType& Cell = Loose.Cells[GetCellIndex(CenterX, CenterY)];
		int32* Link			= Cell.GetHeadPtr();

		while (Elements[*Link].GetID() != ID)
		{
			Link = Elements[*Link].GetNextPtr();
		}

		// Remove the element from the loose cell and row.
		const int32 Index = *Link;
		*Link			  = Elements[Index].GetNext();

		Elements.erase(Index);
		--NumElements;
	}

	void FGrid::Move_Internal(const int32& ID, const float& PrevCenterX, const float& PrevCenterY, float CenterX, float CenterY)
	{
		typedef NCsLooseCoarseGrid::NLoose::FCell LooseCellType;

		const int32 PrevIndex = GetCellIndex(PrevCenterX, PrevCenterY);
		const int32 NewIndex  = GetCellIndex(CenterX, CenterY);
		LooseCellType& Cell	  = Loose.Cells[PrevIndex];

		if (PrevIndex == NewIndex)
		{
			// Find the element in the loose cell.
			int32 Index = Cell.Head;

			while (Elements[Index].GetID() != ID)
			{
				Index = Elements[Index].GetNext();
			}

			// Since the element is still inside the same cell, we can simply overwrite 
			// its position and expand the loose cell's AABB.
			CenterX -= Left;
			CenterY -= Top;
			Elements[Index].CenterX = CenterX;
			Elements[Index].CenterY = CenterY;

			Expand_AABB(PrevIndex, CenterX, CenterY, Elements[Index].HalfWidth, Elements[Index].HalfHeight);
		}
		else
		{
			// Find the element in the loose cell.
			int32* Link = Cell.GetHeadPtr();

			while (Elements[*Link].GetID() != ID)
			{
				Link = Elements[*Link].GetNextPtr();
			}

			const int32 Index	   = *Link;
			const float HalfWidth  = Elements[Index].HalfWidth;
			const float HalfHeight = Elements[Index].HalfHeight;

			// If the element has moved into a different loose cell, remove
			// remove the element from the previous loose cell and row.
			*Link = Elements[Index].GetNext();
			Elements.erase(Index);
			--NumElements;

			// Now insert the element to its new position.
			Insert(ID, CenterX, CenterY, HalfWidth, HalfHeight);
		}
	}

	TSmallList<int32> FGrid::Query(float CenterX, float CenterY, float HalfWidth, float HalfHeight, const int32& OmitID)
	{
		CenterX -= Left;
		CenterY -= Top;

		// Compute the tight cell extents [min_tx, min_ty, max_tx, max_ty].
		const FVector4 qrect	= FVector4(CenterX - HalfWidth, CenterY - HalfHeight, CenterX + HalfWidth, CenterY + HalfHeight);
		FVector4 qrect_vec		= qrect;
		const FIntVector4 trect = GetCellIndex4(qrect_vec);

		// Gather the intersecting loose cells in the tight cells that intersect.
		TSmallList<int32> LooseCellIndices;

		for (int32 ty = trect.Y; ty <= trect.W; ++ty)
		{
			const int32* tight_row = Tight.Heads + (ty * Tight.NumColumns);

			for (int32 tx = trect.X; tx <= trect.Z; ++tx)
			{
				// Iterate through the loose cells that intersect the tight cells.
				int32 tcell_idx = tight_row[tx];

				while (tcell_idx != INDEX_NONE)
				{
					typedef NCsLooseCoarseGrid::NTight::FCell TightCellType;
					typedef NCsLooseCoarseGrid::NLoose::FCell LooseCellType;

					const TightCellType& TightCell = Tight.Cells[tcell_idx];
					const LooseCellType& LooseCell = Loose.Cells[TightCell.Index];

					if (LooseCellIndices.find_index(TightCell.Index) == INDEX_NONE && NCsLooseCoarseGrid::FHelper::DoesRectIntersect(qrect_vec, LooseCell.RectToVector4()))
						LooseCellIndices.push_back(TightCell.Index);
					tcell_idx = TightCell.Next;
				}
			}
		}

		// For each loose cell, determine what elements intersect.
		TSmallList<int32> Result;

		for (int32 I = 0; I < LooseCellIndices.size(); ++I)
		{
			typedef NCsLooseCoarseGrid::NLoose::FCell LooseCellType;

			const LooseCellType& LooseCell = Loose.Cells[LooseCellIndices[I]];
			int32 elt_idx				   = LooseCell.Head;

			while (elt_idx != INDEX_NONE)
			{
				// If the element intersects the search rectangle, add it to the
				// resulting elements unless it has an ID that should be omitted.
				const ElementType& Element = Elements[elt_idx];

				if (Element.GetID() != OmitID && NCsLooseCoarseGrid::FHelper::DoesRectIntersect(qrect_vec, Element.ToRectAsVector4()))
					Result.push_back(Element.GetID());

				elt_idx = Element.GetNext();
			}
		}
		return Result;
	}

	void FGrid::Query_Internal(float CenterX, float CenterY, float HalfWidth, float HalfHeight, const int32& OmitID, TArray<int32>& OutResult, int32& OutResultCount) const
	{
		CenterX -= Left;
		CenterY -= Top;

		// Compute the tight cell extents [min_tx, min_ty, max_tx, max_ty].
		const FVector4 qrect	= FVector4(CenterX - HalfWidth, CenterY - HalfHeight, CenterX + HalfWidth, CenterY + HalfHeight);
		FVector4 qrect_vec		= qrect;
		const FIntVector4 trect = GetCellIndex4(qrect_vec);

		// Gather the intersecting loose cells in the tight cells that intersect.
		static TArray<int32> LooseCellIndices;
		int32 Count = 0;

		for (int32 ty = trect.Y; ty <= trect.W; ++ty)
		{
			const int32* tight_row = Tight.Heads + (ty * Tight.NumColumns);

			for (int32 tx = trect.X; tx <= trect.Z; ++tx)
			{
				// Iterate through the loose cells that intersect the tight cells.
				int32 tcell_idx = tight_row[tx];

				while (tcell_idx != INDEX_NONE)
				{
					typedef NCsLooseCoarseGrid::NTight::FCell TightCellType;
					typedef NCsLooseCoarseGrid::NLoose::FCell LooseCellType;

					const TightCellType& TightCell = Tight.Cells[tcell_idx];
					const LooseCellType& LooseCell = Loose.Cells[TightCell.Index];

					if (LooseCellIndices.Find(TightCell.Index) == INDEX_NONE && NCsLooseCoarseGrid::FHelper::DoesRectIntersect(qrect_vec, LooseCell.RectToVector4()))
					{
						LooseCellIndices.Add(TightCell.Index);
						++Count;
					}
					tcell_idx = TightCell.Next;
				}
			}
		}

		// For each loose cell, determine what elements intersect.
		OutResultCount = 0;

		for (int32 I = Count - 1; I >= 0; --I)
		{
			typedef NCsLooseCoarseGrid::NLoose::FCell LooseCellType;

			const int32& Index			   = LooseCellIndices[I];
			const LooseCellType& LooseCell = Loose.Cells[Index];
			int32 elt_idx				   = LooseCell.Head;

			while (elt_idx != INDEX_NONE)
			{
				// If the element intersects the search rectangle, add it to the
				// resulting elements unless it has an ID that should be omitted.
				const ElementType& Element = Elements[elt_idx];

				if (Element.GetID() != OmitID && NCsLooseCoarseGrid::FHelper::DoesRectIntersect(qrect_vec, Element.ToRectAsVector4()))
				{
					OutResult.Add(Element.GetID());
					++OutResultCount;
				}

				elt_idx = Element.GetNext();
			}
			LooseCellIndices.RemoveAt(I, 1, false);
		}
	}

	void FGrid::Optimize()
	{
		// Clear all the tight cell data.
		for (int32 I = 0; I < Tight.NumCells; ++I)
			Tight.Heads[I] = -1;

		Tight.Cells.clear();

		// Optimize the memory layout of the grid.
		OptimizeMemoryLayout();

		for (int32 c = 0; c < Loose.NumCells; ++c)
		{
			// Empty the loose cell's bounding box.
			typedef NCsLooseCoarseGrid::NLoose::FCell LooseCellType;

			LooseCellType& LooseCell = Loose.Cells[c];
				
			LooseCell.InvalidateRect();

			// Expand the bounding box by each element's extents in 
			// the loose cell.
			int32 elt_idx = LooseCell.Head;

			while (elt_idx != INDEX_NONE)
			{
				const ElementType& Element = Elements[elt_idx];

				LooseCell.Rect[0] = FMath::Min(LooseCell.Rect[0], Element.CenterX - Element.HalfWidth);
				LooseCell.Rect[1] = FMath::Min(LooseCell.Rect[1], Element.CenterY - Element.HalfHeight);
				LooseCell.Rect[2] = FMath::Max(LooseCell.Rect[2], Element.CenterX + Element.HalfWidth);
				LooseCell.Rect[3] = FMath::Max(LooseCell.Rect[3], Element.CenterY + Element.HalfHeight);
				elt_idx = Element.GetNext();
			}
		}

		for (int32 c = 0; c < Loose.NumCells; ++c)
		{
			// Insert the loose cell to all the tight cells in which 
			// it now belongs.
			typedef NCsLooseCoarseGrid::NLoose::FCell LooseCellType;

			LooseCellType& LooseCell = Loose.Cells[c];
			const FIntVector4 trect  = GetCellIndex4(LooseCell.RectToVector4());

			for (int32 ty = trect.Y; ty <= trect.W; ++ty)
			{
				int32* tight_row = Tight.Heads + (ty * Tight.NumColumns);

				for (int32 tx = trect.X; tx <= trect.Z; ++tx)
				{
					typedef NCsLooseCoarseGrid::NTight::FCell TightCellType;

					const TightCellType new_tcell = {tight_row[tx], c};

					tight_row[tx] = Tight.Cells.insert(new_tcell);
				}
			}
		}
	}

	void FGrid::OptimizeMemoryLayout()
	{
		// TODO: Possibly have static array
		TempElements.clear();
		TempElements.reserve(NumElements);

		for (int32 c = 0; c < Loose.NumCells; ++c)
		{
			// Replace links to the old elements list to links in the new
			// cache-friendly element list.
			typedef NCsLooseCoarseGrid::NLoose::FCell LooseCellType;

			static TArray<int32> new_elt_idxs;
			LooseCellType& LooseCell = Loose.Cells[c];

			while (LooseCell.HasHead())
			{
				const ElementType& Element = Elements[LooseCell.Head];

				new_elt_idxs.Add(TempElements.insert(Element));

				LooseCell.Head = Element.GetNext();
			}

			const int32 Count = new_elt_idxs.Num();

			for (int32 J = Count - 1; J >= 0; --J)
			{
				const int32 new_elt_idx		   = new_elt_idxs[J];
				TempElements[new_elt_idx].Next = LooseCell.Head;
				LooseCell.Head				   = new_elt_idx;

				new_elt_idxs.RemoveAt(J, 1, false);
			}
		}
		// Swap the new element list with the old one.
		Elements.swap(TempElements);
	}

	void FGrid::Expand_AABB(const int32& CellIndex, const float& CenterX, const float& CenterY, const float& HalfWidth, const float& HalfHeight)
	{
		typedef NCsLooseCoarseGrid::NLoose::FCell LooseCellType;

		LooseCellType& LooseCell = Loose.Cells[CellIndex];
		const FVector4 prev_rect = FVector4(LooseCell.Rect[0], LooseCell.Rect[1], LooseCell.Rect[2], LooseCell.Rect[3]);

		LooseCell.Rect[0] = FMath::Min(LooseCell.Rect[0], CenterX - HalfWidth);
		LooseCell.Rect[1] = FMath::Min(LooseCell.Rect[1], CenterY - HalfHeight);
		LooseCell.Rect[2] = FMath::Max(LooseCell.Rect[2], CenterX + HalfWidth);
		LooseCell.Rect[3] = FMath::Max(LooseCell.Rect[3], CenterY + HalfHeight);

		// Determine the cells occupied by the loose cell in the tight grid.
		const FVector4 elt_rect = FVector4(CenterX - HalfWidth, CenterY - HalfHeight, CenterX + HalfWidth, CenterY + HalfHeight);
		const FIntVector4 trect = GetCellIndex4(elt_rect);

		if (prev_rect.X > prev_rect.Z)
		{
			// If the loose cell was empty, simply insert the loose cell
			// to all the tight cells it occupies. We don't need to check
			// to see if it was already inserted.
			for (int32 ty = trect.Y; ty <= trect.W; ++ty)
			{
				int32* tight_row = Tight.Heads + (ty * Tight.NumColumns);

				for (int32 tx = trect.X; tx <= trect.Z; ++tx)
				{
					typedef NCsLooseCoarseGrid::NTight::FCell TightCellType;

					const TightCellType new_tcell = {tight_row[tx], CellIndex};

					tight_row[tx] = Tight.Cells.insert(new_tcell);
				}
			}
		}
		else
		{
			// Only perform the insertion if the loose cell overlaps new tight cells.
			const FIntVector4 prev_trect = GetCellIndex4(prev_rect);

			if (trect.X != prev_trect.X || trect.Y != prev_trect.Y ||
				trect.Z != prev_trect.Z || trect.W != prev_trect.W)
			{
				for (int32 ty = trect.Y; ty <= trect.W; ++ty)
				{
					int32* tight_row = Tight.Heads + (ty * Tight.NumColumns);

					for (int32 tx = trect.X; tx <= trect.Z; ++tx)
					{
						if (tx < prev_trect.X || tx > prev_trect.Z ||
							ty < prev_trect.Y || ty > prev_trect.W)
						{
							typedef NCsLooseCoarseGrid::NTight::FCell TightCellType;

							const TightCellType new_tcell = {tight_row[tx], CellIndex};

							tight_row[tx] = Tight.Cells.insert(new_tcell);
						}
					}
				}
			}
		}
	}
}