#ifndef CA_CODER_FILE_HEADER
#define CA_CODER_FILE_HEADER


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

#include "cainterfaces.h"


namespace CA
{



class xmlCppDecoder
    : public IXmlCompiler
{
    std::string file_h;
    std::string file_cpp;
    std::string file_xml;
    std::string file_xslt;
    std::string file_info;
    std::string file_debug;
    std::string single_name;
    std::string path_in;
    stringList interface;
    stringList header;
    stringList source;
    stringList xslt;
    static std::string namesp_def;
    static std::string namesp_dec;

    void createXmlSource( IXmlNode* root);
    void createSourceFromXml( IXmlNode * node);
    static void createXsltFromNode( IXmlNode * node , xmlnodeList & childs );
    void createXslt(IXmlNode *node);
    void startXsltNodeFromXml(IXmlNode * node);
    void stopXsltNodeFromXml(IXmlNode * node);
    bool prepareOutFiles(std::string & filename);
    void createInfoFile( IXmlNode* root);
    void createIncludes();
    void createTest( IXmlNode* root);
    void prepareForXslt();
    void finalizeForXslt();
    void createXsltFile(IXmlNode *node);
    void createDebugFile(IXmlNode *node);
    void createLicense();
    void createIfdef();
    static void promoteChild( IXmlNode * model ,  IXmlNode *other);
    static void promoteChildTo( IXmlNode * model ,  xmlnodeList *other);
    static void prepareChildNodeList( IXmlNode * node , xmlnodeList & childs );
    static void emitAddTestCode(IXmlNode *root,std::stringstream & out);
    static void emitHeaderInterfaceInit(IXmlNode * node, std::stringstream & out);
    static void emitHeaderClassInit(IXmlNode * node,std::stringstream & out);
    static void emitCtorInterfaceInit(IXmlNode * node, std::stringstream & out);
    static void emitCtorClass(IXmlNode * node, xmlnodeList & childs,std::stringstream & out);
    static void emitSourceCtorClass(IXmlNode * node,xmlnodeList & childs, std::stringstream & out);
    static void emitConstKeyNames(xmlnodeList & childs , std::stringstream & out);
    static void emitSourceConstKeyNames(IXmlNode * node,xmlnodeList & childs , std::stringstream & out);
    static void emitVarChildClass(IXmlNode * node,xmlnodeList & childs , std::stringstream & out);
    static void emitGettersClass(IXmlNode * node,xmlnodeList & childs , std::stringstream & out);
    static void emitHeaderClassClose(std::stringstream & out);
    static void getInterfaceName(IXmlNode *node, std::string & classname);
    static void getClassName(IXmlNode *node, std::string & classname);
    static void getClassDottedName(IXmlNode *node, std::string & classname);
    static bool saveToFile(std::string & filename,stringList & list);
    static bool appendToFile(std::string & filename,stringList & list);
    static bool packToFile(std::string & path,const char *name,const char *array,size_t size);
    static void getUpperName(const std::string & name, std::string & u1name);
    static void getOriginName(IXmlNode *node,std::string & name);
    //static void printFullNode(std::stringstream & ss, IXmlNode *node);
    static bool checkChildsArray(xmlnodeList & childs);
    inline static std::string & getNameSpace()
    {
        return namesp_def;
    }
    inline static std::string & getNameSpaceDecorate()
    {
        return namesp_dec;
    }
    static void prepareNamespace();
public :
    bool compile(std::string filename) final;
};

}


#endif
