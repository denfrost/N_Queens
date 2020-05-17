// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Queen.generated.h"

UCLASS()
class N_QUEENS_API AQueen : public APawn
{
	GENERATED_BODY()

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UStaticMeshComponent* MeshComp;

	bool bIsSafe;
	
	uint8 MoveCount;

	UPROPERTY()
	FVector NewLocation;
	
public:
	
	AQueen();

	bool TraceInEveryDirection()const;

	void VerifyQueen();

	void MoveInRow();
	
protected:
	
	virtual void BeginPlay() override;




};
