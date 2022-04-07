
#pragma once

#include "../GameInfo.h"
#include "Components/ActorComponent.h"
#include "MessageComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECT1_API UMessageComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UMessageComponent();
	virtual ~UMessageComponent() override;

private:
	class Dispatcher* m_Dispatcher;
	
protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
