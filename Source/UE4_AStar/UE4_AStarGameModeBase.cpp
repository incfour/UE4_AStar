// Fill out your copyright notice in the Description page of Project Settings.

#include "UE4_AStar.h"
#include "UE4_AStarGameModeBase.h"
#include "Util.h"
#include "BlockBox.h"

//AUE4_AStarGameModeBase::AUE4_AStarGameModeBase(const FObjectInitializer& ObjectInitializer)
//:Super(ObjectInitializer)
//{
//	
//}

void AUE4_AStarGameModeBase::StartPlay()
{
	Super::StartPlay();

	CameraSetting();
	InputSetting();
	EnvSetting();
}

void AUE4_AStarGameModeBase::CameraSetting()
{
	AActor* Actor = Util::FindActor<AActor>(GetWorld(), TEXT("CameraActor_1"));
	//AActor* Actor = Util::FindActor<AActor>(GetWorld(), TEXT("CameraActor2_3"));
	if (Actor)
	{		
		
		if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
		{
			PlayerController->SetViewTargetWithBlend(Actor);
			PlayerController->bShowMouseCursor = true;
			PlayerController->bEnableClickEvents = true;			
		}		
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AUE4_AStarGameModeBase::CameraSetting Actor is nullptr"));
	}
}

void AUE4_AStarGameModeBase::InputSetting()
{
	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		if (PlayerController->InputComponent)
		{		
			PlayerController->InputComponent->BindAction(TEXT("LMouseClick"), IE_Released, this, &AUE4_AStarGameModeBase::LMouseClick);
		}		
	}
}

void AUE4_AStarGameModeBase::LMouseClick()
{
	UE_LOG(LogTemp, Warning, TEXT("LMouseClick"));

	SpawnBlock();
}

void AUE4_AStarGameModeBase::EnvSetting()
{	
	if (AStaticMeshActor* Mesh = Util::FindActor<AStaticMeshActor>(GetWorld(), TEXT("Floor")))
	{
		const FBox Bounds = Mesh->GetComponentsBoundingBox(false);
		MapSize = FMath::Abs(Bounds.Max.X - Bounds.Min.X);
		//FVector Origin;
		//FVector BoxExtent;
		//Mesh->GetActorBounds(true, Origin, BoxExtent);		

		////FVector Location = Mesh->GetActorLocation();		
		//MapSize = BoxExtent.X;

		BlockSize = MapSize / MapSellCount;		

		UE_LOG(LogTemp, Warning, TEXT("MapSize %d"), MapSize);
	}
}

void AUE4_AStarGameModeBase::SpawnBlock()
{
	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		FHitResult HitResult;
		PlayerController->GetHitResultUnderCursor(ECC_Visibility, false, HitResult);
		if (HitResult.bBlockingHit)
		{
			float X = HitResult.ImpactPoint.X + MapSize / 2.0f;
			float Y = HitResult.ImpactPoint.Y + MapSize / 2.0f;

			int ArrayX = (int)(X / (float)BlockSize);
			int ArrayY = (int)(Y / (float)BlockSize);

			FActorSpawnParameters spawninfo;// = FActorSpawnParameters();
			spawninfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			GWorld->SpawnActor<ABlockBox>(FVector(ArrayX * BlockSize - MapSize / 2.0f + 50.0f
				, ArrayY * BlockSize - MapSize / 2.0f + 50.0f, 0.0f), FRotator(0, 0, 0), spawninfo);

			//UE_LOG(LogTemp, Warning, TEXT("hit %f %f"), X, Y);
			UE_LOG(LogTemp, Warning, TEXT("hit %d %d"), ArrayX, ArrayY);
		}
	}
}



