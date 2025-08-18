// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTTask_ClearBlackboardValue.h"
#include "BehaviorTree/BlackboardComponent.h"

UMyBTTask_ClearBlackboardValue::UMyBTTask_ClearBlackboardValue()
{
    NodeName = TEXT("Clear Blackboard Value");
}
EBTNodeResult::Type UMyBTTask_ClearBlackboardValue::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory); // Call the parent class's ExecuteTask method

    OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey()); // Clear the value of the selected blackboard key

    return EBTNodeResult::Succeeded; 
}