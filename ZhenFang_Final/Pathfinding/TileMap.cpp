#include "TileMap.h"
#include <ImGui/Inc/imgui.h>

TileMap::~TileMap()
{
	delete[] mMap;
	mMap = nullptr;
}

void TileMap::LoadMap(const char* fileName)
{
	FILE* file = nullptr;
	fopen_s(&file, fileName, "r");
	if (file)
	{
		fscanf_s(file, "Columns: %d\n", &mColumns);
		fscanf_s(file, "Rows: %d\n", &mRows);


		delete[] mMap;
		int n = mColumns * mRows;
		mMap = new int[n];
		for (int y = 0; y < mRows; ++y)
		{
			for (int x = 0; x < mColumns; ++x)
			{
				const int index = GetIndex(x, y, mColumns);

				mMap[index] = fgetc(file) - '0';

			}
			fgetc(file);

		}
		fclose(file);
	}

}

void TileMap::SaveMap(const char* fileName)
{
	// TODO:
	// This is basically the opposite of LoadMap, but use fprintf_s instead.
	FILE* file = nullptr;
	fopen_s(&file, fileName, "w");
	if (file)
	{
		fprintf_s(file, "Columns: %d\n", mColumns);
		fprintf_s(file, "Rows: %d\n", mRows);

		for (int y = 0; y < mRows; ++y)
		{
			for (int x = 0; x < mColumns; ++x)
			{
				const int index = GetIndex(x, y, mColumns);

				fprintf_s(file, "%d", mMap[index]);


			}
			fprintf_s(file, "\n");

		}
		fclose(file);
	}
}

void TileMap::LoadTiles(const char* fileName)
{
	// Clear the old set
	mTileSet.clear();

	// TODO:
	// Update the code to load from file
	FILE* file = nullptr;
	errno_t err = fopen_s(&file, fileName, "r");
	if (err == 0 && file)
	{
		int count = 0;
		fscanf_s(file, "TileCount: %d\n", &count);
		mTileSet.resize(count);
		for (int i = 0; i < count; ++i)
		{
			char buffer[256];
			fscanf_s(file, "%s\n", buffer, static_cast<int>(std::size(buffer)));

			mTileSet[i] = X::LoadTexture(buffer);
		}
		fclose(file);
		// TEMP: Hardcoding these for now

		// Assume all the tiles are the same size
		mTileWidth = X::GetSpriteWidth(mTileSet.front());
		mTileHeight = X::GetSpriteHeight(mTileSet.front());
	}
}

void TileMap::Resize(int columns, int rows)
{
	// If the dimension is the same, nothing to do!
	if (columns == mColumns && rows == mRows)
		return;

	// If the inputs are invalid, cannot proceed.
	if (columns <= 0 || rows <= 0)
		return;

	// Allocate a new map with the given dimensions
	int n = columns * rows;
	int* newMap = new int[n];

	// TODO:
	// Use a nested for loop to copy existing data to the new map
	// *Warning* you need to be aware of the dimensions of both arrays!
	if ((columns >= mColumns && rows >= mRows) || (columns <= mColumns && rows <= mRows))
	{
		for (int r = 0; r < rows; ++r)
		{
			for (int c = 0; c < columns; ++c)
			{
				const int index = GetIndex(c, r, columns);
				const int oldindex = GetIndex(c, r, mColumns);
				const int oldsize = mColumns * mRows - 1;
				if (index <= oldsize)
				{
					newMap[index] = mMap[oldindex];
				}
				else
				{
					newMap[index] = 0;
				}


			}
		}

	}
	else if (columns > mColumns && rows < mRows)
	{
		for (int r = 0; r < rows; ++r)
		{
			for (int c = 0; c < mColumns; ++c)
			{
				const int index = GetIndex(c, r, columns);
				const int oldindex = GetIndex(c, r, mColumns);


				newMap[index] = mMap[oldindex];



			}
			for (int c = mColumns; c < columns; ++c)
			{
				const int index = GetIndex(c, r, columns);
				newMap[index] = 0;

			}
		}

	}
	else if (columns <= mColumns && rows >= mRows)
	{
		for (int r = 0; r < mRows; ++r)
		{
			for (int c = 0; c < columns; ++c)
			{
				const int index = GetIndex(c, r, columns);
				const int oldindex = GetIndex(c, r, mColumns);

					newMap[index] = mMap[oldindex];


			}

		}
		for (int r = mRows; r < rows; ++r)
		{
			for (int c = 0; c < columns; ++c)
			{
				const int index = GetIndex(c, r, columns);
				newMap[index] = 0;

			}
		}

	}

	// TEMP:
	// This clears the map to 0
	//for (int r = 0; r < rows; ++r)
	//{
	//	for (int c = 0; c < columns; ++c)
	//	{
	//		const int index = GetIndex(c, r, columns);
	//		newMap[index] = 0;
	//	}
	//}

	mColumns = columns;
	mRows = rows;
	delete[] mMap;
	mMap = newMap;
}

void TileMap::Update()
{
	if (X::IsMouseDown(X::Mouse::LBUTTON))
	{
		const int mouseX = X::GetMouseScreenX();
		const int mouseY = X::GetMouseScreenY();
		const int column = mouseX / mTileWidth;
		const int row = mouseY / mTileHeight;

		const int index = GetIndex(column, row, mColumns);
		mMap[index] = mSelectedTile;
	}

}

void TileMap::Render()
{
	// TODO:
	// Finish this part using double for-loop
	for (int y = 0; y < mRows; ++y)
	{
		for (int x = 0; x < mColumns; ++x)
		{
			const int mapindex = GetIndex(x, y, mColumns);
			const int tileIndex = mMap[mapindex];

			const X::TextureId textureId = mTileSet[tileIndex];

			const X::Math::Vector2 worldPosition = { static_cast<float>(x * mTileWidth),static_cast<float>(y * mTileHeight )};


			X::DrawSprite(textureId, worldPosition, X::Pivot::TopLeft);
		}
	}

}

void TileMap::ShowDebugUI()
{
	ImGui::Begin("Map Editor", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

	if (ImGui::Button("Load Map"))
	{
		char fileName[MAX_PATH] = {};
		if (X::OpenFileDialog(fileName, "Load Map", "Map Files (*.txt)\0*.txt"))
			LoadMap(fileName);
	}
	if (ImGui::Button("Save Map"))
	{
		char fileName[MAX_PATH] = {};
		if (X::SaveFileDialog(fileName, "Save Map", "Map Files (*.txt)\0*.txt"))
			SaveMap(fileName);
	}

	static int columns = mColumns;
	static int rows = mRows;
	ImGui::SliderInt("Columns", &columns, 5, 50);
	ImGui::SliderInt("Rows", &rows, 5, 50);
	if (ImGui::Button("Resize Map"))
		Resize(columns, rows);

	for (int i = 0; i < (int)mTileSet.size(); ++i)
	{
		if (ImGui::ImageButton(X::GetSprite(mTileSet[i]), { (float)mTileWidth, (float)mTileHeight }))
			mSelectedTile = i;
		if (i + 1 < (int)mTileSet.size())
			ImGui::SameLine();
	}

	ImGui::End();
}

bool TileMap::IsBlocked(int column, int row) 
{
	const int mapindex = GetIndex(column, row, mColumns);
	const int tileIndex = mMap[mapindex];
	if (tileIndex > 1)
	{
		return true;
	}

	return false;
}

float TileMap::GetTraversalCost(int fromColumn, int fromRow, int toColumn, int toRow) const
{
	const int frommapindex = GetIndex(fromColumn, fromRow, mColumns);
	const int fromtileIndex = mMap[frommapindex];

	const int tomapindex = GetIndex(toColumn, toRow, mColumns);
	const int totileIndex = mMap[tomapindex];

	float horizontial = abs(toColumn - fromColumn);
	float vertical = abs(toRow - fromRow);
	float distance = horizontial + vertical;
	if (distance == 2)
		distance = 1.414f;		// sqrt（2）

	int tilecost[7][7] = { 0 };
	tilecost[0][1] = 3;
	tilecost[1][0] = 1;


	//     from
	// to [_][_][_][_][_]
	//    [_][_][_][_][_]
	//    [_][_][_][_][_]
	//    [_][_][_][_][_]
	//    [_][_][_][_][_]

	return static_cast<float>(distance + tilecost[fromtileIndex][totileIndex]);
}

float TileMap::GetEstimatedDistanceManhattan(int fromColumn, int fromRow, int endColumn, int endRow) const
{
	float dx = abs(endColumn - fromColumn);
	float dy = abs(endRow - fromRow);
	float distance = dx + dy;
	return distance;
}
float TileMap::GetEstimatedDistanceEuclidean(int fromColumn, int fromRow, int endColumn, int endRow) const
{
	float dx = abs(endColumn - fromColumn);
	float dy = abs(endRow - fromRow);

	return sqrt(dx * dx + dy * dy);
}
float TileMap::GetEstimatedDistanceDiagonal(int fromColumn, int fromRow, int endColumn, int endRow) const
{
	float dx = abs(endColumn - fromColumn);
	float dy = abs(endRow - fromRow);
	float distance = dx + dy;
	float mindistance = dx < dy ? dx : dy;
	return distance + (1.414f - 2.0f) * mindistance;
}
int TileMap::GetIndex(int column, int row, int columnCount) const
{
	return column + (row * columnCount);
}