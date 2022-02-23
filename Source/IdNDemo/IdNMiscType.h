#include "IdNGameInstance.h"

#if PLATFORM_WINDOWS
#define SEND_DATA(InProtocols,...)\
if (UIdNGameInstance* InGameInstance_A = GetGameInstance<UIdNGameInstance>())\
{\
	SIMPLE_CLIENT_SEND(InGameInstance_A->GetClient(), InProtocols, __VA_ARGS__);\
}
#else
#define SEND_DATA(InProtocols,args...)\
if (UIdNGameInstance* InGameInstance_A = GetGameInstance<UIdNGameInstance>())\
{\
	SIMPLE_CLIENT_SEND(InGameInstance_A->GetClient(), InProtocols, ##args);\
}
#endif