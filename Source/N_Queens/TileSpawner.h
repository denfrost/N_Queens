// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TileSpawner.generated.h"

UCLASS()
class N_QUEENS_API ATileSpawner : public AActor
{
	GENERATED_BODY()



protected:

	uint8 BoardSize;

	uint8 CurrentColumn; 
	uint8 CurrentRow;

	uint16 TileSize;

	UPROPERTY()
	FVector StartTileLocation;
	
	UPROPERTY()
	FRotator DefaultTileRotation;

private:

	UPROPERTY(VisibleAnywhere, Category = "Tile", meta = (PrivateAccess = "True"))
	class ATile* Tile;

	UPROPERTY(EditDefaultsOnly, Category = "Tile", meta = (PrivateAccess = "True"))
	TSubclassOf<ATile> TileToSpawn;

	
public:	

	ATileSpawner();

protected:

	virtual void BeginPlay() override;

};
