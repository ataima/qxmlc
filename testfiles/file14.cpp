#include "caminiXml.h"
#include "calcfxml.h"
#include "file14.h"

const _cbt*  ICAXml_Root_Node::caKEY_PIPPO = "pippo";
const _cbt*  ICAXml_Root_Node::caKEY_PLUTO = "pluto";
const _cbt*  ICAXml_Root_Node::caKEY_TOPOLINO = "topolino";
const _cbt*  ICAXml_Root_Node::caKEY_ZIOPAPERONE = "ziopaperone";
const _cbt*  ICAXml_Root_Node::mName="node";


CAXml_Root_Node::CAXml_Root_Node(){
    predef.push_back(xmlNodeSpec( caKEY_PIPPO,"root.node.pippo",&pippo,&pippo_option));
    predef.push_back(xmlNodeSpec( caKEY_PLUTO,"root.node.pluto",&pluto,&pluto_option));
    predef.push_back(xmlNodeSpec( caKEY_TOPOLINO,"root.node.topolino",&topolino,&topolino_option));
    predef.push_back(xmlNodeSpec( caKEY_ZIOPAPERONE,"root.node.ziopaperone",&ziopaperone));
}


const _cbt*  ICAXml_Root::caKEY_NODE = "node";
const _cbt*  ICAXml_Root::mName="root";


CAXml_Root::CAXml_Root(){
    predef.push_back(xmlNodeSpec( caKEY_NODE,"root.node",&node,&node_ref_clonable));
}


CAXml_Root::~CAXml_Root()
{
    LCFXml::deleteChildsArray(&node);
}


bool CAXml_Root::loadFromXml(std::string filename){
bool res=false;
CA::IXmlNode *root=CA::IXmlNode::getNewNode();
if(root->load(filename)){
    loadFromXml(root);
    res=true;
   }
delete root;
return res;
}

