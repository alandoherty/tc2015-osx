#include "SMMethodHandler.h"
#include <Awesomium/STLHelpers.h>
#include "SMApplication.h"

char* SMOpenFileDialog();

void SMMethodHandler::OnMethodCall(Awesomium::WebView* caller,
                              unsigned int remote_object_id,
                              const Awesomium::WebString& method_name,
                              const Awesomium::JSArray& args) {
    // log
    char* methodNameStr = SMWebStrToUTF8((Awesomium::WebString&)method_name);
    printf("[supermesh] called method %s\n", methodNameStr);
    free(methodNameStr);
    
    // check method
    if (method_name.Compare(Awesomium::WSLit("message")) == 0) {
        Awesomium::JSValue msgVal = args.At(0);
        Awesomium::WebString msgStr = msgVal.ToString();
        
        char* msgStrPtr = SMWebStrToUTF8(msgStr);
        SMMessageBox(msgStrPtr, APP_NAME, MB_OK);
        free(msgStrPtr);
    } else if (method_name.Compare(Awesomium::WSLit("open")) == 0) {
        // get path to open
        char* pathToOpen = SMOpenFileDialog();
        
        if (pathToOpen == NULL)
            return;
        
        // trigger application
        g_App->Open(pathToOpen);
        
        // free
        free(pathToOpen);
    } else if (method_name.Compare(Awesomium::WSLit("on")) == 0) {
        Awesomium::JSValue nameVal = args.At(0);
        Awesomium::WebString nameStr = nameVal.ToString();
        
        Awesomium::JSValue cbVal = args.At(1);
        Awesomium::JSObject& cbStr = cbVal.ToObject();
        
        g_App->On(nameStr, cbStr);
    }
}

Awesomium::JSValue SMMethodHandler::OnMethodCallWithReturnValue(Awesomium::WebView* caller,
                                               unsigned int remote_object_id,
                                               const Awesomium::WebString& method_name,
                                               const Awesomium::JSArray& args) {
    return Awesomium::JSValue();
}