
#include "Tile.h"

#include "Components/StaticMeshComponent.h"

ATile::ATile()
{
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	RootComponent = MeshComp;

}


void ATile::BeginPlay()
{
	Super::BeginPlay();
	
}


void ATile::SetTileMaterial(bool bIsLight)
{
	if (!ensure(LightMat != nullptr) && !ensure(DarkMat != nullptr))
		return;
	
	if (bIsLight)
	{
		MeshComp->SetMaterial(0, LightMat);
	}
	else
	{
		MeshComp->SetMaterial(0, DarkMat);
	}
}



