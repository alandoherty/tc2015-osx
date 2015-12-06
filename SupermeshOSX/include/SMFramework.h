#ifndef SMFramework_h
#define SMFramework_h

//------------------------------------------------------------------------
// Basic includes
//------------------------------------------------------------------------
#include <cstdint>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <unistd.h>


//------------------------------------------------------------------------
// Basic defines
//------------------------------------------------------------------------
#define APP_NAME "Supermesh"
#define APP_WIDTH 1440
#define APP_HEIGHT 900

//------------------------------------------------------------------------
// Basic types
//------------------------------------------------------------------------
typedef int16_t SMInt16;
typedef int32_t SMInt32;
typedef int64_t SMInt64;
typedef uint16_t SMUInt16;
typedef uint32_t SMUInt32;
typedef uint64_t SMUInt64;
typedef bool SMBool;

//------------------------------------------------------------------------
// Basic includes
//------------------------------------------------------------------------
#include <Awesomium/WebCore.h>
#include <Awesomium/STLHelpers.h>

//------------------------------------------------------------------------
// Message boxes.
//------------------------------------------------------------------------
#define MB_OK 0
#define MB_ERROR 1
SMInt32 SMMessageBox(const char* msg, const char* caption, SMInt32 mbFlags);

//------------------------------------------------------------------------
// Converts and allocates a WebString into an UTF-8
// You must free(ptr) when done.
//------------------------------------------------------------------------
char* SMWebStrToUTF8(Awesomium::WebString& str);



#endif
