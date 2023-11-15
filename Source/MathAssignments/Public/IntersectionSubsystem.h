// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IntersectionDemonstrator.h"
#include "Subsystems/WorldSubsystem.h"
#include "IntersectionSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class MATHASSIGNMENTS_API UIntersectionSubsystem : public UTickableWorldSubsystem
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<AIntersectionDemonstrator*> Demonstrators;

	UPROPERTY()
	APlayerController* PlayerControllerInstance;

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Tick(float DeltaTime) override;

	void RegisterDemonstrator(AIntersectionDemonstrator* Demonstrator);
	void UnregisterDemonstrator(AIntersectionDemonstrator* Demonstrator);

	virtual TStatId GetStatId() const override;
};
