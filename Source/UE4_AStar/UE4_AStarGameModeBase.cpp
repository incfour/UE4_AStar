// Fill out your copyright notice in the Description page of Project Settings.

#include "UE4_AStar.h"
#include "UE4_AStarGameModeBase.h"

//AUE4_AStarGameModeBase::AUE4_AStarGameModeBase(const FObjectInitializer& ObjectInitializer)
//:Super(ObjectInitializer)
//{
//	
//}

void AUE4_AStarGameModeBase::StartPlay()
{
	for (TActorIterator<AActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		// Same as with the Object Iterator, access the subclass instance with the * or -> operators.
		AActor *Actor = *ActorItr;
		if (Actor->GetName() == TEXT("CameraActor_1"))
		{			
			UE_LOG(LogTemp, Warning, TEXT("1 : %s"), *Actor->GetName())
			break;
		}		
	}
}



