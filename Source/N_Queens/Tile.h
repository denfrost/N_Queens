// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"


USTRUCT(BlueprintType)
struct FTileInfo
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere)
	uint8 ColumnNumber;

	UPROPERTY(VisibleAnywhere)
	uint8 RowNumber;
	
};


UCLASS()
class N_QUEENS_API ATile : public AActor
{
	GENERATED_BODY()

public:
	FTileInfo TileInfo;
	
protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Material")
	class UMaterialInterface* LightMat;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Material")
	class UMaterialInterface* DarkMat;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UStaticMeshComponent* MeshComp;

public:	

	ATile();

	void SetTileMaterial(bool bIsLight);
	

protected:
	virtual void BeginPlay() override;


};
