
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

#include "caminiXml.h"
#include "calcfxml.h"
#include "model.h"

const CA::_cbt *ICAXml_Root_Node::caKEY_PIPPO = "pippo";
const CA::_cbt *ICAXml_Root_Node::caKEY_PLUTO = "pluto";
const CA::_cbt *ICAXml_Root_Node::caKEY_TOPOLINO = "topolino";
const CA::_cbt *ICAXml_Root_Node::caKEY_ZIOPAPERONE = "ziopaperone";
const CA::_cbt *ICAXml_Root_Node::mName="node";


CAXml_Root_Node::CAXml_Root_Node()
{
    predef.push_back(xmlNodeSpec( caKEY_PIPPO,"root.node.pippo",&pippo,&pippo_option));
    predef.push_back(xmlNodeSpec( caKEY_PLUTO,"root.node.pluto",&pluto,&pluto_option));
    predef.push_back(xmlNodeSpec( caKEY_TOPOLINO,"root.node.topolino",&topolino,&topolino_option));
    predef.push_back(xmlNodeSpec( caKEY_ZIOPAPERONE,"root.node.ziopaperone",&ziopaperone));
}


const CA::_cbt *ICAXml_Root::caKEY_NODE = "node";
const CA::_cbt *ICAXml_Root::mName="root";


CAXml_Root::CAXml_Root()
{
    predef.push_back(xmlNodeSpec( caKEY_NODE,"root.node",&node,&node_ref_clonable));
}


CAXml_Root::~CAXml_Root()
{
    LCFXml::deleteChildsArray(&node);
}


bool CAXml_Root::loadFromXml(std::string filename)
{
    bool res=false;
    CA::IXmlNode *root=CA::IXmlNode::getNewNode();
    if(root->load(filename))
    {
        loadFromXml(root);
        res=true;
    }
    delete root;
    return res;
}




int main(int argc,const CA::_cbt * argv[])
{
    CAXml_Root xmlDb;
    std::chrono::steady_clock::time_point t_start;
    std::chrono::steady_clock::time_point t_stop;
    if(argc==2)
    {
        try
        {
            std::string filename(argv[1]);
            t_start = std::chrono::steady_clock::now();
            if (xmlDb.loadFromXml(filename))
            {
                t_stop = std::chrono::steady_clock::now();
                std::cerr<<"parse Xml file :"<< filename <<" - "<<
                         (t_stop - t_start).count()<<" ns"<< std::endl;
                std::stringstream ss;
                t_start = std::chrono::steady_clock::now();
                xmlDb.toString(ss);
                t_stop = std::chrono::steady_clock::now();
                std::cerr<<"toString  - "<<
                         (t_stop - t_start).count()<<" ns"<< std::endl;
                std::cout<<ss.str().c_str();
                return 0;
            }
        }
        catch(std::runtime_error & e)
        {
            std::cerr<<e.what()<<std::endl;
        }
        catch(...)
        {
            std::cerr<<"Unknow exception "<<std::endl;
        }
    }
    else
    {
        ;
        std::cerr<<"usage : test_xml <file xml>"<< std::endl;
    }
    return -1;
}


