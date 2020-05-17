
#include "QueenSpawner.h"


#include "MyGameInstance.h"
#include "Queen.h"
#include "TimerManager.h"
#include "Engine/World.h"

AQueenSpawner::AQueenSpawner()
{
	DefaultSpawnLocation.Set(200.f, 200.f, 0.0f);
	CurrentQueen = nullptr;
	PreviousQueen = nullptr;
}


void AQueenSpawner::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(SpawnTimerHandle, this, &AQueenSpawner::SpawnQueen, 1.f, false, 3.f);
}



void AQueenSpawner::CallSpawnQueen()
{
	GetWorldTimerManager().SetTimer(SpawnTimerHandle, this, &AQueenSpawner::SpawnQueen, 1.f, false, 1.5); 
}

void AQueenSpawner::QueenDestroyed(AQueen* QueenToDestroy)
{	
	QueenArray.Remove(QueenToDestroy); //Removes the last one.
	CurrentQueen = PreviousQueen;
	PreviousQueen = QueenArray.Last(1);

	QueenToDestroy->Destroy();

	CurrentQueen->MoveInRow();
}

void AQueenSpawner::SpawnQueen()
{
	FVector SpawnLocation;
	FActorSpawnParameters SpawnParameters;

	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	if (CurrentQueen == nullptr)
	{
		SpawnLocation = DefaultSpawnLocation;
		//UE_LOG(LogTemp, Warning, TEXT("SpawnLocation set for Null Current Queen"))
	}
	else
	{
		//todo should controll if the columns are over.
		/** Spawning in new Column*/
		SpawnLocation.Set(CurrentQueen->GetActorLocation().X + 400.f, 200.f, CurrentQueen->GetActorLocation().Z);
		
	}


	//UE_LOG(LogTemp, Warning, TEXT("Array Length %d"), QueenArray.Num())
	if (QueenArray.Num() > 8)
	{
		UMyGameInstance* GameInstance = Cast<UMyGameInstance>(GetGameInstance());
		if (!ensure(GameInstance != nullptr))
			return;

		GameInstance->bGameFinished = true;
		Destroy();
		return;
	}

	
	if (!ensure(QueenToSpawn != nullptr))
		return;

	Queen = GetWorld()->SpawnActor<AQueen>(QueenToSpawn, SpawnLocation, FRotator::ZeroRotator, SpawnParameters);
	if (!ensure(Queen != nullptr))
		return;

	PreviousQueen = CurrentQueen;
	CurrentQueen = Queen;
	QueenArray.Add(Queen);



	Queen->SetOwner(this);
	Queen->VerifyQueen();

}
