#ifndef SMDataSource_H
#define SMDataSource_H

#include "SMFramework.h"
#include <Awesomium/DataSource.h>

class SMDataSource : public Awesomium::DataSource {
public:
    SMDataSource() {}
    virtual ~SMDataSource() {}
    
    virtual void OnRequest(int request_id,
                           const Awesomium::ResourceRequest& request,
                           const Awesomium::WebString& path);
    
};

#endif