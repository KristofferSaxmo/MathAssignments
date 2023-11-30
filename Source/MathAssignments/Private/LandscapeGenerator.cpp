// Fill out your copyright notice in the Description page of Project Settings.


#include "LandscapeGenerator.h"
#include "ProceduralMeshComponent.h"

// Sets default values
ALandscapeGenerator::ALandscapeGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ProceduralMesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("ProceduralMesh"));
	ProceduralMesh->SetupAttachment(RootComponent);
	ProceduralMesh->bUseAsyncCooking = true;
	RootComponent = ProceduralMesh;
}

// Called when the game starts or when spawned
void ALandscapeGenerator::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALandscapeGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	GenerateMesh();

	PrimaryActorTick.bCanEverTick = false;
}

void ALandscapeGenerator::GenerateMesh()
{
	Vertices.Empty();
	Triangles.Empty();
	Normals.Empty();
	UVs.Empty();
	Tangents.Empty();

	NoiseScale = FMath::RandRange(0.01f, 0.1f);
	
	for (int32 X = 0; X < GridSize; X++)
	{
		for (int32 Y = 0; Y < GridSize; Y++)
		{
			float Z = FMath::PerlinNoise2D(FVector2D(X * NoiseScale, Y * NoiseScale)) * Scale;
			Vertices.Add(FVector(X * 10, Y * 10, Z));
			UVs.Add(FVector2D(X, Y));
		}
	}

	for (int32 X = 0; X < GridSize - 1; X++)
	{
		for (int32 Y = 0; Y < GridSize - 1; Y++)
		{
			int32 VertexIndex = X * GridSize + Y;

			Triangles.Add(VertexIndex);
			Triangles.Add(VertexIndex + 1);
			Triangles.Add(VertexIndex + GridSize);
			Triangles.Add(VertexIndex + 1);
			Triangles.Add(VertexIndex + GridSize + 1);
			Triangles.Add(VertexIndex + GridSize);
		}
	}

	ProceduralMesh->ClearAllMeshSections();

	ProceduralMesh->CreateMeshSection_LinearColor(0, Vertices, Triangles, Normals, UVs, TArray<FLinearColor>(), Tangents, false);
}


bool ALandscapeGenerator::ShouldTickIfViewportsOnly() const
{
	return Super::ShouldTickIfViewportsOnly();
}

void ALandscapeGenerator::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	GenerateMesh();
	
	Super::PostEditChangeProperty(PropertyChangedEvent);
}