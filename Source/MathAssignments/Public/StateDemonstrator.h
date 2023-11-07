// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StateDemonstrator.generated.h"

UCLASS()
class MATHASSIGNMENTS_API AStateDemonstrator : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AStateDemonstrator();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual bool ShouldTickIfViewportsOnly() const override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Base")
	UStaticMeshComponent* StaticMeshComponent;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="State", meta=(UIMin=0,UIMax=100))
	float Health;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Context", Meta = (Bitmask, BitmaskEnum = "/Script/MathAssignments.ERelativeContext"))
	int32 ContextFlags;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Context")
	TArray<AActor*> Demonstrators;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Context")
	bool DrawArc;
};