// Fill out your copyright notice in the Description page of Project Settings.

#include "UE4_AStar.h"
#include "BlockBox.h"


// Sets default values
ABlockBox::ABlockBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	UStaticMeshComponent* Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ABlockBoxMesh"));
	RootComponent = Mesh;
	//Mesh->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> BoxAsset(TEXT("StaticMesh'/Game/Shape_Cube.Shape_Cube'"));
	if (BoxAsset.Succeeded())
	{		
		Mesh->SetStaticMesh(BoxAsset.Object);
		/*SphereVisual->SetRelativeLocation(FVector(0.0f, 0.0f, 40.0f));
		SphereVisual->SetWorldScale3D(FVector(0.8f));*/			
	}

	static ConstructorHelpers::FObjectFinder<UMaterial>	Material (TEXT("Material'/Game/Material/Cube_mat.Cube_mat'"));
	Mesh->SetMaterial(0, Material.Object);	
}

ABlockBox::~ABlockBox()
{
	int a = 0;
}

// Called when the game starts or when spawned
void ABlockBox::BeginPlay()
{
	Super::BeginPlay();	
}

// Called every frame
void ABlockBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

