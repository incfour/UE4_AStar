// Fill out your copyright notice in the Description page of Project Settings.

#include "UE4_AStar.h"
#include "UE4_AStarGameModeBase.h"
#include "Util.h"

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
}

void AUE4_AStarGameModeBase::CameraSetting()
{
	AActor* Actor = Util::FindActor(GetWorld(), TEXT("CameraActor_1"));
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
}



