// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "BlockBox.generated.h"

UCLASS()
class UE4_ASTAR_API ABlockBox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABlockBox();
	virtual ~ABlockBox();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	void ChangeMaterial();

protected:
	UPROPERTY()
	UMaterial* TheMaterial;	
};
