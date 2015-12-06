#ifndef SMMethodHandler_h
#define SMMethodHandler_h

#include "SMFramework.h"
#include <Awesomium/WebCore.h>

class SMMethodHandler : public Awesomium::JSMethodHandler {
public:
    virtual void OnMethodCall(Awesomium::WebView* caller,
                              unsigned int remote_object_id,
                              const Awesomium::WebString& method_name,
                              const Awesomium::JSArray& args);
    
    
    virtual Awesomium::JSValue OnMethodCallWithReturnValue(Awesomium::WebView* caller,
                                                           unsigned int remote_object_id,
                                                           const Awesomium::WebString& method_name,
                                                           const Awesomium::JSArray& args);
    
    virtual ~SMMethodHandler() {}
};

#endif
