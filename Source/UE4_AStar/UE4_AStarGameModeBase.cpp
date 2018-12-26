// Fill out your copyright notice in the Description page of Project Settings.

#include "UE4_AStar.h"
#include "UE4_AStarGameModeBase.h"
#include "Util.h"
#include "BlockBox.h"
#include "AStar_logic.h"
#include "FMainEvent.h"

AUE4_AStarGameModeBase::AUE4_AStarGameModeBase(const FObjectInitializer& ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

	AStar = CreateDefaultSubobject<UAStar_logic>(TEXT("UAStar_logic"));	
}

void AUE4_AStarGameModeBase::StartPlay()
{
	FMainEvent::MoveWayEvent.AddUObject(this, &AUE4_AStarGameModeBase::RecvEvent_MoveWay);

	Super::StartPlay();

	CameraSetting();
	InputSetting();
	EnvSetting();

	AStar->StartPlay();
}

void AUE4_AStarGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);	

	AStar->Tick(DeltaTime);
}

void AUE4_AStarGameModeBase::CameraSetting()
{	
	AActor* Actor = Util::FindActor<AActor>(GetWorld(), TEXT("CameraActor_1"));	
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
			PlayerController->InputComponent->BindAction(TEXT("C_Btn_Click"), IE_Released, this, &AUE4_AStarGameModeBase::Clear);
			PlayerController->InputComponent->BindAction(TEXT("S_Btn_Click"), IE_Released, this, &AUE4_AStarGameModeBase::StartPointSetting);
			PlayerController->InputComponent->BindAction(TEXT("G_Btn_Click"), IE_Released, this, &AUE4_AStarGameModeBase::GoalPointSetting);
			PlayerController->InputComponent->BindAction(TEXT("P_Btn_Click"), IE_Released, this, &AUE4_AStarGameModeBase::Play);
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

		BlockSize = MapSize / UAStar_logic::MAP_SELL_NUM;

		UE_LOG(LogTemp, Warning, TEXT("MapSize %d"), MapSize);
	}
}

FVector2D AUE4_AStarGameModeBase::GetHitPoint()
{
	FVector2D ret;	

	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		FHitResult HitResult;
		PlayerController->GetHitResultUnderCursor(ECC_Visibility, false, HitResult);
		if (HitResult.bBlockingHit)
		{
			ret.X = HitResult.ImpactPoint.X;
			ret.Y = HitResult.ImpactPoint.Y;
		}
	}

	return ret;
}

FVector2D AUE4_AStarGameModeBase::ConvertArrayPos(const FVector2D& HitPos)
{
	FVector2D ret;	

	float X = HitPos.X + MapSize / 2.0f;
	float Y = HitPos.Y + MapSize / 2.0f;

	ret.X = (int)(X / (float)BlockSize);
	ret.Y = (int)(Y / (float)BlockSize);

	return ret;
}

FVector2D AUE4_AStarGameModeBase::ConvertWorldSpawnPos(const FVector2D& ArrayPos)
{
	FVector2D ret;

	ret.X = ArrayPos.X * BlockSize - MapSize / 2.0f + 50.0f;
	ret.Y = ArrayPos.Y * BlockSize - MapSize / 2.0f + 50.0f;

	return ret;
}

void AUE4_AStarGameModeBase::SpawnBlock()
{
	FVector2D HitPoint = GetHitPoint();

	if (!HitPoint.IsZero())
	{
		FVector2D ArrayPoint = ConvertArrayPos(HitPoint);

		if (AStar->IsBlock(ArrayPoint.X, ArrayPoint.Y))
		{
			return;
		}

		AStar->SetBlock(ArrayPoint.X, ArrayPoint.Y);

		FVector2D WorldSpawnPoint = ConvertWorldSpawnPos(ArrayPoint);

		FActorSpawnParameters spawninfo;
		spawninfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		ABlockBox* BlockBox = GWorld->SpawnActor<ABlockBox>(FVector(WorldSpawnPoint.X , WorldSpawnPoint.Y, 0.0f), FRotator(0, 0, 0), spawninfo);

		BlockBoxArray.Emplace(BlockBox);		
	}	
}

void AUE4_AStarGameModeBase::ClearBlock()
{
	UE_LOG(LogTemp, Warning, TEXT("ClearBlock Size : %d"), BlockBoxArray.Num());

	for (auto* i : BlockBoxArray)
	{		
		GWorld->DestroyActor(i);		
	}	

	BlockBoxArray.Empty();	
}

void AUE4_AStarGameModeBase::Clear()
{
	ClearBlock();

	AStar->Reset();

	if (AStaticMeshActor* Mesh = Util::FindActor<AStaticMeshActor>(GetWorld(), TEXT("Player")))
	{
		Mesh->SetActorLocation(FVector(-350, -550, 50));
	}

	if (AStaticMeshActor* Mesh = Util::FindActor<AStaticMeshActor>(GetWorld(), TEXT("Goal")))
	{
		Mesh->SetActorLocation(FVector(-450, -550, 50));
	}
}

void AUE4_AStarGameModeBase::StartPointSetting()
{
	if (AStaticMeshActor* Mesh = Util::FindActor<AStaticMeshActor>(GetWorld(), TEXT("Player")))
	{
		FVector2D HitPoint = GetHitPoint();

		if (!HitPoint.IsZero())
		{
			FVector2D ArrayPoint = ConvertArrayPos(HitPoint);		
			FVector2D WorldSpawnPoint = ConvertWorldSpawnPos(ArrayPoint);
			FVector Loc = Mesh->GetActorLocation();

			Loc.X = WorldSpawnPoint.X;
			Loc.Y = WorldSpawnPoint.Y;

			Mesh->SetActorLocation(Loc);

			AStar->SetStartPoint(ArrayPoint.X, ArrayPoint.Y);
		}
	}	
}

void AUE4_AStarGameModeBase::GoalPointSetting()
{
	UE_LOG(LogTemp, Warning, TEXT("GoalPointSetting"));
	if (AStaticMeshActor* Mesh = Util::FindActor<AStaticMeshActor>(GetWorld(), TEXT("Goal")))
	{
		FVector2D HitPoint = GetHitPoint();

		if (!HitPoint.IsZero())
		{
			FVector2D ArrayPoint = ConvertArrayPos(HitPoint);
			FVector2D WorldSpawnPoint = ConvertWorldSpawnPos(ArrayPoint);
			FVector Loc = Mesh->GetActorLocation();

			Loc.X = WorldSpawnPoint.X;
			Loc.Y = WorldSpawnPoint.Y;

			Mesh->SetActorLocation(Loc);

			AStar->SetGoalPoint(ArrayPoint.X, ArrayPoint.Y);
		}
	}
}

void AUE4_AStarGameModeBase::Play()
{	
	AStar->Play();
}

void AUE4_AStarGameModeBase::RecvEvent_MoveWay(FVector2D Point)
{
	if (AStaticMeshActor* Mesh = Util::FindActor<AStaticMeshActor>(GetWorld(), TEXT("Player")))
	{
		FVector Loc = Mesh->GetActorLocation();
		FVector2D WorldPoint = ConvertWorldSpawnPos(Point);

		Loc.X = WorldPoint.X;
		Loc.Y = WorldPoint.Y;

		Mesh->SetActorLocation(Loc);
	}
}

