
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

const CA::_cbt *ICAXml_Root_Node3::caKEY_B1 = "b1";
const CA::_cbt *ICAXml_Root_Node3::caKEY_B2 = "b2";
const CA::_cbt *ICAXml_Root_Node3::caKEY_B3 = "b3";
const CA::_cbt *ICAXml_Root_Node3::caKEY_B4 = "b4";
const CA::_cbt *ICAXml_Root_Node3::caKEY_B5 = "b5";
const CA::_cbt *ICAXml_Root_Node3::caKEY_B6 = "b6";
const CA::_cbt *ICAXml_Root_Node3::caKEY_B7 = "b7";
const CA::_cbt *ICAXml_Root_Node3::caKEY_B8 = "b8";
const CA::_cbt *ICAXml_Root_Node3::caKEY_B9 = "b9";
const CA::_cbt *ICAXml_Root_Node3::mName="node3";


CAXml_Root_Node3::CAXml_Root_Node3()
{
    predef.push_back(CA::xmlNodeSpec( caKEY_B1,"root.node3.b1",&b1));
    predef.push_back(CA::xmlNodeSpec( caKEY_B2,"root.node3.b2",&b2));
    predef.push_back(CA::xmlNodeSpec( caKEY_B3,"root.node3.b3",&b3));
    predef.push_back(CA::xmlNodeSpec( caKEY_B4,"root.node3.b4",&b4));
    predef.push_back(CA::xmlNodeSpec( caKEY_B5,"root.node3.b5",&b5));
    predef.push_back(CA::xmlNodeSpec( caKEY_B6,"root.node3.b6",&b6));
    predef.push_back(CA::xmlNodeSpec( caKEY_B7,"root.node3.b7",&b7));
    predef.push_back(CA::xmlNodeSpec( caKEY_B8,"root.node3.b8",&b8));
    predef.push_back(CA::xmlNodeSpec( caKEY_B9,"root.node3.b9",&b9));
}


const CA::_cbt *ICAXml_Root_Node2::caKEY_A1 = "a1";
const CA::_cbt *ICAXml_Root_Node2::caKEY_A2 = "a2";
const CA::_cbt *ICAXml_Root_Node2::caKEY_A3 = "a3";
const CA::_cbt *ICAXml_Root_Node2::caKEY_A4 = "a4";
const CA::_cbt *ICAXml_Root_Node2::caKEY_A5 = "a5";
const CA::_cbt *ICAXml_Root_Node2::caKEY_A6 = "a6";
const CA::_cbt *ICAXml_Root_Node2::caKEY_A7 = "a7";
const CA::_cbt *ICAXml_Root_Node2::caKEY_A8 = "a8";
const CA::_cbt *ICAXml_Root_Node2::caKEY_A9 = "a9";
const CA::_cbt *ICAXml_Root_Node2::mName="node2";


CAXml_Root_Node2::CAXml_Root_Node2()
{
    predef.push_back(CA::xmlNodeSpec( caKEY_A1,"root.node2.a1",&a1));
    predef.push_back(CA::xmlNodeSpec( caKEY_A2,"root.node2.a2",&a2));
    predef.push_back(CA::xmlNodeSpec( caKEY_A3,"root.node2.a3",&a3));
    predef.push_back(CA::xmlNodeSpec( caKEY_A4,"root.node2.a4",&a4));
    predef.push_back(CA::xmlNodeSpec( caKEY_A5,"root.node2.a5",&a5));
    predef.push_back(CA::xmlNodeSpec( caKEY_A6,"root.node2.a6",&a6));
    predef.push_back(CA::xmlNodeSpec( caKEY_A7,"root.node2.a7",&a7));
    predef.push_back(CA::xmlNodeSpec( caKEY_A8,"root.node2.a8",&a8));
    predef.push_back(CA::xmlNodeSpec( caKEY_A9,"root.node2.a9",&a9));
}


const CA::_cbt *ICAXml_Root_Node1::caKEY_PIPPO = "pippo";
const CA::_cbt *ICAXml_Root_Node1::caKEY_PLUTO = "pluto";
const CA::_cbt *ICAXml_Root_Node1::caKEY_TOPOLINO = "topolino";
const CA::_cbt *ICAXml_Root_Node1::mName="node1";


CAXml_Root_Node1::CAXml_Root_Node1()
{
    predef.push_back(CA::xmlNodeSpec( caKEY_PIPPO,"root.node1.pippo",&pippo));
    predef.push_back(CA::xmlNodeSpec( caKEY_PLUTO,"root.node1.pluto",&pluto));
    predef.push_back(CA::xmlNodeSpec( caKEY_TOPOLINO,"root.node1.topolino",&topolino));
}


const CA::_cbt *ICAXml_Root::caKEY_NODE1 = "node1";
const CA::_cbt *ICAXml_Root::caKEY_NODE2 = "node2";
const CA::_cbt *ICAXml_Root::caKEY_NODE3 = "node3";
const CA::_cbt *ICAXml_Root::caKEY_STEP = "step";
const CA::_cbt *ICAXml_Root::mName="root";


CAXml_Root::CAXml_Root()
{
    predef.push_back(CA::xmlNodeSpec( caKEY_NODE1,"root.node1",&node1.node_internal_value,&node1));
    predef.push_back(CA::xmlNodeSpec( caKEY_NODE2,"root.node2",&node2.node_internal_value,&node2));
    predef.push_back(CA::xmlNodeSpec( caKEY_NODE3,"root.node3",&node3.node_internal_value,&node3));
    predef.push_back(CA::xmlNodeSpec( caKEY_STEP,"root.step",&step));
}


bool CAXml_Root::loadFromXml(std::string filename)
{
    bool res=false;
    CA::IXmlNode *root=CA::IXmlNode::getNewNode();
    if(root->load(filename))
    {
        loadFromXmlNode(root);
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


