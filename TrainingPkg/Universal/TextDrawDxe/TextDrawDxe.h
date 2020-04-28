#include <PiDxe.h>

#include <Library/PrintLib.h>
#include <Library/DebugLib.h>
#include <Library/UefiLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiDriverEntryPoint.h>

#include <Protocol/TextDrawProtocol.h>

#define TEXT_DRAW_SIGNATURE SIGNATURE_32 ('t', 'd', 'p', 'd')

typedef struct {
  UINTN                               Signature;
  EFI_EVENT                           TimerEvent;
  UINTN                               Ticks;
} TEXT_DRAW_EVENT_DATA;
