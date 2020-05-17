
#include "Queen.h"

#include "DrawDebugHelpers.h"
#include "QueenSpawner.h"
#include "TimerManager.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"

AQueen::AQueen()
{
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	RootComponent = MeshComp;

	MoveCount = 0;
}


void AQueen::BeginPlay()
{
	Super::BeginPlay();

	TraceInEveryDirection();
}


bool AQueen::TraceInEveryDirection()const
{
	UWorld* World = GetWorld();
	if (!ensure(World != nullptr))
		return false;;

	FHitResult HitResult;
	FVector StartLocation;
	FVector EndLocation;
	FCollisionObjectQueryParams ObjectQueryParams;
	FCollisionQueryParams CollisionQueryParams;

	ObjectQueryParams.AddObjectTypesToQuery(ECollisionChannel::ECC_GameTraceChannel1);
	CollisionQueryParams.AddIgnoredActor(this);

	StartLocation.Set(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z + 50.f);

	auto name = ECollisionChannel::ECC_EngineTraceChannel1;

	//UE_LOG(LogTemp, Warning, TEXT("Channel 1 : %s"), )

	for (size_t i = 0; i < 8; ++i)
	{
		switch (i)
		{
		case 0:
			EndLocation.Set(StartLocation.X + 3200.f, StartLocation.Y, StartLocation.Z);
			break;
		case 1:
			EndLocation.Set(StartLocation.X - 3200.f, StartLocation.Y, StartLocation.Z);
			break;
		case 2:
			EndLocation.Set(StartLocation.X, StartLocation.Y + 3200.f, StartLocation.Z);
			break;
		case 3:
			EndLocation.Set(StartLocation.X, StartLocation.Y - 3200.f, StartLocation.Z);
			break;
		case 4:
			EndLocation.Set(StartLocation.X + 3200.f, StartLocation.Y + 3200.f, StartLocation.Z);
			break;
		case 5:
			EndLocation.Set(StartLocation.X + 3200.f, StartLocation.Y - 3200.f, StartLocation.Z);
			break;
		case 6:
			EndLocation.Set(StartLocation.X - 3200.f, StartLocation.Y + 3200.f, StartLocation.Z);
			break;
		case 7:
			EndLocation.Set(StartLocation.X - 3200.f, StartLocation.Y - 3200.f, StartLocation.Z);
			break;
		}

		DrawDebugLine(World, StartLocation, EndLocation, FColor::Blue, false, 1.f, 0, 10.f);

	
		if (World->LineTraceSingleByObjectType(HitResult, StartLocation, EndLocation, ObjectQueryParams, CollisionQueryParams))
		{
			//UE_LOG(LogTemp, Warning, TEXT("HitResult : %s"), *HitResult.GetActor()->GetName())
			return false;
		}
	}

	return true;
}

void AQueen::VerifyQueen()
{
	
	bIsSafe = TraceInEveryDirection();

	//UE_LOG(LogTemp, Warning, TEXT("bIsSafe %i"), bIsSafe)
	
	AQueenSpawner* Owner_ = Cast<AQueenSpawner>(GetOwner());
	if (!ensure(Owner_ != nullptr))
		return;
	
	if (bIsSafe)
	{
		Owner_->CallSpawnQueen();
	}
	else
	{
		/** then move in Row by 400. */
		FTimerHandle SpawnTimerHandle;
		GetWorldTimerManager().SetTimer(SpawnTimerHandle, this, &AQueen::MoveInRow, 1.f, false, 1.f);
	}
}


void AQueen::MoveInRow()
{
	++MoveCount;
	if (MoveCount >= 8)
	{
		//This Object should be destroyed
		AQueenSpawner* Owner_ = Cast<AQueenSpawner>(GetOwner());
		if (!ensure(Owner_ != nullptr))
			return;

		Owner_->QueenDestroyed(this);
		return;     
	}

	NewLocation = FVector(GetActorLocation().X, GetActorLocation().Y + 400, GetActorLocation().Z);

	SetActorLocation(NewLocation);
	
	VerifyQueen();
}


