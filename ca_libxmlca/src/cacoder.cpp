#include "calogiface.h"
#include "caminiXml.h"
#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#include <libgen.h>
#include <numeric>
#include "caargv.h"
#include "cacoder.h"
#include "camain.h"
#include "calogiface.h"
#include "capackedfiles.h"
#include <algorithm>
#include <sys/stat.h>


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



namespace CA
{

static const char * dbgaid[]=
{
    "inode_simple",
    "inode_simple_with_options",
    "inode_childs",
    "inode_childs_with_options",
    "inode_array",
    "inode_array_with_options",
    "inode_array_childs",
    "inode_array_childs_with_options"
};

std::string xmlCppDecoder::namesp_def;
std::string xmlCppDecoder::namesp_dec;




bool xmlCppDecoder::checkChildsArray(xmlnodeList & childs)
{
    for ( auto it : childs )
    {
        if (it->getNodeType() == IXmlNode::xmlNodeType::inode_array_childs)
        {
            return true;
        }
    }
    return false;
}



void xmlCppDecoder::getOriginName(IXmlNode *node,std::string & name)
{
    std::string result;
    if(node!=nullptr)
    {
        result = node->getFullName();
        std::string::size_type pos;
        result[0] = ::toupper(result.at(0));
        do
        {
            pos = result.find('.');
            if (pos != std::string::npos)
            {
                result[pos] = '_';
                pos++;
                result[pos] = ::toupper(result.at(pos));
            }
        }
        while (pos != std::string::npos);
        name += result;
    }
}




void xmlCppDecoder::getUpperName(const std::string & name, std::string & u1name)
{
    u1name=name;
    std::transform(u1name.begin(), u1name.end(), u1name.begin(), ::toupper);
}
void xmlCppDecoder::getInterfaceName(IXmlNode *node, std::string & classname)
{
    classname="ICAXml_";
    getOriginName(node,classname);
}


void xmlCppDecoder::getClassName(IXmlNode *node, std::string & classname)
{
    classname="CAXml_";
    getOriginName(node,classname);
}


void xmlCppDecoder::getClassDottedName(IXmlNode *node, std::string & classname)
{
    classname="\""+node->getFullName()+"\"";
}

void  xmlCppDecoder::emitHeaderInterfaceInit(IXmlNode * node , std::stringstream & out)
{

    std::string decoratename;
    xmlCppDecoder::getInterfaceName(node,decoratename);
    out<<"/// declare interface "<<decoratename<<" for node <"<<
       node->getName()<<">"<<std::endl;
    out<<"class "<<decoratename<<std::endl;
    out<<"{"<<std::endl;
    LogInfo("Add Interface : %s",decoratename.c_str());
}

void  xmlCppDecoder::emitHeaderClassInit(IXmlNode * node, std::stringstream & out)
{
    std::string decoratename,idecoratename;
    xmlCppDecoder::getInterfaceName(node,idecoratename);
    xmlCppDecoder::getClassName(node,decoratename);
    out<<"/// implement interface "<<idecoratename<<" : as "<<decoratename<<std::endl;
    out<<"class "<<decoratename <<std::endl;
    out<<"    : public "<<idecoratename<<std::endl;
    if(node->getNodeType()==IXmlNode::xmlNodeType::inode_array_childs)
        out<<"    , public CA::IClonable"<<std::endl;
    else if(node->getNodeType()==IXmlNode::xmlNodeType::inode_array_childs_with_options)
        out<<"    , public CA::IClonableOption"<<std::endl;
    else
        out<<"    , public CA::IKeyValue"<<std::endl;
    out<<"{"<<std::endl;
    LogInfo("Add Class : %s",decoratename.c_str());
}

void  xmlCppDecoder::emitCtorInterfaceInit(IXmlNode * node, std::stringstream & out)
{
    std::string decoratename;
    xmlCppDecoder::getInterfaceName(node,decoratename);
    out<<"public:"<<std::endl;
    out<<"    virtual ~"<<decoratename<<"()=default;"<<std::endl;
    if(node->getParent()==nullptr)
    {
        out<<"    virtual bool loadFromXml(std::string filename)=0;"<<std::endl;
    }

}

void xmlCppDecoder::emitCtorClass(IXmlNode * node, xmlnodeList & childs,std::stringstream & out)
{
    out <<"protected:"<< std::endl;
    out <<"    CA::keyList predef;"<< std::endl;
    out << std::endl;
    std::string decoratename;
    xmlCppDecoder::getClassName(node,decoratename);
    out<<"public:"<<std::endl;
    out<<"/// ctor"<<std::endl;
    out<<"    "<<decoratename<<"();"<<std::endl;
    if(node->getParent()==nullptr  && xmlCppDecoder::checkChildsArray(childs) )
    {
        out<<"    ~"<<decoratename<<"();"<<std::endl;
    }
}


void xmlCppDecoder::emitSourceCtorClass(IXmlNode * node,xmlnodeList & childs, std::stringstream & out)
{

    std::string decoratename;
    if(node==nullptr)return;
    xmlCppDecoder::getClassName(node,decoratename);
    out<<std::endl;
    out<<decoratename<<"::"<<decoratename<<"(){"<<std::endl;
    for(auto it : childs)
    {
        std::string up,dot;
        xmlCppDecoder::getUpperName(it->getName(),up);
        xmlCppDecoder::getClassDottedName(it,dot);
        if (it->getNodeType() == IXmlNode::xmlNodeType::inode_simple)
        {
            out << "    predef.push_back(CA::xmlNodeSpec( caKEY_" <<up<<","<<dot<<",&"<<
                it->getName()<<"));"<<std::endl;
        }
        else if (it->getNodeType() == IXmlNode::xmlNodeType::inode_simple_with_options)
        {
            out << "    predef.push_back(CA::xmlNodeSpec( caKEY_" <<up<<","<<dot<<",&"<<it->getName()<<",&"
                <<it->getName()<<"_option));"<<std::endl;
        }
        else if (it->getNodeType() == IXmlNode::xmlNodeType::inode_childs)
        {
            out << "    predef.push_back(CA::xmlNodeSpec( caKEY_" <<up<<","<<dot<<",&"<<it->getName()<<
                ".node_internal_value,&"<<it->getName()<<"));"<<std::endl;
        }
        else if (it->getNodeType() == IXmlNode::xmlNodeType::inode_childs_with_options)
        {
            out << "    predef.push_back(CA::xmlNodeSpec( caKEY_" <<up<<","<<dot<<",&"<<it->getName()<<
                ".node_internal_value,&"<<it->getName()<<",&"<<it->getName()<<
                ".node_internal_options"<<"));"<<std::endl;
        }
        else if (it->getNodeType() == IXmlNode::xmlNodeType::inode_array )
        {
            out << "    predef.push_back(CA::xmlNodeSpec( caKEY_" <<up<<","<<dot<<",&"<<
                it->getName()<<"));"<<std::endl;
        }
        else if (it->getNodeType() == IXmlNode::xmlNodeType::inode_array_with_options )
        {
            out << "    predef.push_back(CA::xmlNodeSpec( caKEY_" <<up<<","<<dot<<",&"<<
                it->getName()<<"));"<<std::endl;
        }
        else if (it->getNodeType() == IXmlNode::xmlNodeType::inode_array_childs)
        {
            out << "    predef.push_back(CA::xmlNodeSpec( caKEY_" <<up<<","<<dot<<",&"
                <<it->getName()<<",&"<<it->getName()<<"_ref_clonable));"<<std::endl;
        }
        else if (it->getNodeType() == IXmlNode::xmlNodeType::inode_array_childs_with_options)
        {
            out << "    predef.push_back(CA::xmlNodeSpec( caKEY_" <<up<<","<<dot<<",&"<<it->getName()<<
                ",&"<<it->getName()<<"_ref_clonable_option));"<<std::endl;
        }
        it++;
    }
    out<<"}"<<std::endl<<std::endl<<std::endl;
    IXmlNode *parent=(*childs.begin())->getParent();
    if(parent->getParent()==nullptr)
    {
        auto delete_child_array=xmlCppDecoder::checkChildsArray(childs);
        if(delete_child_array)
        {
            out << decoratename << "::~" << decoratename << "()" << std::endl;
            out << "{" << std::endl;

            for ( auto it: childs )
            {
                if (it->getNodeType() == IXmlNode::xmlNodeType::inode_array_childs)
                {
                    out << "    CA::LCFXml::deleteChildsArray(&"<<it->getName()<<");"<<std::endl;
                }
            }
            out << "}" << std::endl<< std::endl<< std::endl;
        }
        out << "bool "<<decoratename<<"::loadFromXml(std::string filename){" << std::endl;
        out << "bool res=false;"<<std::endl;
        out << "CA::IXmlNode *root=CA::IXmlNode::getNewNode();" << std::endl;
        out << "if(root->load(filename)){" << std::endl;
        out << "    loadFromXml(root);" << std::endl;
        out << "    res=true;"<<std::endl;
        out << "   }" << std::endl;
        out << "delete root;" << std::endl;
        out << "return res;"<<std::endl;
        out << "}" << std::endl<< std::endl;
    }

}

void  xmlCppDecoder::emitConstKeyNames(xmlnodeList & childs , std::stringstream & out)
{
    out<<"protected:"<<std::endl;
    for ( auto & it : childs )
    {
        std::string up;
        xmlCppDecoder::getUpperName(it->getName(),up);
        out << "   static const CA::_cbt *  caKEY_" <<up<<";"<<std::endl;
    }
    out<<"   static const CA::_cbt *   mName;"<<std::endl;
    out<<std::endl;
}

void  xmlCppDecoder::emitSourceConstKeyNames(IXmlNode * node,xmlnodeList & childs , std::stringstream & out)
{
    std::string classname;
    if(node==nullptr)return ;
    xmlCppDecoder::getInterfaceName(node,classname);
    for (auto it : childs )
    {
        std::string up;
        xmlCppDecoder::getUpperName(it->getName(),up);
        IXmlNode::xmlNodeType curType=it->getNodeType();
        if(curType==IXmlNode::xmlNodeType::inode_simple ||
                curType==IXmlNode::xmlNodeType::inode_simple_with_options ||
                curType==IXmlNode::xmlNodeType::inode_childs ||
                curType==IXmlNode::xmlNodeType::inode_childs_with_options)
        {
            out << "const CA::_cbt *" << classname << "::caKEY_" << up << " = \"" <<
                it->getName() << "\";" << std::endl;
        }
        else if ( (curType==IXmlNode::xmlNodeType::inode_array ||
                   curType==IXmlNode::xmlNodeType::inode_array_with_options ||
                   curType==IXmlNode::xmlNodeType::inode_array_childs ||
                   curType==IXmlNode::xmlNodeType::inode_array_childs_with_options) )
        {
            out << "const CA::_cbt *" << classname << "::caKEY_" << up << " = \"" <<
                it->getName() << "\";" << std::endl;
        }
    }
    out << "const CA::_cbt *"<<classname<<"::mName=\""<<node->getName()<<"\";"<<std::endl;
    out<<std::endl;
}


void  xmlCppDecoder::emitVarChildClass(IXmlNode * parent,xmlnodeList & childs , std::stringstream & out)
{
    auto node_with_value=false;
    auto node_with_option=false;
    if(parent==nullptr)
    {
        node_with_value=true;
    }
    else
    {
        IXmlNode::xmlNodeType type=parent->getNodeType();
        if((type==IXmlNode::xmlNodeType::inode_childs) ||
                (type==IXmlNode::xmlNodeType::inode_childs_with_options) ||
                (type==IXmlNode::xmlNodeType::inode_array_childs) ||
                (type==IXmlNode::xmlNodeType::inode_array_childs_with_options))
        {
            node_with_value=true;
        }
    }
    if(node_with_value)
    {
        out << "/// value of this node : "<< std::endl;
        out << "   std::string node_internal_value;"<< std::endl;
    }
    if(parent==nullptr && childs.front()->getNodeType()==IXmlNode::xmlNodeType::inode_simple_with_options)
    {
        node_with_option=true;
    }
    else
    {
        IXmlNode::xmlNodeType type=parent->getNodeType();
        if((type==IXmlNode::xmlNodeType::inode_childs_with_options) ||
                (type==IXmlNode::xmlNodeType::inode_array_childs_with_options))
        {
            node_with_option=true;
        }
    }
    if(node_with_option)
    {
        out << "/// options of this node : "<< std::endl;
        out << "   CA::optionsList node_internal_options;"<< std::endl;
    }
    for ( auto it : childs )
    {
        if (it->getNodeType() == IXmlNode::xmlNodeType::inode_simple)
        {
            out << "/// value of node : "<<it->getFullName()<<std::endl;
            out << "   std::string " << it->getName() << ";" << std::endl;
        }
        else if (it->getNodeType() == IXmlNode::xmlNodeType::inode_simple_with_options)
        {
            out << "/// value of node : "<<it->getFullName()<<std::endl;
            out << "   std::string " << it->getName() << ";" << std::endl;
            out << "/// options of node : "<<it->getFullName()<<std::endl;
            out << "   CA::optionsList  " << it->getName() << "_option;" << std::endl;
        }
        else if (it->getNodeType() == IXmlNode::xmlNodeType::inode_childs)
        {
            std::string decoratename;
            out << "/// object for node : "<<it->getFullName()<<std::endl;
            xmlCppDecoder::getClassName(it, decoratename);
            out << "   " << decoratename << " "<<it->getName() << ";" << std::endl;
        }
        else if (it->getNodeType() == IXmlNode::xmlNodeType::inode_childs_with_options)
        {
            std::string decoratename;
            out << "/// object for node : "<<it->getFullName()<<std::endl;
            xmlCppDecoder::getClassName(it, decoratename);
            out << "   " << decoratename << " "<<it->getName() << ";" << std::endl;
        }
        else if (it->getNodeType() == IXmlNode::xmlNodeType::inode_array)
        {
            out << "/// value of nodes[] : "<<it->getFullName()<<std::endl;
            out << "   std::vector<std::string> " <<  it->getName()<< ";" << std::endl;
        }
        else if (it->getNodeType() == IXmlNode::xmlNodeType::inode_array_with_options)
        {
            out << "/// value of nodes[] with option : "<<it->getFullName()<<std::endl;
            out << "   std::vector <CA::pairValue>  " <<  it->getName()<< ";" << std::endl;
        }
        else if (it->getNodeType() == IXmlNode::xmlNodeType::inode_array_childs)
        {
            std::string decoratename;
            out << "/// object for nodes[] : "<<it->getFullName()<<std::endl;
            xmlCppDecoder::getClassName(it, decoratename);
            out << "   std::vector<CA::IClonable *> " << it->getName() << ";" << std::endl;
            out << "   "<<decoratename<<"  "<< it->getName()<<"_ref_clonable;"<< std::endl;
        }
        else if (it->getNodeType() == IXmlNode::xmlNodeType::inode_array_childs_with_options)
        {
            std::string decoratename;
            out << "/// object for nodes[] : "<<it->getFullName()<<std::endl;
            xmlCppDecoder::getClassName(it, decoratename);
            out << "   std::vector<CA::IClonableOption *> " << it->getName() << ";" << std::endl;
            out << "   "<<decoratename<<"  "<< it->getName()<<"_ref_clonable_option;"<< std::endl;
        }
    }
}



void  xmlCppDecoder::emitGettersClass(IXmlNode * parent,xmlnodeList & childs , std::stringstream & out)
{
    out<<"public:"<<std::endl;
    out<<"/// getters"<<std::endl;
    out<<"/// return this node name"<<std::endl;
    out<<"    inline const CA::_cbt * getICAXml_Name_Value() final"<<std::endl;
    out<<"    {"<<std::endl;
    out<<"        return mName;"<<std::endl;
    out<<"    }"<<std::endl<<std::endl;
    out<<"/// return list of predefined childs node name"<<std::endl;
    out<<"    inline CA::keyList *  getICAXml_Predef_List() final"<<std::endl;
    out<<"    {"<<std::endl;
    out<<"        return &predef;"<<std::endl;
    out<<"    }"<<std::endl<<std::endl;
    out<<"/// load from IXmlNode"<<std::endl;
    out<<"    inline void loadFromXml(CA::IXmlNode *node) final"<<std::endl;
    out<<"    {"<<std::endl;
    out<<"        CA::LCFXml::loadFromXml(node,this);"<<std::endl;
    out<<"    }"<<std::endl;


    out<<"/// human readable to map as pair key value"<<std::endl;
    out<<"    void toMap(std::map<std::string,std::string> & outmap,bool ucase=true)"<<std::endl;
    out<<"    {"<<std::endl;
    out<<"        CA::LCFXml::toMap(outmap,this,ucase);"<<std::endl;
    out<<"    }"<<std::endl;

    if(parent->getParent()==nullptr)
    {
        out<<"/// human readable to string"<<std::endl;
        out<<"    void toString(std::iostream &ss)"<<std::endl;
        out<<"    {"<<std::endl;
        out<<"        std::string parent(\"    \");"<<std::endl;
        out<<"        ss<<\"<\"<<getICAXml_Name_Value();"<<std::endl;
        out<<"        ss<<\">\"<<node_internal_value<<std::endl;"<<std::endl;
        out<<"        CA::LCFXml::toString(ss,this,parent);"<<std::endl;
        out<<"        ss<<\"</\"<<getICAXml_Name_Value()"<<"<<\">\"<<std::endl;"<<std::endl;
        out<<"    }"<<std::endl;
        out<<"/// entry point from file xml to variable class members"<<std::endl;
        out << "   bool loadFromXml(std::string filename) final;" << std::endl;
    }
    else
    {
        IXmlNode::xmlNodeType type=parent->getNodeType();
        if( type==IXmlNode::xmlNodeType::inode_array_childs )
        {
            std::string decoratename;
            getClassName(parent,decoratename);
            out<<"/// return a clone of Unknow Obj"<<std::endl;
            out<<"    inline CA::IClonable *clone() final" << std::endl;
            out<<"    {" << std::endl;
            out<<"        return new "<<decoratename<<"();" << std::endl;
            out<<"    }" << std::endl;
            out<<"/// return a value of complex child node"<<std::endl;
            out<<"    inline const CA::_cbt * getInternalValue() final" << std::endl;
            out<<"    {" << std::endl;
            out<<"        return node_internal_value.c_str();" << std::endl;
            out<<"    }" << std::endl;
            out<<"/// Set the  value of complex child node"<<std::endl;
            out<<"    inline void setInternalValue(std::string &str) final" << std::endl;
            out<<"    {" << std::endl;
            out<<"        node_internal_value=str;" << std::endl;
            out<<"    }" << std::endl;
        }
        else if( type==IXmlNode::xmlNodeType::inode_array_childs_with_options )
        {
            std::string decoratename;
            getClassName(parent,decoratename);
            out<<"/// return a clone of Unknow Obj"<<std::endl;
            out<<"    inline CA::IClonable *clone() final" << std::endl;
            out<<"    {" << std::endl;
            out<<"        return new "<<decoratename<<"();" << std::endl;
            out<<"    }" << std::endl;
            out<<"/// return a value of complex child node"<<std::endl;
            out<<"    inline const CA::_cbt * getInternalValue() final" << std::endl;
            out<<"    {" << std::endl;
            out<<"        return node_internal_value.c_str();" << std::endl;
            out<<"    }" << std::endl;
            out<<"/// Set the  value of complex child node"<<std::endl;
            out<<"    inline void setInternalValue(std::string &str) final" << std::endl;
            out<<"    {" << std::endl;
            out<<"        node_internal_value=str;" << std::endl;
            out<<"    }" << std::endl;
            out<<"/// return the  option list  of complex child node"<<std::endl;
            out<<"    inline CA::optionsList & getOptionsList() final" << std::endl;
            out<<"    {" << std::endl;
            out<<"        return node_internal_options;" << std::endl;
            out<<"    }" << std::endl;
            out<<"/// set the  option list  of complex child node"<<std::endl;
            out<<"    inline void setOptionList(CA::optionsList & optl)  final" << std::endl;
            out<<"    {" << std::endl;
            out<<"      if(!optl.empty()){"<<std::endl;
            out<<"          auto it=optl.begin();"<<std::endl;
            out<<"          auto _end=optl.end();"<<std::endl;
            out<<"          while(it!=_end) {"<<std::endl;
            out<<"              CA::optionPair p(it->first,it->second);"<<std::endl;
            out<<"              node_internal_options.insert(p);"<<std::endl;
            out<<"              it++;"<<std::endl;
            out<<"          }"<<std::endl;
            out<<"       }"<<std::endl;
            out<<"    }" << std::endl;
        }
    }
}



void  xmlCppDecoder::emitHeaderClassClose(  std::stringstream & out)
{
    out<<"};"<<std::endl<<std::endl<<std::endl;
}



void xmlCppDecoder::emitAddTestCode(IXmlNode *root,std::stringstream & out)
{
    std::string decoratename;
    xmlCppDecoder::getClassName(root,decoratename);
    out<<std::endl<<std::endl<<std::endl;
    out << "int main(int argc,const CA::_cbt * argv[]){" << std::endl;
    out << "  " << getNameSpaceDecorate()<<decoratename << " xmlDb;" << std::endl;
    out << "   std::chrono::steady_clock::time_point t_start;" << std::endl;
    out << "   std::chrono::steady_clock::time_point t_stop;" << std::endl;
    out << "   if(argc==2){" << std::endl;
    out << "      try{" << std::endl;
    out << "      std::string filename(argv[1]);" << std::endl;
    out << "      t_start = std::chrono::steady_clock::now();" << std::endl;
    out << "      if (xmlDb.loadFromXml(filename)){" << std::endl;
    out << "              t_stop = std::chrono::steady_clock::now();" << std::endl;
    out << "              std::cerr<<\"parse Xml file :\"<< filename <<\" - \"<<" << std::endl;
    out << "                       (t_stop - t_start).count()<<\" ns\"<< std::endl;" << std::endl;
    out << "              std::stringstream ss;" << std::endl;
    out << "              t_start = std::chrono::steady_clock::now();" << std::endl;
    out << "              xmlDb.toString(ss);" << std::endl;
    out << "              t_stop = std::chrono::steady_clock::now();" << std::endl;
    out << "              std::cerr<<\"toString  - \"<<" << std::endl;
    out << "                       (t_stop - t_start).count()<<\" ns\"<< std::endl;" << std::endl;
    out << "              std::cout<<ss.str().c_str();" << std::endl;
    out << "              return 0;" << std::endl;
    out << "         }" << std::endl;
    out << "      }catch(std::runtime_error & e){" << std::endl;
    out << "       std::cerr<<e.what()<<std::endl;"<< std::endl;
    out << "      }catch(...){" << std::endl;
    out << "       std::cerr<<\"Unknow exception \"<<std::endl;"<< std::endl;
    out << "      }" << std::endl;
    out << "    } else {;" << std::endl;
    out << "    std::cerr<<\"usage : test_xml <file xml>\"<< std::endl;"<< std::endl;
    out << "    }" << std::endl;
    out << "  return -1;"<< std::endl;
    out << "}" << std::endl << std::endl << std::endl;
}

/*
void xmlCppDecoder::printFullNode(std::stringstream & out, IXmlNode *node)
{
    stringList full;
    IXmlNode::xmlNodeType nType=IXmlNode::xmlNodeType::inode_simple;
    if(node!=nullptr)
    {
        out<<REPLACE;
        nType=node->getNodeType();
        std::string decorate;
        node->getDiscendantDecorateName(decorate);
        out<<decorate;
        out<<" : "<<BLUE_LIGHT<<dbgaid[nType]<<REPLACE<<std::endl;
    }
}
*/


void xmlCppDecoder::promoteChild( IXmlNode * model ,  IXmlNode *other)
{
    xmlnodeList childs;
    IXmlNode *ochild;
    other->getChildNameList( model->getName(), &childs, nullptr);
    for (auto & oit : childs)
    {
        ochild=oit;
        IXmlNode::xmlNodeType mtype = model->getNodeType();
        IXmlNode::xmlNodeType otype = ochild->getNodeType();
        if (mtype != otype)
        {
            switch (mtype)
            {
            case IXmlNode::xmlNodeType::inode_simple:
                if (otype == IXmlNode::xmlNodeType::inode_simple_with_options)
                {
                    model->setOptions(ochild->getOptions());
                    model->setNodeType(IXmlNode::xmlNodeType::inode_simple_with_options);
                }
                else if (otype == IXmlNode::xmlNodeType::inode_array)
                {
                    model->setNodeType(IXmlNode::xmlNodeType::inode_array);
                }
                else if (otype == IXmlNode::xmlNodeType::inode_array_with_options)
                {
                    model->setOptions(ochild->getOptions());
                    model->setNodeType(IXmlNode::xmlNodeType::inode_array_with_options);
                }
                break;
            case IXmlNode::xmlNodeType::inode_simple_with_options:
                if (otype == IXmlNode::xmlNodeType::inode_simple_with_options)
                {
                    model->mergeOptions(ochild->getOptions());
                }
                else if (otype == IXmlNode::xmlNodeType::inode_array)
                {
                    model->setNodeType(IXmlNode::xmlNodeType::inode_array_with_options);
                }
                else if (otype == IXmlNode::xmlNodeType::inode_array_with_options)
                {
                    model->mergeOptions(ochild->getOptions());
                    model->setNodeType(IXmlNode::xmlNodeType::inode_array_with_options);
                }
            case IXmlNode::xmlNodeType::inode_childs:
                if (otype == IXmlNode::xmlNodeType::inode_childs_with_options)
                {
                    model->setOptions(ochild->getOptions());
                    model->setNodeType(IXmlNode::xmlNodeType::inode_childs_with_options);
                }
                else if (otype == IXmlNode::xmlNodeType::inode_array_childs)
                {
                    model->setNodeType(IXmlNode::xmlNodeType::inode_array_childs);
                }
                else if (otype == IXmlNode::xmlNodeType::inode_array_childs_with_options)
                {
                    model->setOptions(ochild->getOptions());
                    model->setNodeType(IXmlNode::xmlNodeType::inode_array_childs_with_options);
                }
                break;
            case IXmlNode::xmlNodeType::inode_childs_with_options:
                if (otype == IXmlNode::xmlNodeType::inode_childs_with_options)
                {
                    model->mergeOptions(ochild->getOptions());
                }
                else if (otype == IXmlNode::xmlNodeType::inode_array_childs)
                {
                    model->setNodeType(IXmlNode::xmlNodeType::inode_array_childs_with_options);
                }
                else if (otype == IXmlNode::xmlNodeType::inode_array_childs_with_options)
                {
                    model->mergeOptions(ochild->getOptions());
                    model->setNodeType(IXmlNode::xmlNodeType::inode_array_childs_with_options);
                }
                break;
            case IXmlNode::xmlNodeType::inode_array:
                if (otype == IXmlNode::xmlNodeType::inode_array_with_options)
                {
                    model->setOptions(ochild->getOptions());
                    model->setNodeType(IXmlNode::xmlNodeType::inode_array_with_options);
                }
                else if (otype == IXmlNode::xmlNodeType::inode_simple_with_options)
                {
                    model->setOptions(ochild->getOptions());
                    model->setNodeType(IXmlNode::xmlNodeType::inode_array_childs_with_options);
                }
                break;
            case IXmlNode::xmlNodeType::inode_array_with_options:
                if (otype == IXmlNode::xmlNodeType::inode_array_with_options)
                {
                    model->mergeOptions(ochild->getOptions());
                }
                else if (otype == IXmlNode::xmlNodeType::inode_simple_with_options)
                {
                    model->mergeOptions(ochild->getOptions());
                }
            case IXmlNode::xmlNodeType::inode_array_childs:
                if (otype == IXmlNode::xmlNodeType::inode_array_childs_with_options)
                {
                    model->setOptions(ochild->getOptions());
                    model->setNodeType(IXmlNode::xmlNodeType::inode_array_childs_with_options);
                }
                break;
            case IXmlNode::xmlNodeType::inode_array_childs_with_options:
                if (otype == IXmlNode::xmlNodeType::inode_array_with_options)
                {
                    model->mergeOptions(ochild->getOptions());
                }
                break;
            }
        }
        else
        {
            switch (mtype)
            {
            case IXmlNode::xmlNodeType::inode_simple_with_options:
            case IXmlNode::xmlNodeType::inode_childs_with_options:
            case IXmlNode::xmlNodeType::inode_array_with_options:
            case IXmlNode::xmlNodeType::inode_array_childs_with_options:
                model->mergeOptions(ochild->getOptions());
                break;
            default:
                break;
            }
        }
    }

}


void xmlCppDecoder::promoteChildTo( IXmlNode * model ,  xmlnodeList *other)
{
    xmlnodeList childs;
    // find all child ot template selected: is the node with max childs
    size_t nchilds=model->getChildNameList(std::string("*"), &childs, nullptr);
    if(nchilds>0)
    {
        // for all node of the same name of selected template
        for (auto & it : *other)
        {
            for( auto & cit : childs)
            {
                IXmlNode * tmpchild=cit;
                if(it!=model)
                {
                    model->merge(it);
                    promoteChild(tmpchild, it);
                }
            }
        }
    }
}

void xmlCppDecoder::prepareChildNodeList( IXmlNode * node , xmlnodeList & childs )
{
    childs.clear();
    if(node==nullptr)return;
    IXmlNode::xmlNodeType nodeType;
    std::stringstream out;
    xmlnodeMap  childsMap;
    IXmlNode *child = node->getChild();
    // ottengo una lista per nome con un solo nodo per tutti inode_array_xxx
    while (child != nullptr)
    {
        pairNode pnode(child->getName(), child);
        auto it = childsMap.find(pnode.first);
        if (it == childsMap.end())
        {
            childsMap.insert(pnode);
        }
        else
        {
            nodeType=it->second->getNodeType();
            if((nodeType!= IXmlNode::xmlNodeType::inode_array) &&
                    (nodeType!= IXmlNode::xmlNodeType::inode_array_with_options) &&
                    (nodeType!= IXmlNode::xmlNodeType::inode_array_childs) &&
                    (nodeType!= IXmlNode::xmlNodeType::inode_array_childs_with_options)
              )
            {
                std::stringstream ss;
                ss<<"node :'"<<it->first<<"' already present but not signed as array, invalid !";
                throw std::runtime_error(ss.str().c_str());
            }
        }
        child = child->getNext();
    }
    // per ogni figlio nella lista che sia un array sostituisco con il modello prescelto
    for( auto it : childsMap)
    {
        child = it.second;
        if(child->getChild()!=nullptr && child->getParent()!=nullptr)
        {
            nodeType = child->getNodeType();
            switch(nodeType)
            {
            default:
                break;
            case IXmlNode::xmlNodeType::inode_array:
            case IXmlNode::xmlNodeType::inode_array_with_options:
            case IXmlNode::xmlNodeType::inode_array_childs:
            case IXmlNode::xmlNodeType::inode_array_childs_with_options:
                // find the node with max child to promote as template
                IXmlNode *mtemplate = nullptr;
                xmlnodeList tmpChilds;
                //trovo tutti i childs di nome guale e scelgo quello con più childs
                auto nnode = node->getChildNameList(child->getName(), &tmpChilds, &mtemplate);
                if (mtemplate != nullptr && nnode > 1)
                {
                    // mtemplate is the node with max child
                    promoteChildTo(mtemplate,&tmpChilds);
                    it.second=mtemplate;
                }
                else
                {
                    std::stringstream ss;
                    ss << "Type node missmatch : inode ' " << child->getName()
                       << "' sign as array but index return 1\n ";
                    throw std::runtime_error(ss.str().c_str());
                }
            }
        }
        // copio in  uscita
        //std::cout<<"ADD CHILD : "<<it->first<<std::endl;
        childs.push_back(it.second);
    }
}

void xmlCppDecoder::startXsltNodeFromXml(IXmlNode * node)
{
    if (node!=nullptr &&
            IOptionArgvManager::checkOption(f_createxslt))
    {
        std::stringstream ss;
        std::string decoratename;
        node->getDecorateName(decoratename);
        LogInfo("Xslt add element : %s to schema",decoratename.c_str());
        switch(node->getNodeType())
        {
        case IXmlNode::xmlNodeType::inode_simple:
            ss<<"<xs:element name=\""<<node->getName()<<"\" type=\"xs:string\"/>"<<std::endl;
            break;
        case IXmlNode::xmlNodeType::inode_simple_with_options:
        {
            ss << "<xs:element name=\"" << node->getName() << "\" type=\"xs:string\">" << std::endl;
            ss << "    <xs:complexType>" << std::endl;
            for (auto & it : node->getOptions())
            {
                ss<<"        <xs:attribute name=\""<<it.first<<"\" type=\"xs:string\"/>"<<std::endl;
            }
            ss << "    </xs:complexType>" << std::endl;
            ss << "</xs:element>" << std::endl;
        }
        break;
        case IXmlNode::xmlNodeType::inode_childs:
            ss << "<xs:element name=\"" << node->getName() << "\" type=\"xs:string\">" << std::endl;
            ss << "    <xs:complexType>" << std::endl;
            break;
        case IXmlNode::xmlNodeType::inode_childs_with_options:
        {
            ss << "<xs:element name=\"" << node->getName() << "\" type=\"xs:string\">" << std::endl;
            ss << "    <xs:complexType>" << std::endl;
            for (auto & it : node->getOptions())
            {
                ss<<"        <xs:attribute name=\""<<it.first<<"\" type=\"xs:string\"/>"<<std::endl;
            }
        }
        break;
        case IXmlNode::xmlNodeType::inode_array:
            ss<<"<xs:element name=\""<<node->getName()<<"\" type=\"xs:string\"/>"<<std::endl;

            break;
        case IXmlNode::xmlNodeType::inode_array_with_options:
        {
            ss << "<xs:element name=\"" << node->getName() << "\" type=\"xs:string\">" << std::endl;
            ss << "    <xs:complexType>" << std::endl;
            for (auto & it : node->getOptions())
            {
                ss<<"        <xs:attribute name=\""<<it.first<<"\" type=\"xs:string\"/>"<<std::endl;
            }
            ss << "    </xs:complexType>" << std::endl;
            ss << "</xs:element>" << std::endl;
        }

        break;
        case IXmlNode::xmlNodeType::inode_array_childs:
            ss << "<xs:element name=\"" << node->getName() << "\" type=\"xs:string\">" << std::endl;
            ss << "    <xs:complexType>" << std::endl;
            break;
        case IXmlNode::xmlNodeType::inode_array_childs_with_options:
        {
            ss << "<xs:element name=\"" << node->getName() << "\" type=\"xs:string\">" << std::endl;
            ss << "    <xs:complexType>" << std::endl;
            for (auto & it : node->getOptions())
            {
                ss<<"        <xs:attribute name=\""<<it.first<<"\" type=\"xs:string\"/>"<<std::endl;
            }
        }
        break;
        }
        xslt.push_back(ss.str());
    }
}

void xmlCppDecoder::stopXsltNodeFromXml(IXmlNode * node)
{
    if (node!=nullptr && IOptionArgvManager::checkOption(f_createxslt))
    {
        std::stringstream ss;
        std::string decoratename;
        node->getDecorateName(decoratename);
        LogInfo("Xslt add element : %s to schema",decoratename.c_str());
        switch(node->getNodeType())
        {
        case IXmlNode::xmlNodeType::inode_simple:
        case IXmlNode::xmlNodeType::inode_simple_with_options:
        case IXmlNode::xmlNodeType::inode_array:
        case IXmlNode::xmlNodeType::inode_array_with_options:
            break;
        case IXmlNode::xmlNodeType::inode_childs:
        case IXmlNode::xmlNodeType::inode_childs_with_options:
        case IXmlNode::xmlNodeType::inode_array_childs:
        case IXmlNode::xmlNodeType::inode_array_childs_with_options:
            ss << "    </xs:complexType>" << std::endl;
            ss << "</xs:element>" << std::endl;
            xslt.push_back(ss.str());
            break;
        }
    }
}


void xmlCppDecoder::createXslt(IXmlNode *node)
{
    xmlnodeList childs;
    createXsltFromNode(node,childs);
    startXsltNodeFromXml(node);
    for( auto it : childs)
    {
        if(it->getChild()!=nullptr && it->getParent()!=nullptr)
        {
            createXslt(it);
        }
        else
        {
            startXsltNodeFromXml(it);
        }
    }
    stopXsltNodeFromXml(node);
}



void xmlCppDecoder::createXsltFromNode( IXmlNode * node , xmlnodeList & childs )
{
    childs.clear();
    if(node==nullptr)return;
    IXmlNode::xmlNodeType nodeType;
    std::stringstream out;
    xmlnodeMap  childsMap;
    IXmlNode *child = node->getChild();
    // ottengo una lista per nome con un solo nodo per tutti inode_array_xxx
    while (child != nullptr)
    {
        pairNode pnode(child->getName(), child);
        auto it = childsMap.find(pnode.first);
        if (it == childsMap.end())
        {
            childsMap.insert(pnode);
        }
        else
        {
            nodeType=it->second->getNodeType();
            switch(nodeType)
            {
            case IXmlNode::xmlNodeType::inode_simple_with_options:
            case IXmlNode::xmlNodeType::inode_array_with_options:
            case IXmlNode::xmlNodeType::inode_childs_with_options:
            case IXmlNode::xmlNodeType::inode_array_childs_with_options:
                it->second->mergeOptions(pnode.second->getOptions());
                break;
            default:
                break;
            }
        }
        child = child->getNext();
    }
    // per ogni figlio nella lista che sia un array sostituisco con il modello prescelto
    for ( auto it : childsMap )
    {
        child = it.second;
        if(child->getChild()!=nullptr && child->getParent()!=nullptr)
        {
            nodeType = child->getNodeType();
            switch (nodeType)
            {
            default:
                break;
            case IXmlNode::xmlNodeType::inode_array:
            case IXmlNode::xmlNodeType::inode_array_with_options:
            case IXmlNode::xmlNodeType::inode_array_childs:
            case IXmlNode::xmlNodeType::inode_array_childs_with_options:
                // find the node with max child to promote as template
                IXmlNode *mtemplate = nullptr;
                xmlnodeList tmpChilds;
                auto nnode = node->getChildNameList(child->getName(), &tmpChilds, &mtemplate);
                if (mtemplate != nullptr && nnode > 1)
                {
                    it.second = mtemplate;
                }
                break;
            }
        }
        // copio in  uscita
        //std::cout<<"ADD CHILD : "<<it->first<<std::endl;
        childs.push_back(it.second);
    }
}


void xmlCppDecoder::createSourceFromXml( IXmlNode * node)
{
    if(node!=nullptr)
    {
        std::stringstream out;
        xmlnodeList childs;
        prepareChildNodeList(node,childs);
        emitHeaderInterfaceInit(node, out);
        emitConstKeyNames(childs, out);
        emitCtorInterfaceInit(node, out);
        emitHeaderClassClose(out);
        interface.push_front(out.str());
        out.str("");
        emitHeaderClassInit(node, out);
        emitCtorClass(node,childs, out);
        emitVarChildClass(node,childs, out);
        emitGettersClass(node,childs, out);
        emitHeaderClassClose(out);
        header.push_front(out.str());
        out.str("");
        emitSourceConstKeyNames(node,childs, out);
        emitSourceCtorClass(node,childs, out);
        source.push_front(out.str());
        for ( auto it :  childs )
        {
            if(it->getChild()!=nullptr && it->getParent()!=nullptr)
            {
                createSourceFromXml(it);
            }
            it++;
        }
    }
}



void xmlCppDecoder::createXmlSource( IXmlNode* root)
{
    if(root->getChild()!=nullptr)
    {
        createSourceFromXml(root);
    }
}

bool xmlCppDecoder::saveToFile(std::string & filename,stringList & list)
{
    auto res=false;
    std::ofstream writer;
    writer.open(filename);
    if (writer.is_open())
    {
        for (auto & it : list )
        {
            writer << it;
        }
        res=true;
    }
    writer.close();
    return res;
}

bool xmlCppDecoder::packToFile(std::string & path,const char *name,const char *array,size_t size)
{
    auto res=false;
    std::ofstream writer;
    std::string filename=path+"/"+name;
    writer.open(filename);
    if (writer.is_open())
    {
        writer.write(array,size);
    }
    writer.close();
    return res;
}


bool xmlCppDecoder::appendToFile(std::string & filename,stringList & list)
{
    auto res=false;
    std::ofstream writer;
    writer.open(filename,std::ofstream::out | std::ofstream::app);
    if (writer.is_open())
    {
        for  (auto & it : list )
        {
            writer << it;
        }
        res=true;
    }
    writer.close();
    return res;
}

bool xmlCppDecoder::prepareOutFiles(std::string & filename)
{
    auto res=false;
    if(!filename.empty())
    {
        if (IOptionArgvManager::checkOption(f_out_path ) )
        {
            path_in =IOptionArgvManager::getInstance()->getOption(f_out_path).getStringValue();
            mkdir(path_in.c_str(), (int)(S_IRWXU | S_IRWXG));
            std::string nfile = filename;
            std::string::size_type p = nfile.rfind('/');
            if (p != std::string::npos)
                nfile.erase(0, p + 1);
            p = nfile.rfind('.');
            if (p != std::string::npos)
                nfile.erase(p, nfile.size());
            single_name = nfile;
            file_h = path_in + "/" + single_name + ".h";
            file_cpp = path_in + "/" + single_name + ".cpp";
            file_xml = path_in + "/" + single_name + ".xml";
            file_xslt = path_in + "/" + single_name + ".xml.xslt";
            file_info = path_in + "/" + single_name + ".info.xml";
            file_debug = path_in + "/" + single_name + ".xml.debug";
        }
        else
        {
            std::string::size_type p = filename.rfind('.');
            file_h = filename;
            if (p != std::string::npos)
                file_h.erase(p, file_h.size());
            file_cpp = file_h;
            single_name = file_h;
            file_info=file_h;
            file_xml=file_h;
            file_xslt=file_h;
            file_debug=file_h;
            p = filename.rfind('/');
            if (p != std::string::npos)
                single_name.erase(0, p + 1);
            file_h += ".h";
            file_cpp += ".cpp";
            file_xml += ".xml";
            file_info += ".info.xml";
            file_xslt += ".xml.xslt";
            file_debug += ".xml.debug";
            path_in = filename;
            if (p != std::string::npos)
                path_in.erase(p, path_in.size());
        }
        res=true;
    }
    return res;
}

void xmlCppDecoder::createTest( IXmlNode* root)
{
    if (IOptionArgvManager::checkOption(f_addtest))
    {
        std::stringstream ss;
        emitAddTestCode(root, ss);
        source.push_back(ss.str());
    }
}



void xmlCppDecoder::createLicense()
{
    std::stringstream ss;
    ss<<"\n"
      "/**************************************************************\n"
      "Copyright(c) 2019 Angelo Coppi\n"
      "\n"
      "Permission is hereby granted, free of charge, to any person\n"
      "obtaining a copy of this software and associated documentation\n"
      "files(the \"Software\"), to deal in the Software without\n"
      "restriction, including without limitation the rights to use,\n"
      "copy, modify, merge, publish, distribute, sublicense, and / or sell\n"
      "copies of the Software, and to permit persons to whom the\n"
      "Software is furnished to do so, subject to the following\n"
      "conditions :\n"
      "\n"
      "The above copyright notice and this permission notice shall be\n"
      "included in all copies or substantial portions of the Software.\n"
      "\n"
      "THE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND,\n"
      "EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES\n"
      "OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND\n"
      "NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT\n"
      "HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,\n"
      "WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING\n"
      "FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR\n"
      "OTHER DEALINGS IN THE SOFTWARE.\n"
      "********************************************************************/"<<std::endl<<std::endl;
    source.push_front(ss.str());
    interface.push_front(ss.str());
    xslt.push_front(ss.str());
}


void xmlCppDecoder::createIfdef()
{
    std::stringstream ss;
    std::string hdef=single_name;
    std::transform(hdef.begin(),hdef.end(),hdef.begin(),::toupper);
    hdef+="_HEADER";
    ss<<"#ifndef "<<hdef<<std::endl;
    ss<<"#define "<<hdef<<std::endl;
    interface.push_front(ss.str());
    ss.str("");
    ss<<"#endif  //"<<hdef<<std::endl;
    header.push_back(ss.str());
}


void xmlCppDecoder::createIncludes()
{
    if (IOptionArgvManager::checkOption(f_namespace) )
    {
        std::stringstream ss;
        ss << "/// declare namespace " << getNameSpace()<< std::endl;
        ss << "namespace " << getNameSpace() << " {" << std::endl << std::endl << std::endl;
        interface.push_front(ss.str());
        source.push_front(ss.str());
        ss.str("");
        ss << "}; /// end namespace " << getNameSpace() <<std::endl;
        header.push_back(ss.str());
        source.push_back(ss.str());
    }

    std::stringstream ss;
    ss << "#include \"caminiXml.h\"" << std::endl;
    ss << "#include \"calcfxml.h\"" << std::endl;
    ss << "#include \"" << single_name << ".h\"" << std::endl << std::endl;
    source.push_front(ss.str());

}

void xmlCppDecoder::createInfoFile( IXmlNode* root )
{
    if (root!=nullptr && IOptionArgvManager::checkOption(f_addxmlinfo))
    {
        std::ofstream info;
        std::stringstream ss;
        info.open(file_info);
        if(info.is_open())
        {
            root->toString(ss,true,true);
            info<<ss.str();
            info.close();
        }
        else
        {
            ss<<"Cannot open "<<file_info<< "for output of decorate xml file"<<std::endl;
            throw std::runtime_error(ss.str());
        }
    }
}



void xmlCppDecoder::prepareForXslt()
{
    if(IOptionArgvManager::checkOption(f_createxslt))
    {
        std::stringstream ss;
        ss<<"<?xml version=\"1.0\"?>"<<std::endl;
        ss<<"<xs:schema xmlns:xs=\"http://www.w3.org/2001/XMLSchema\""<<std::endl;
        ss<<"elementFormDefault=\"qualified\">"<<std::endl;
        xslt.push_back(ss.str());
    }
}


void xmlCppDecoder::createXsltFile(IXmlNode *node)
{
    if(IOptionArgvManager::checkOption(f_createxslt))
    {
        createXslt(node);
        std::stringstream ss;
        ss<<"</xs:schema>"<<std::endl;
        xslt.push_back(ss.str());
    }
}

void xmlCppDecoder::finalizeForXslt()
{
    if(IOptionArgvManager::checkOption(f_createxslt))
    {
        std::ofstream outxslt(file_xslt);
        if(outxslt.is_open())
        {
            for(auto & it: xslt)
            {
                outxslt<<(it);
            }
            outxslt.close();
        }
    }
}

void xmlCppDecoder::createDebugFile(IXmlNode *node)
{
    if(IOptionArgvManager::checkOption(f_debug))
    {
        node->save(file_debug);
    }
}


void xmlCppDecoder::prepareNamespace()
{
    if(IOptionArgvManager::checkOption(f_namespace))
    {
        namesp_def=IOptionArgvManager::getInstance()->getOption(f_namespace).
                   getStringValue();
        if(!namesp_def.empty())
            namesp_dec=namesp_def+"::";
    }
}

bool xmlCppDecoder::compile(std::string filename)
{
    auto res=false;
    if(prepareOutFiles(filename))
    {
        miniXmlNode root("", "");
        if (root.load(filename))
        {
            prepareNamespace();
            prepareForXslt();
            createInfoFile(&root);
            root.save(file_xml);
            createXmlSource(&root);
            createDebugFile(&root);
            createXsltFile(&root);
            createIncludes();
            createTest(&root);
            createLicense();
            finalizeForXslt();
            createIfdef();
            xmlCppDecoder::saveToFile(file_h, interface);
            xmlCppDecoder::appendToFile(file_h, header);
            xmlCppDecoder::saveToFile(file_cpp, source);
            unsigned int lenfile = 0;
            const char *ptrFile = packManager::getFile_caminiXml_h(&lenfile);
            xmlCppDecoder::packToFile(path_in, "caminiXml.h",
                                      ptrFile, lenfile);
            ptrFile = packManager::getFile_calcfxml_h(&lenfile);
            xmlCppDecoder::packToFile(path_in, "calcfxml.h",
                                      ptrFile, lenfile);
            if (IOptionArgvManager::checkOption(f_addtest))
            {
                ptrFile = packManager::getFile_Makefile(&lenfile);
                xmlCppDecoder::packToFile(path_in, "Makefile",
                                          ptrFile, lenfile);
            }
        }
        else
        {
            std::stringstream ss;
            ss << "fail to load xml file : " << filename;
            throw std::runtime_error(ss.str());
        }
    }
    return res;
}

}



