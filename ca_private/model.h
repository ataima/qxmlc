
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

/// declare interface ICAXml_Root_Node for node <node>
class ICAXml_Root_Node
{
protected:
    static const CA::_cbt *  caKEY_PIPPO;
    static const CA::_cbt *  caKEY_PLUTO;
    static const CA::_cbt *  caKEY_TOPOLINO;
    static const CA::_cbt *  caKEY_ZIOPAPERONE;
    static const CA::_cbt *   mName;

public:
    virtual ~ICAXml_Root_Node()=default;
};


/// declare interface ICAXml_Root for node <root>
class ICAXml_Root
{
protected:
    static const CA::_cbt *  caKEY_NODE;
    static const CA::_cbt *   mName;

public:
    virtual ~ICAXml_Root()=default;
    virtual bool loadFromXml(std::string filename)=0;
};


/// implement interface ICAXml_Root_Node : as CAXml_Root_Node
class CAXml_Root_Node
    : public ICAXml_Root_Node
    , public IClonable
{
protected:
    keyList predef;

public:
/// ctor
    CAXml_Root_Node();
/// value of this node :
    std::string node_internal_value;
/// value of node : root.node.pippo
    std::string pippo;
/// options of node : root.node.pippo
    CA::optionsList  pippo_option;
/// value of node : root.node.pluto
    std::string pluto;
/// options of node : root.node.pluto
    CA::optionsList  pluto_option;
/// value of node : root.node.topolino
    std::string topolino;
/// options of node : root.node.topolino
    CA::optionsList  topolino_option;
/// value of node : root.node.ziopaperone
    std::string ziopaperone;
public:
/// getters
/// return this node name
    inline const CA::_cbt * getICAXml_Name_Value() final
    {
        return mName;
    }

/// return list of predefined childs node name
    inline keyList *  getICAXml_Predef_List() final
    {
        return &predef;
    }

/// load from IXmlNode
    inline void loadFromXml(CA::IXmlNode *node) final
    {
        LCFXml::loadFromXml(node,this);
    }
/// human readable to string
/// return a clone of Unknow Obj
    inline IClonable *clone() final
    {
        return new CAXml_Root_Node();
    }
/// return a value of complex child node
    inline const CA::_cbt * getInternalValue() final
    {
        return node_internal_value.c_str();
    }
/// Set the  value of complex child node
    inline void setInternalValue(std::string &str) final
    {
        node_internal_value=str;
    }
};


/// implement interface ICAXml_Root : as CAXml_Root
class CAXml_Root
    : public ICAXml_Root
    , public IKeyValue
{
protected:
    keyList predef;

public:
/// ctor
    CAXml_Root();
    ~CAXml_Root();
/// value of this node :
    std::string node_internal_value;
/// object for nodes[] : root.node
    std::vector<IClonable *> node;
    CAXml_Root_Node  node_ref_clonable;
public:
/// getters
/// return this node name
    inline const CA::_cbt * getICAXml_Name_Value() final
    {
        return mName;
    }

/// return list of predefined childs node name
    inline keyList *  getICAXml_Predef_List() final
    {
        return &predef;
    }

/// load from IXmlNode
    inline void loadFromXml(CA::IXmlNode *node) final
    {
        LCFXml::loadFromXml(node,this);
    }
/// human readable to string
    void toString(std::iostream &ss)
    {
        std::string parent("    ");
        ss<<"<"<<getICAXml_Name_Value();
        ss<<">"<<node_internal_value<<std::endl;
        LCFXml::toString(ss,this,parent);
        ss<<"</"<<getICAXml_Name_Value()<<">"<<std::endl;
    }
/// entry point from file xml to variable class members
    bool loadFromXml(std::string filename) final;
};


