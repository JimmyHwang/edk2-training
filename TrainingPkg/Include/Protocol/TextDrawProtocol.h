#ifndef __TEXT_DRAW_H__
#define __TEXT_DRAW_H__

//
// Forward reference for pure ANSI compatability
//
typedef struct _TEXT_DRAW_PROTOCOL  TEXT_DRAW_PROTOCOL;

/**
  Draw a text rectangle on screen 

  @param  Width       Width of rectangle
  @param  Height      Height of rectangle
  @param  Character   Special character to draw

  @retval EFI_SUCCESS   Run successful

**/
typedef
EFI_STATUS
(EFIAPI *TEXT_DRAW_RECTANGLE)(
  IN  UINTN Width,
  IN  UINTN Height,
  IN  CHAR16 *Character
  );

/**
  Draw a text triangle on screen 

  @param  Height      Height of rectangle
  @param  Character   Special character to draw

  @retval EFI_SUCCESS   Run successful

**/
typedef
EFI_STATUS
(EFIAPI *TEXT_DRAW_TRIANGLE)(
  IN  UINTN Height,
  IN  CHAR16 *Character
  );

struct _TEXT_DRAW_PROTOCOL {
  TEXT_DRAW_RECTANGLE                  DrawRectangle;
  TEXT_DRAW_TRIANGLE                   DrawTriangle;
};

extern EFI_GUID gTextDrawProtocolGuid;

#endif
