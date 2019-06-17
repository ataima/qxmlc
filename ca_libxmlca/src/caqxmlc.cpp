#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale>
#include <string>
#include <stdarg.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "caminiXml.h"
#include "caargv.h"
#include "cacoder.h"
#include "calogger.h"
#include "camain.h"
#include "caqxmlc.h"
#include <iostream>

/**************************************************************
Copyright(c) 2019 Angelo Coppi

Permission is hereby granted, free of charge, to any person
obtaining a copy of this software and associated documentation
files(the "Software"), to deal in the Software without
restriction, including without limitation the rights to use,
copy, modify, merge, publish, distribute, sublicense, and / or sell
copies of the Software, and to permit persons to whom the
Software is furnished to do so, subject to the following
conditions :

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.
 ********************************************************************/


extern "C" void * openQxmlInstance()
{
    CA::ILogger *logger = new CA::Logger();
    CA::IPrinter *printer = new CA::DefaultPrinter();
    logger->setOutput(printer);
    return (void * ) new CA::mainAppExecutor();
}

extern "C" void   closeQxmlInstance(void * *instance)
{
    if(instance!=nullptr)
    {
        auto *exec = static_cast<CA::mainAppExecutor *>(*instance);
        delete exec;
        *instance=nullptr;
    }
    CA::ILogger *logger=CA::ILogger::getInstance();
    delete logger;
}

extern "C" bool   runQxmlInstance(void *instance,const char *argv[], size_t argc)
{
    auto result=false;
    auto *exec = static_cast<CA::mainAppExecutor *>(instance);
    if (exec != nullptr)
    {
        if (exec->init(argv, argc))
        {
            result = exec->execute();
        }
    }
    return result;
}