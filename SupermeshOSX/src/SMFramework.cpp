#include "SMFramework.h"
#include <CoreFoundation/CoreFoundation.h>

SMInt32 SMMessageBox(const char* msg, const char* caption, SMInt32 mbFlags) {
    CFStringRef header_ref = CFStringCreateWithCString( NULL, caption, static_cast<SMUInt32>(strlen(caption)));
    CFStringRef message_ref  = CFStringCreateWithCString(NULL, msg, static_cast<SMUInt32>(strlen(msg)));
    
    CFOptionFlags result;
    CFUserNotificationDisplayAlert(0, (mbFlags == MB_ERROR) ? kCFUserNotificationCautionAlertLevel : kCFUserNotificationPlainAlertLevel,
                                   NULL, NULL, NULL, header_ref, message_ref,
                                   NULL, NULL, NULL, &result);
    
    CFRelease( header_ref );
    CFRelease( message_ref );
    
    if( result == kCFUserNotificationDefaultResponse )
        return 0;
    else
        return 1;
}

char* SMWebStrToUTF8(Awesomium::WebString& str) {
    SMUInt32 size = str.ToUTF8(NULL, 0);
    char* ptr = (char*)malloc(size + 1);
    ptr[size] = '\0';
    str.ToUTF8(ptr, size);
    return ptr;
}