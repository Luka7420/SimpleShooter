// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_Shoot.h"
#include "AIController.h"
#include "ShooterCharacter.h"

UBTTaskNode_Shoot::UBTTaskNode_Shoot()
{
    NodeName = TEXT("Shoot");
}
EBTNodeResult::Type UBTTaskNode_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory); 
    //call shoot method
    if(OwnerComp.GetAIOwner() == nullptr)
    {
        return EBTNodeResult::Failed;
    }
    AShooterCharacter* Character = Cast<AShooterCharacter>(OwnerComp.GetAIOwner()->GetPawn());
    if(Character == nullptr)
    {
        return EBTNodeResult::Failed;
    }
    
    Character->Shoot(); // Call the Shoot method on the character

    return EBTNodeResult::Succeeded; 

}