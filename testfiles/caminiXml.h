#ifndef CA_MINI_XML_HEADER
#define CA_MINI_XML_HEADER

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

#include <cstddef>
#include <string>
#include <list>
#include <map>
#include <vector>
#include <sstream>
#include <iostream>
#include <locale>
#include <chrono>
#include <cstring>

namespace CA
{
#ifdef _DOUBLE_UNICODE
typedef  char32_t     _cbt;
#else
#ifdef _UNICODE
typedef  char16_t     _cbt;
#else
typedef char _cbt;
#endif
#endif

#ifdef _MSV_VER
#include <codecvt>
#endif


#if  (_WIN32 || _WIN64)
#define wctombs wcstombs
#endif

#ifdef _UNICODE

class UtoA
{
public:
    UtoA(const std::u16string & v):_good(false)
    {
        std::wstring_convert<std::codecvt_utf8_utf16<char16_t>,char16_t> converter;
        if(v.size())
        {
            u8 = converter.to_bytes(v);
            if(u8.size())
            {
                _good=true;
            }
        }
        else
        {
            _good=true;
            u8.clear();
        }
    }
    inline const char *utf8()
    {
        return u8.c_str();
    }
    inline bool good()
    {
        return _good;
    }
private:
    std::string u8;
    bool _good;
};
#else

class UtoA
{
public:
    inline explicit UtoA(const std::string &v)
    {
        u8 = v.c_str();
    }

    inline explicit UtoA(const char *v)
    {
        u8 = v;
    }

    inline const char *utf8()
    {
        return u8;
    }

    inline bool good()
    {
        return true;
    }

private:
    const char *u8;
};

#endif

#ifdef _UNICODE
class AtoU
{
public:
    AtoU(const std::string & v):_good(false)
    {
        std::wstring_convert<std::codecvt_utf8_utf16<char16_t>,char16_t> converter;
        if(v.size())
        {
            u16 = converter.from_bytes(v);
            if(u16.size())
            {
                _good=true;
            }
        }
        else
        {
            _good=true;
            u16.clear();
        }
    }
    inline const char16_t *utf16()
    {
        return u16.c_str();
    }
    inline bool good()
    {
        return _good;
    }
private:
    std::u16string u16;
    bool _good;
};

#else

class AtoU
{
public:
    inline explicit AtoU(const std::string &v)
    {
        u16 = v.c_str();
    }

    inline explicit AtoU(const char *v)
    {
        u16 = v;
    }

    inline const char *utf16()
    {
        return u16;
    }

    inline bool good()
    {
        return true;
    }

private:
    const char *u16;
};

#endif
class IXmlNode;
typedef std::pair<std::string, std::string> optionPair;
typedef std::list<optionPair> optionsList;
typedef std::pair<std::string,optionsList > pairValue;
typedef std::vector<IXmlNode *> xmlnodeList;


class IXmlNode
{
public:
    static IXmlNode * getNewNode();
    typedef enum tag_imx_node_type
    {
        inode_simple,
        inode_simple_with_options,
        inode_childs,
        inode_childs_with_options,
        inode_array,
        inode_array_with_options,
        inode_array_childs,
        inode_array_childs_with_options,
    } xmlNodeType;
public:


    virtual IXmlNode *find(std::string _name) = 0;

    virtual IXmlNode *add(std::string _name, std::string  value) = 0;

    virtual IXmlNode *add(std::string _name, std::string & value,optionsList & optl) = 0;

    virtual long getLong() = 0;

    virtual std::string &getValue() = 0;

    virtual IXmlNode *getNext() = 0;

    virtual void setNext(IXmlNode *v) = 0;

    virtual const std::string &getName() = 0;

    virtual const std::string &getFullName() = 0;

    virtual void getDecorateName(std::string & out) = 0;

    virtual void getDiscendantDecorateName(std::string & out)=0;

    virtual void setName(std::string _name) = 0;

    virtual IXmlNode *getParent() = 0;

    virtual void setParent(IXmlNode *v) = 0;

    virtual IXmlNode *getChild() = 0;

    virtual void setChild(IXmlNode *v) = 0;

    virtual void setValue(std::string _value) = 0;

    virtual size_t getChildName(std::string name) = 0;

    virtual size_t getChildNameList(std::string name, xmlnodeList *child, IXmlNode ** templ_m) = 0;

    virtual IXmlNode *lastchild() = 0;

    virtual IXmlNode *findLast(std::string _name, IXmlNode *end) = 0;

    virtual IXmlNode *link(std::string &name, IXmlNode *_child) = 0;

    virtual IXmlNode *cat(std::string addValue) = 0;

    virtual void addOption(optionPair & option) = 0;

    virtual optionsList &getOptions() = 0;

    virtual void setOptions( optionsList & optl) = 0;

    virtual void mergeOptions( optionsList & optl) = 0;

    virtual const xmlNodeType getNodeType() = 0;

    virtual void setNodeType(xmlNodeType n)=0;

    virtual size_t getIndex() = 0;

    virtual size_t getChildsNum() =0;

    virtual void merge(IXmlNode *other)=0;

    virtual void setIndex(size_t _index) = 0;

    virtual bool load(std::string file_in)=0;

    virtual bool save(std::string file_out)=0;

    virtual void print(FILE *out, bool decorate=false) = 0;

    virtual void toString(std::stringstream & ss,bool descendant,bool decorate=false)=0;

    virtual ~IXmlNode() = default;
};


///simple xml for key<.key.....> - value pair
} // ena CA namespace


#endif
