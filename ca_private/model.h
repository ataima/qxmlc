#ifndef FILE3_HEADER
#define FILE3_HEADER

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

/// declare interface ICAXml_Root_Node3 for node <node3>
class ICAXml_Root_Node3
{
protected:
    static const CA::_cbt *  caKEY_B1;
    static const CA::_cbt *  caKEY_B2;
    static const CA::_cbt *  caKEY_B3;
    static const CA::_cbt *  caKEY_B4;
    static const CA::_cbt *  caKEY_B5;
    static const CA::_cbt *  caKEY_B6;
    static const CA::_cbt *  caKEY_B7;
    static const CA::_cbt *  caKEY_B8;
    static const CA::_cbt *  caKEY_B9;
    static const CA::_cbt *   mName;

public:
    virtual ~ICAXml_Root_Node3()=default;
};


/// declare interface ICAXml_Root_Node2 for node <node2>
class ICAXml_Root_Node2
{
protected:
    static const CA::_cbt *  caKEY_A1;
    static const CA::_cbt *  caKEY_A2;
    static const CA::_cbt *  caKEY_A3;
    static const CA::_cbt *  caKEY_A4;
    static const CA::_cbt *  caKEY_A5;
    static const CA::_cbt *  caKEY_A6;
    static const CA::_cbt *  caKEY_A7;
    static const CA::_cbt *  caKEY_A8;
    static const CA::_cbt *  caKEY_A9;
    static const CA::_cbt *   mName;

public:
    virtual ~ICAXml_Root_Node2()=default;
};


/// declare interface ICAXml_Root_Node1 for node <node1>
class ICAXml_Root_Node1
{
protected:
    static const CA::_cbt *  caKEY_PIPPO;
    static const CA::_cbt *  caKEY_PLUTO;
    static const CA::_cbt *  caKEY_TOPOLINO;
    static const CA::_cbt *   mName;

public:
    virtual ~ICAXml_Root_Node1()=default;
};


/// declare interface ICAXml_Root for node <root>
class ICAXml_Root
{
protected:
    static const CA::_cbt *  caKEY_NODE1;
    static const CA::_cbt *  caKEY_NODE2;
    static const CA::_cbt *  caKEY_NODE3;
    static const CA::_cbt *  caKEY_STEP;
    static const CA::_cbt *   mName;

public:
    virtual ~ICAXml_Root()=default;
    virtual bool loadFromXml(std::string filename)=0;
    virtual void toString(std::iostream &ss)=0;
};


/// implement interface ICAXml_Root_Node3 : as CAXml_Root_Node3
class CAXml_Root_Node3
    : public ICAXml_Root_Node3
    , public CA::IKeyValue
{
protected:
    CA::keyList predef;

public:
/// ctor
    CAXml_Root_Node3();
/// value of this node :
    std::string node_internal_value;
/// value of node : root.node3.b1
    std::string b1;
/// value of node : root.node3.b2
    std::string b2;
/// value of node : root.node3.b3
    std::string b3;
/// value of node : root.node3.b4
    std::string b4;
/// value of node : root.node3.b5
    std::string b5;
/// value of node : root.node3.b6
    std::string b6;
/// value of node : root.node3.b7
    std::string b7;
/// value of node : root.node3.b8
    std::string b8;
/// value of node : root.node3.b9
    std::string b9;
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
/// human readable to map as pair key value
    void toMap(std::map<std::string,std::string> & outmap,bool ucase=true)
    {
        CA::LCFXml::toMap(outmap,this,ucase);
    }
};


/// implement interface ICAXml_Root_Node2 : as CAXml_Root_Node2
class CAXml_Root_Node2
    : public ICAXml_Root_Node2
    , public CA::IKeyValue
{
protected:
    CA::keyList predef;

public:
/// ctor
    CAXml_Root_Node2();
/// value of this node :
    std::string node_internal_value;
/// value of node : root.node2.a1
    std::string a1;
/// value of node : root.node2.a2
    std::string a2;
/// value of node : root.node2.a3
    std::string a3;
/// value of node : root.node2.a4
    std::string a4;
/// value of node : root.node2.a5
    std::string a5;
/// value of node : root.node2.a6
    std::string a6;
/// value of node : root.node2.a7
    std::string a7;
/// value of node : root.node2.a8
    std::string a8;
/// value of node : root.node2.a9
    std::string a9;
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
/// human readable to map as pair key value
    void toMap(std::map<std::string,std::string> & outmap,bool ucase=true)
    {
        CA::LCFXml::toMap(outmap,this,ucase);
    }
};


/// implement interface ICAXml_Root_Node1 : as CAXml_Root_Node1
class CAXml_Root_Node1
    : public ICAXml_Root_Node1
    , public CA::IKeyValue
{
protected:
    CA::keyList predef;

public:
/// ctor
    CAXml_Root_Node1();
/// value of this node :
    std::string node_internal_value;
/// value of node : root.node1.pippo
    std::string pippo;
/// value of node : root.node1.pluto
    std::string pluto;
/// value of node : root.node1.topolino
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
/// human readable to map as pair key value
    void toMap(std::map<std::string,std::string> & outmap,bool ucase=true)
    {
        CA::LCFXml::toMap(outmap,this,ucase);
    }
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
/// object for node : root.node1
    CAXml_Root_Node1 node1;
/// object for node : root.node2
    CAXml_Root_Node2 node2;
/// object for node : root.node3
    CAXml_Root_Node3 node3;
/// value of nodes[] : root.step
    std::vector<std::string> step;
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
/// human readable to map as pair key value
    void toMap(std::map<std::string,std::string> & outmap,bool ucase=true)
    {
        CA::LCFXml::toMap(outmap,this,ucase);
    }
/// human readable to string
    void toString(std::iostream &ss) final
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


#endif  //FILE3_HEADER
