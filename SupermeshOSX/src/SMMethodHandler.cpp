#include "SMMethodHandler.h"
#include <Awesomium/STLHelpers.h>
#include "SMApplication.h"

void SMMethodHandler::OnMethodCall(Awesomium::WebView* caller,
                              unsigned int remote_object_id,
                              const Awesomium::WebString& method_name,
                              const Awesomium::JSArray& args) {
    
    if (method_name.Compare(Awesomium::WSLit("message")) == 0) {
        Awesomium::JSValue msgVal = args.At(0);
        Awesomium::WebString msgStr = msgVal.ToString();
        
        char* msgStrPtr = SMWebStrToUTF8(msgStr);
        SMMessageBox(msgStrPtr, APP_NAME, MB_OK);
        free(msgStrPtr);
    }
    
}

Awesomium::JSValue SMMethodHandler::OnMethodCallWithReturnValue(Awesomium::WebView* caller,
                                               unsigned int remote_object_id,
                                               const Awesomium::WebString& method_name,
                                               const Awesomium::JSArray& args) {
    return Awesomium::JSValue();
}