
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

/// declare namespace TEST
namespace TEST
{


/// declare interface ICAXml_Root for node <root>
class ICAXml_Root
{
protected:
    static const CA::_cbt *  caKEY_PIPPO;
    static const CA::_cbt *  caKEY_PLUTO;
    static const CA::_cbt *  caKEY_TOPOLINO;
    static const CA::_cbt *   mName;

public:
    virtual ~ICAXml_Root()=default;
    virtual bool loadFromXml(std::string filename)=0;
};


/// implement interface ICAXml_Root : as CAXml_Root
class CAXml_Root
    : public ICAXml_Root
    , public CA::IKeyValue
{
protected:
    CA::keyList predef;

public:
/// ctor
    CAXml_Root();
/// value of this node :
    std::string node_internal_value;
/// value of node : root.pippo
    std::string pippo;
/// value of node : root.pluto
    std::string pluto;
/// value of node : root.topolino
    std::string topolino;
public:
/// getters
/// return this node name
    inline const CA::_cbt * getICAXml_Name_Value() final
    {
        return mName;
    }

/// return list of predefined childs node name
    inline CA::keyList *  getICAXml_Predef_List() final
    {
        return &predef;
    }

/// load from IXmlNode
    inline void loadFromXmlNode(CA::IXmlNode *node) final
    {
        CA::LCFXml::loadFromXml(node,this);
    }
/// human readable to string
    void toString(std::iostream &ss)
    {
        std::string parent("    ");
        ss<<"<"<<getICAXml_Name_Value();
        ss<<">"<<node_internal_value<<std::endl;
        CA::LCFXml::toString(ss,this,parent);
        ss<<"</"<<getICAXml_Name_Value()<<">"<<std::endl;
    }
/// entry point from file xml to variable class members
    bool loadFromXml(std::string filename) final;
};


}; /// end namespace TEST
