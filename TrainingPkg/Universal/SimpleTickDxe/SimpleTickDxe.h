#include <PiDxe.h>

#include <Library/PrintLib.h>
#include <Library/DebugLib.h>
#include <Library/UefiLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiDriverEntryPoint.h>

#include <Protocol/TextDrawProtocol.h>

#define SIMPLE_TICK_SIGNATURE SIGNATURE_32 ('t', 'd', 'p', 'd')

typedef struct {
  UINTN                               Signature;
  EFI_EVENT                           TimerEvent;
  UINTN                               Seconds;
  EFI_EVENT                           TickEvent;
  UINTN                               Ticks;
} SIMPLE_TICK_PRIVATE_DATA;
