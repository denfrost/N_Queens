
#include "TileSpawner.h"
#include "Tile.h"

#include "Engine/World.h"


ATileSpawner::ATileSpawner()
{
	BoardSize = 8;
	TileSize = 400.f;
	
	CurrentColumn = 0;
	CurrentRow = 0;

	StartTileLocation.Set(0.0, 0.0, 0.0);
	DefaultTileRotation = FRotator(0.0, 0.0, 0.0);
}


void ATileSpawner::BeginPlay()
{
	Super::BeginPlay();

	UWorld* World = GetWorld();
	if(!ensure(World != nullptr))
		return;

	FActorSpawnParameters Parameters;
	
	for (size_t i = 0; i < BoardSize; ++i) // Row
	{
		for (size_t j = 0; j < BoardSize; ++j) //Column
		{
			/** Setting The Location of Spawning Tile To Make A ChessBoard */
			StartTileLocation.Set(j * TileSize, i * TileSize, 0.f);

			/** Spawning The Tiles To World */
			Tile = World->SpawnActor<ATile>(TileToSpawn->GetDefaultObject()->GetClass(), StartTileLocation, DefaultTileRotation, Parameters);
			
			if(!ensure(Tile != nullptr))
				return;

			Tile->TileInfo.RowNumber = i;
			Tile->TileInfo.ColumnNumber = j;

			/** if j is even then material is light*/
			if ((j+i) % 2 == 0)
			{
				Tile->SetTileMaterial(true);
			}
			else
			{
				Tile->SetTileMaterial(false);
			}
		}
	}
}


