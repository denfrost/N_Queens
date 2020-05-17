 // Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "QueenSpawner.generated.h"

UCLASS()
class N_QUEENS_API AQueenSpawner : public AActor
{
	GENERATED_BODY()

protected:
	
	UPROPERTY(VisibleAnywhere, Category = "Queen")
	class AQueen* CurrentQueen;
	
	UPROPERTY(VisibleAnywhere, Category = "Queen")
	class AQueen* PreviousQueen;

	UPROPERTY(VisibleAnywhere, Category = "Queen")
	TArray<AQueen*> QueenArray;
	
	
private:
	UPROPERTY(VisibleAnywhere, Category = "Queen", meta = (PrivateAccess = "True"))
	class AQueen* Queen;

	UPROPERTY(EditDefaultsOnly, Category = "Queen", meta = (PrivateAccess = "True"))
	TSubclassOf <AQueen> QueenToSpawn;

	FVector DefaultSpawnLocation;

	FTimerHandle SpawnTimerHandle;
	
	
public:	
	AQueenSpawner();
	
	void CallSpawnQueen();

	void QueenDestroyed(AQueen* QueenToDestroy);
	
protected:
	virtual void BeginPlay() override;

	void SpawnQueen();
};

 