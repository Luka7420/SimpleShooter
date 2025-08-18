// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAiController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

void AShooterAiController::BeginPlay()
{
    Super::BeginPlay();

    if(AIBehavior != nullptr)
    {
        RunBehaviorTree(AIBehavior); 

        APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

        
         //Set a start location for the AI
        GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());
        
    }
   
}
void AShooterAiController::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    
    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0); // Get the first player pawn
    if (LineOfSightTo(PlayerPawn))
    {
        // Set the player's location in the blackboard
        GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), PlayerPawn->GetActorLocation());
        // Set the last known player location
        GetBlackboardComponent()->SetValueAsVector(TEXT("LastKnownPlayerLocation"), PlayerPawn->GetActorLocation());
    }
    else
    {
        //clear player location
        GetBlackboardComponent()->ClearValue(TEXT("PlayerLocation"));
    }
}