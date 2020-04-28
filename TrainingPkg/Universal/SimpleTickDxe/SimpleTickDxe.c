#include "SimpleTickDxe.h"

SIMPLE_TICK_PRIVATE_DATA  *mSimpleTickData;

//-----------------------------------------------------------------------------
// Tick Events
//-----------------------------------------------------------------------------
VOID
EFIAPI
SimpleTickEventHandler (
  IN EFI_EVENT Event,
  IN VOID      *Context
  )
{
  SIMPLE_TICK_PRIVATE_DATA *SimpleTickData;

  SimpleTickData = (SIMPLE_TICK_PRIVATE_DATA *) Context;
  SimpleTickData->Ticks++;
  //DEBUG ((EFI_D_ERROR, "Info: SimpleTickEventHandler, Ticks=%d\n", SimpleTickData->Ticks));
}

VOID 
CreateSimpleTickEvent (
  ) 
{
  //
  // Create simple tick event
  //
  gBS->CreateEventEx (
                  EVT_NOTIFY_SIGNAL,
                  TPL_NOTIFY,
                  SimpleTickEventHandler,
                  mSimpleTickData,                // Context
                  &gSimpleTickEventGuid,
                  &mSimpleTickData->TickEvent
                  );
}

//-----------------------------------------------------------------------------
// Timer Events
//-----------------------------------------------------------------------------
/**
  Event notification function for TimerEvent event.
  If mouse device is connected to system, try to get the mouse packet data.

  @param Event      -  TimerEvent in PS2_MOUSE_DEV
  @param Context    -  Pointer to PS2_MOUSE_DEV structure

**/
VOID
EFIAPI
SimpleTickTimerHandler (
  IN EFI_EVENT  Event,
  IN VOID       *Context
  )
{
  SIMPLE_TICK_PRIVATE_DATA *SimpleTickData;

  // DEBUG((EFI_D_ERROR, "."));
  SimpleTickData = (SIMPLE_TICK_PRIVATE_DATA *) Context;
  SimpleTickData->Seconds++;
  //
  // Trigger tick event per second
  //
  if ((SimpleTickData->Seconds % 3) == 0) {
    gBS->SignalEvent (SimpleTickData->TickEvent);
  }
}

VOID 
CreateTimerEvent (
  ) 
{
  EFI_STATUS Status;
  
  //
  // Allocate private data
  //
  mSimpleTickData = AllocateZeroPool (sizeof (SIMPLE_TICK_PRIVATE_DATA));
  if (mSimpleTickData == NULL) {
    Status = EFI_OUT_OF_RESOURCES;
    goto ErrorExit;
  }
  //
  // Setup the device instance
  //
  mSimpleTickData->Signature       = SIMPLE_TICK_SIGNATURE;
  mSimpleTickData->Seconds         = 0;
  mSimpleTickData->Ticks           = 0;
  //
  // Setup a periodic timer, used to poll mouse state
  //
  Status = gBS->CreateEvent (
                  EVT_TIMER | EVT_NOTIFY_SIGNAL,
                  TPL_NOTIFY,
                  SimpleTickTimerHandler,
                  mSimpleTickData,              // Context
                  &mSimpleTickData->TimerEvent  // Event Handle
                  );
  if (EFI_ERROR (Status)) {
    Status = EFI_OUT_OF_RESOURCES;
    goto ErrorExit;
  }
  //
  // Start timer (per second)
  //
  Status = gBS->SetTimer (mSimpleTickData->TimerEvent, TimerPeriodic, 10000000);
  if (EFI_ERROR (Status)) {
    Status = EFI_OUT_OF_RESOURCES;
    goto ErrorExit;
  }

ErrorExit:
  return;
}

//-----------------------------------------------------------------------------
// EntryPoint
//-----------------------------------------------------------------------------
/**
  The user Entry Point for simple tick module.

  @param[in] ImageHandle    The firmware allocated handle for the EFI image.
  @param[in] SystemTable    A pointer to the EFI System Table.

  @retval EFI_SUCCESS       The entry point is executed successfully.
  @retval Others            Some error occurs when executing this entry point.

**/
EFI_STATUS
EFIAPI
SimpleTickDxeEntryPoint (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  )
{
  EFI_STATUS  Status;

  Status = EFI_SUCCESS;
  
  CreateTimerEvent();           // for 1 second
  CreateSimpleTickEvent();      // Trigger tick event per 3 second
  
  return Status;
}
