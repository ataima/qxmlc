#include "caminiXml.h"
#include "caargopt.h"
#include "caargv.h"


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
#define WHITE "\e[1;37m"
#define GRAY_LIGHT "\e[0;37m"
#define GRAY_DARK "\e[1;30m"
#define BLUE "\e[0;34m"
#define BLUE_LIGHT "\e[1;34m"
#define GREEN "\e[0;32m"
#define GREEN_LIGHT "\e[1;32m"
#define CYAN "\e[0;36m"
#define CYAN_LIGHT "\e[1;36m"
#define RED "\e[0;31m"
#define RED_LIGHT "\e[1;31m"
#define PURPLE "\e[0;35m"
#define PURPLE_LIGHT "\e[1;35m"
#define BROWN "\e[0;33m"
#define YELLOW "\e[1;33m"
#define BLACK "\e[0;30m"
#define REPLACE "\e[0m"


typedef enum tag_optin_av
{
    f_help,
    f_get,
    f_set,
    f_create,
    f_out_xml,
    f_time,
    f_last_flags
} foptions;


static void Help(CA::IOptionArgvManager *manager)
{
    std::cout<<GREEN_LIGHT<<"Available commands :"<<REPLACE<<std::endl;
    for(const std::pair<const std::string ,CA::IOptionArgv *> & it : manager->getOptionsMap() )
    {
        std::cout<<it.first<<std::endl;
    }
    std::cout<<YELLOW<<"use --help  <command> to obtain more help"<<REPLACE<<std::endl;
    exit(0);
}


static void Help_get(CA::IOptionArgvManager *)
{
    std::cout<<GREEN_LIGHT<<"--get "<<REPLACE<<std::endl;
    std::cout<<"Return the value or attribute of node"<<std::endl;
    std::cout<<"syntax:"<<std::endl;
    std::cout<<YELLOW<<"--get \"( root.node1 )\""<<std::endl;
    std::cout<<REPLACE<<"\treturn the value of node root.node1"<<std::endl;
    std::cout<<YELLOW<<"--get \"( root.node1.node2 ? @value )\""<<std::endl;
    std::cout<<REPLACE<<"\treturn the value of node root.node1.node2"<<std::endl;
    std::cout<<YELLOW<<"--get \"( root.node1.node2 ? @attrib(id))\""<<std::endl;
    std::cout<<REPLACE<<"\treturn the value of attribute id of node root.node1.node2"<<std::endl;
    std::cout<<YELLOW<<"--get \"( root.node1.node2 ? @value#)\""<<std::endl;
    std::cout<<REPLACE<<"\treturn the len of string of value for node root.node1.node2"<<std::endl;
    std::cout<<YELLOW<<"--get \"( root.node1.node2 ? @value=='apple is for rich')\""<<std::endl;
    std::cout<<REPLACE<<"\treturn the result of test of the value for root.node1.node2"<<std::endl;
    std::cout<<YELLOW<<"--get \"( root.node1.node2 ? @attrib(id)==123)\""<<std::endl;
    std::cout<<REPLACE<<"\treturn the result of test of the value for root.node1.node2"<<std::endl;
    std::cout<<YELLOW<<"--get \"( root.node1.node2 ? @childs)\""<<std::endl;
    std::cout<<REPLACE<<"\treturn the childs node of root.node1.node2"<<std::endl;
    std::cout<<YELLOW<<"--get \"( root.node1.node2 ? @childs#)\""<<std::endl;
    std::cout<<REPLACE<<"\treturn the number of childs node of root.node1.node2"<<std::endl;
    std::cout<<YELLOW<<"--get \"(egg.conf ? @childs(editor) && .editor ? @value=='scite')\""<<std::endl;
    std::cout<<REPLACE<<"\tcheck if exist node editor on node egg.conf and also \n";
    std::cout<<REPLACE<<"\tcheck if the value of egg.conf.editor is scite"<<std::endl;
    std::cout<<GREEN_LIGHT<<"with && operator can execute more tests . ex:  "<<REPLACE<<std::endl;
    std::cout<<REPLACE<<"\t--get \"( root.node1.node2 ? @value==apple && . ? @attrib(price)==100 )"<<std::endl;
    std::cout<<REPLACE<<"\tfind node root.node1.node2 if value is apple, check the same node (.)\n"<<
             "\tand test if attrib price is 100, so print the bool result"<<std::endl;
    std::cout<<GREEN_LIGHT<<"for navigate on array nodes can use [nn] access ex." <<REPLACE<<std::endl;
    std::cout<<REPLACE<<"\t--get \"( root.node1[12].node2 ? @value==apple )\n"<<std::endl;
    std::cout<<REPLACE<<"\tcheck the value of 12^ node (node1)  of root (root) \n"<<std::endl;
    std::cout<<GREEN_LIGHT<<"tips:'.' is the same node of previous search "<<REPLACE<<std::endl;
    std::cout<<GREEN_LIGHT<<"tips:'..' is the parent node of the node of the previous search "<<REPLACE<<std::endl;
    std::cout<<GREEN_LIGHT<<"tips:'/' the search restart from main root node "<<REPLACE<<std::endl;
    std::cout<<GREEN_LIGHT<<"ex: ( root.node1 xxxx && . xxxx && .. xxxx && /root xxxx"<<REPLACE<<std::endl;
    std::cout<<GREEN_LIGHT<<"ex:  start at root.node1 -> remain on node1 -> return to root-> remain to root"<<REPLACE<<std::endl;
    exit(0);
}

static void Help_set(CA::IOptionArgvManager *)
{
    std::cout<<GREEN_LIGHT<<"--set"<<REPLACE<<std::endl;
    std::cout<<"add node or set the value / attribute"<<std::endl;
    std::cout<<"syntax:"<<std::endl;
    std::cout<<YELLOW<<"--set \"( root.node1 =@value(test))\""<<std::endl;
    std::cout<<REPLACE<<"\tset the value of node root.node1 to test"<<std::endl;
    std::cout<<YELLOW<<"--set \"( root.node1.node2 =@attrib(id,'unknow mode')\""<<std::endl;
    std::cout<<REPLACE<<"\tset the attrib id of root.node1.node2 node to 'unknow mode'"<<std::endl;
    std::cout<<YELLOW<<"--set \"( root.node1.node2 +@childs(node3,'check'))\""<<std::endl;
    std::cout<<REPLACE<<"\tadd a childs node node3 with value check at root.node1.node2 node"<<std::endl;
    std::cout<<YELLOW<<"--set \"( root.node1.node2 -@childs(node3))\""<<std::endl;
    std::cout<<REPLACE<<"\tremove the childs node node3 from root.node1.node2 node"<<std::endl;
    std::cout<<GREEN_LIGHT<<"with && operator can execute more tests . ex:  "<<REPLACE<<std::endl;
    std::cout<<REPLACE<<"\t--set \"( root.node1.node2 +@childs(nodeA) && . =@attrib(test,100) )"<<std::endl;
    std::cout<<REPLACE<<"\tadd the new node nodeA to  root.node1.node2 && set to the  same node (.)\n"<<
             "\tthe attribute test to value 100"<<std::endl;
    std::cout<<GREEN_LIGHT<<"add more node of same name create a array of node" <<REPLACE<<std::endl;
    std::cout<<GREEN_LIGHT<<"tips:'.' is the same node of previous search "<<REPLACE<<std::endl;
    std::cout<<GREEN_LIGHT<<"tips:'..' is the parent node of the node of the previous search "<<REPLACE<<std::endl;
    std::cout<<GREEN_LIGHT<<"tips:'/' the search restart from main root node "<<REPLACE<<std::endl;
    std::cout<<GREEN_LIGHT<<"ex: ( root.node1 xxxx && . xxxx && .. xxxx && /root xxxx"<<REPLACE<<std::endl;
    std::cout<<GREEN_LIGHT<<"ex:  start at root.node1 -> remain on node1 -> return to root-> remain to root"<<REPLACE<<std::endl;


    exit(0);
}


static void Help_create(CA::IOptionArgvManager *)
{
    std::cout<<GREEN_LIGHT<<"--create"<<REPLACE<<std::endl;
    std::cout<<"create a xml file with root node of name <name>"<<std::endl;
    std::cout<<"syntax:"<<std::endl;
    std::cout<<YELLOW<<"--create conf <file.xml> "<<std::endl;
    std::cout<<REPLACE<<"\tcreate the file.xml with content <conf/>\n"<<std::endl;
    std::cout<<REPLACE<<"\tA this point can add more node with --set operator\n"<<std::endl;
    exit(0);
}

static void Help_out_xml(CA::IOptionArgvManager *)
{
    std::cout<<GREEN_LIGHT<<"--outxml"<<REPLACE<<std::endl;
    std::cout<<"print the out in xml format"<<std::endl;
    std::cout<<"syntax:"<<std::endl;
    std::cout<<YELLOW<<"--outxml "<<std::endl;
    exit(0);
}

static void Help_time(CA::IOptionArgvManager *)
{
    std::cout<<GREEN_LIGHT<<"--time"<<REPLACE<<std::endl;
    std::cout<<"Return the time in ns of operation requested"<<std::endl;
    std::cout<<"syntax:"<<std::endl;
    std::cout<<YELLOW<<"--time "<<std::endl;
    exit(0);
}


typedef enum tag_token_type
{
    t_notype,
    t_end,              // isspace to terminate nodepath or expr
    t_dot,              // .
    t_ddot,             // ..
    t_root,             // /
    t_left,             // (
    t_right,            // )
    t_left_square,      // [
    t_right_square,     // ]
    t_any,              // *
    t_comma,            // ,
    t_test,             // ?
    t_eq,               // ==
    t_noteq,            // !=
    t_and,              // &&
    t_len,              // #
    t_add,              // +
    t_del,              // -
    t_assign,           // =
    t_number,           // number
    t_ident,            // ident
    t_key_childs ,      // @childs
    t_key_value,        // @value
    t_key_attrib,       // @attrib

} t_type;


typedef struct tag_token
{
    std::string ident;
    t_type type;
    std::string::size_type pos;
    tag_token()
    {
        type=t_notype;
        pos=0;
    }
} token;

typedef std::list<token> tokenList;
static void throw_error(const char *msg,size_t pos, std::string & expr)
{
    std::stringstream ss;
    ss<<std::endl<<REPLACE<<expr<<std::endl;
    if(pos < expr.size())
    {
        std::string::size_type  s=0;
        ss<<GREEN_LIGHT;
        while(s<pos)
        {
            ss<<"-";
            s++;
        }
        ss<<PURPLE;
        ss<<"^";
    }
    ss<<std::endl<<RED<<msg<<REPLACE;
    throw std::runtime_error(ss.str().c_str());

}





#define MODESET 1
#define MODEGET 0
static void tokenize(std::string & expr,tokenList &result, int mode )
{
    result.clear();
    std::string::size_type  pos=0;
    std::string tmp;
    int counter_lr=0;
    token t;
    char c;
    do
    {
        c=expr.at(pos);
        pos++;
    }
    while(::isspace(c));
    pos--;
    while(pos < expr.size())
    {
        tmp.clear();
        t.ident.clear();
        t.type=t_notype;
        c=expr.at(pos);
        if(mode==MODESET)
        {
            if(c=='-')
            {
                t.type=t_del;
                t.pos=pos;
                result.push_back(t);
                pos++;
                continue;
            }
            if(c=='+')
            {
                t.type=t_add;
                t.pos=pos;
                result.push_back(t);
                pos++;
                continue;
            }
            if(c=='=')
            {
                t.type = t_assign;
                t.pos=pos-1;
                result.push_back(t);
                pos++;
                continue;
            }
        }
        if(mode==MODEGET)
        {
            if(c=='#')
            {
                t.type=t_len;
                t.pos=pos;
                result.push_back(t);
                pos++;
                continue;
            }
            if(c=='?')
            {
                t.type=t_test;
                t.pos=pos;
                result.push_back(t);
                pos++;
                continue;
            }
            if(c=='=')
            {
                pos++;
                c=expr.at(pos);
                if(c=='=')
                {
                    t.type = t_eq;
                    t.pos=pos-1;
                    result.push_back(t);
                    pos++;
                    continue;
                }
                else
                {
                    std::stringstream ss;
                    ss<<pos<<" : Invalid expr == : missing =" ;
                    throw std::runtime_error(ss.str().c_str());
                }
            }
            if(c=='!')
            {
                pos++;
                c=expr.at(pos);
                if(c=='=')
                {
                    t.type = t_noteq;
                    t.pos=pos-1;
                    result.push_back(t);
                    pos++;
                    continue;
                }
                else
                {
                    std::stringstream ss;
                    ss<<pos<<" : Invalid expr == : missing =" ;
                    throw std::runtime_error(ss.str().c_str());
                }
            }
            if(c=='*')
            {
                t.type=t_any;
                t.pos=pos;
                result.push_back(t);
                pos++;
                continue;
            }
        }
        if(c=='.')
        {
            t.type=t_dot;
            t.pos=pos;
            result.push_back(t);
            pos++;
            c=expr.at(pos);
            if(c=='.')
            {
                t.type=t_ddot;
                t.pos=pos;
                pos++;
                result.pop_back();
                result.push_back(t);
                c=expr.at(pos);
                if(c=='.')
                {
                    throw_error("Syntax error , select . or .. ",pos,expr);
                }
            }
            continue;
        }
        if(c=='/')
        {
            t.type=t_root;
            t.pos=pos;
            result.push_back(t);
            pos++;
            counter_lr++;
            continue;
        }
        if(c=='(')
        {
            t.type=t_left;
            t.pos=pos;
            result.push_back(t);
            pos++;
            counter_lr++;
            continue;
        }
        if(c=='[')
        {
            t.type=t_left_square;
            t.pos=pos;
            result.push_back(t);
            pos++;
            continue;
        }
        if(c==')')
        {
            t.type=t_right;
            t.pos=pos;
            result.push_back(t);
            pos++;
            counter_lr--;
            if(counter_lr==0)
                break;
            continue;
        }

        if(c=='&')
        {
            pos++;
            c=expr.at(pos);
            if(c=='&')
            {
                t.type = t_and;
                t.pos=pos-1;
                result.push_back(t);
                pos++;
                continue;
            }
            else
            {
                std::stringstream ss;
                ss<<pos<<" : Invalid expr && : missing &" ;
                throw std::runtime_error(ss.str().c_str());
            }
        }
        if(c==']')
        {
            if(result.back().type==t_number)
            {
                t.type = t_right_square;
                t.pos = pos;
                result.push_back(t);
                pos++;
                continue;
            }
            else
            {
                throw_error("Insert ] after a number",pos,expr);
            }
        }
        if(c==',')
        {
            t.type=t_comma;
            t.pos=pos;
            result.push_back(t);
            pos++;
            continue;
        }
        if(c=='\'' )
        {
            std::string::size_type  tpos=pos;
            pos++;
            if(pos==expr.size())break;
            c=expr.at(pos);
            do
            {
                tmp+=c;
                pos++;
                if(pos==expr.size())break;
                c=expr.at(pos);
            }
            while(c!='\'');
            if(c!='\'')
            {
                throw_error("Missing '",tpos,expr);
            }
            t.type=t_ident;
            t.pos=tpos;
            t.ident=tmp;
            result.push_back(t);
            pos++;
            continue;
        }
        if(result.back().type==t_left_square && ::isdigit(c))
        {
            std::string::size_type  tpos=pos;
            do
            {
                tmp+=c;
                pos++;
                if(pos==expr.size())break;
                c=expr.at(pos);
            }
            while(::isdigit(c));
            t.type=t_number;
            t.pos=tpos;
            t.ident=tmp;
            result.push_back(t);
            continue;
        }
        if(::isalnum(c) || c=='_' || c=='-' || c=='@')
        {
            std::string::size_type  tpos=pos;
            do
            {
                tmp+=c;
                pos++;
                if(pos==expr.size())break;
                c=expr.at(pos);
            }
            while(::isalnum(c) || c=='_' || c=='-' || c=='@' );
            if(tmp.at(0)=='@')
            {
                if(tmp=="@value")t.type = t_key_value;
                else if(tmp=="@attrib")t.type = t_key_attrib;
                else if(tmp=="@childs")t.type = t_key_childs;
                else
                {
                    std::stringstream ss;
                    ss<<pos<<"Invalid expr keyword :" << tmp;
                    throw std::runtime_error(ss.str().c_str());
                }
            }
            else
            {
                t.type = t_ident;
                t.ident = tmp;
            }
            t.pos=tpos;
            result.push_back(t);
            continue;
        }
        // if here must be a space
        if(::isspace(c))
        {
            t.type=t_end;
            t.pos=pos;
            result.push_back(t);
            pos++;
            continue;
        }
        else
        {
            throw_error("Syntax error ",pos,expr);
        }
    }
    while(pos < expr.size())
    {
        c=expr.at(pos);
        pos++;
        if(::isspace(c))continue;
        throw_error("Syntax Error, chars after expression closure",pos,expr);
    }
}


static void trim(std::string & src, std::string &dst)
{
    std::string::iterator it=src.begin();
    std::string::iterator stop=src.end();
    while(it!=stop)
    {
        if(*it>' ')break;
        it++;
    }
    std::string::reverse_iterator rit=src.rbegin();
    std::string::reverse_iterator rstop=src.rend();
    while(rit!=rstop)
    {
        if(*rit>' ')break;
        rit++;
    }
    while(it!=rit.base())
    {
        dst.push_back(*it);
        it++;
    }
}


static void next_token(tokenList::iterator &it,
                       tokenList::iterator &stop,
                       std::string & expr,bool skip_space=false)
{
    if(it!=stop)it++;
    else
    {
        it--;
        throw_error("Incompltete --expr comand",it->pos,expr);
    }
    if(skip_space && it->type==t_end)
    {
        return next_token(it,stop,expr,skip_space);
    }
}


static bool apply_operator(std::string & input, std::string & test, token & op,t_type aux)
{
    bool res=false;
    if(aux==t_notype)
    {
        switch (op.type)
        {
        case t_eq:
            res = (input == test);
            break;
        case t_noteq:
            res = (input != test);
            break;
        default:
            break;
        }
    }
    else if(aux==t_len)
    {
        switch (op.type)
        {
        case t_eq:
            res = (input.size() == ::strtol(test.c_str(),nullptr,10));
            break;
        case t_noteq:
            res = (input .size() != ::strtol(test.c_str(),nullptr,10));
            break;
        default:
            break;
        }
    }
    return res;
}


static bool apply_operator_attribute(CA::IXmlNode *tmp,std::string & attribute, std::string & test, token & op,t_type aux)
{
    bool res=false;
    CA::optionsList & attributeList=tmp->getOptions();
    if(!attributeList.empty())
    {
        auto it=attributeList.find(attribute);
        if(it!=attributeList.end())
        {
            std::string & value=it->second;
            if (aux == t_notype)
            {
                switch (op.type)
                {
                case t_eq:
                    res = (value == test);
                    break;
                case t_noteq:
                    res = (value != test);
                    break;
                default:
                    break;

                }
            }
            else if (aux == t_len)
            {
                switch (op.type)
                {
                case t_eq:
                    res = (value.size() == ::strtol(test.c_str(),nullptr,10));
                    break;
                case t_noteq:
                    res = (value.size() != ::strtol(test.c_str(),nullptr,10));
                    break;
                default:
                    break;
                }
            }
        }
    }
    return res;
}



static CA::IXmlNode *navigateXml(CA::IXmlNode *tmp,
                                 std::string & ident,CA::xmlnodeList & res,
                                 tokenList::iterator &it,tokenList::iterator &stop,
                                 std::string & expr)
{

    token t;
    size_t rnode=0;
    res.clear();
    if(tmp->getName()==ident)
    {
        res.push_back(tmp);
        rnode=1;
    }
    else
        rnode=tmp->getChildNameList(ident,&res,nullptr);
    if(rnode==0)
    {
        it--;
        std::string decorate;
        tmp->getDiscendantDecorateName(decorate);
        std::string msg="Cannot find xml node : "+decorate+".("+ ident+")";
        throw_error(msg.c_str(),it->pos,expr);
    }
    else if(rnode==1)
    {
        tmp=res.back();
        next_token(it,stop,expr);
        t=*it;
        if(t.type==t_dot)
        {
            next_token(it, stop,expr);
            t = *it;
            if (t.type == t_ident)
                return navigateXml(tmp, t.ident,res, it, stop,expr);
            else
            {
                throw_error("Syntax Error after '.'",t.pos,expr);
            }
        }
        else if(t.type==t_ddot)
        {
            if(tmp->getParent()!=nullptr)
                tmp=tmp->getParent();
            next_token(it, stop,expr);
            t = *it;
            if (t.type == t_ident)
                return navigateXml(tmp, t.ident,res, it, stop,expr);
            else
            {
                throw_error("Syntax Error after '..'",t.pos,expr);
            }
        }
        else if(t.type==t_root)
        {
            while(tmp->getParent()!=nullptr)tmp=tmp->getParent();
            next_token(it, stop,expr);
            t = *it;
            if (t.type == t_ident)
                return navigateXml(tmp, t.ident,res, it, stop,expr);
            else
            {
                throw_error("Syntax Error after '/'",t.pos,expr);
            }
        }
        else if ( t.type == t_end   || t.type==t_assign ||
                  t.type==t_add     || t.type==t_del    ||  t.type==t_test)
        {
            return tmp;
        }
        else
        {
            throw_error("Syntax Error ",t.pos,expr);
        }
    }
    else
    {
        next_token(it,stop,expr);
        t=*it;
        if(t.type==t_left_square)
        {
            next_token(it,stop,expr);
            t = *it;
            if (t.type == t_number)
            {
                size_t index = ::strtol(t.ident.c_str(),nullptr,10);
                if (index >= res.size())
                {
                    std::stringstream ss;
                    ss << "Element at  [ " << t.ident << " ] : out of max bound " << res.size()-1;
                    throw_error(ss.str().c_str(),t.pos,expr);
                }
                else
                {

                    next_token(it, stop,expr);
                    t = *it;
                    if (t.type != t_right_square)
                    {
                        throw_error("Missing ] ",t.pos,expr);
                    }
                    else
                    {
                        tmp = res.at(index);
                        next_token(it, stop,expr);
                        t = *it;
                        if (t.type == t_dot)
                        {
                            next_token(it, stop,expr);
                            t = *it;
                            if (t.type == t_ident)
                                return navigateXml(tmp, t.ident,res, it, stop,expr);
                            else
                            {
                                throw_error("Syntax Error after '.' ",t.pos,expr);
                            }
                        }
                        else if (t.type == t_end || t.type==t_right)
                        {
                            res.clear();
                            res.push_back(tmp);
                            return tmp;
                        }
                        else if (t.type == t_ddot)
                        {
                            throw_error("Cannot switch to parent node is an array",t.pos,expr);
                        }
                        else if(t.type == t_root )
                        {
                            while(tmp->getParent()!=nullptr)tmp=tmp->getParent();
                            next_token(it, stop,expr);
                            t = *it;
                            if (t.type == t_ident)
                                return navigateXml(tmp, t.ident,res, it, stop,expr);
                            else
                            {
                                throw_error("Syntax Error after '/'",t.pos,expr);
                            }
                        }
                        else
                        {
                            throw_error("Syntax Error ",t.pos,expr);
                        }
                    }

                }
            }
            else
            {
                throw_error("Missing number ",t.pos,expr);
            }
        }
        else
        {
            //
            if(t.type==t_dot)
            {
                throw_error("Node Array, cannot enter on child node, use && expr ",t.pos,expr);
            }
            if(t.type!=t_end)
            {
                throw_error("Missing separator or [ or ]",t.pos,expr);
            }
            else if(t.type==t_ddot)
            {
                if(tmp->getParent()!=nullptr)
                    tmp=tmp->getParent();
                next_token(it, stop,expr);
                t = *it;
                if (t.type == t_ident)
                    return navigateXml(tmp, t.ident,res, it, stop,expr);
                else
                {
                    throw_error("Syntax Error after '..'",t.pos,expr);
                }
            }
            else if(t.type==t_root)
            {
                while(tmp->getParent()!=nullptr)tmp=tmp->getParent();
                next_token(it, stop,expr);
                t = *it;
                if (t.type == t_ident)
                    return navigateXml(tmp, t.ident,res, it, stop,expr);
                else
                {
                    throw_error("Syntax Error after '/'",t.pos,expr);
                }
            }
            else
            {
                /// resutl nodes in res list
                if(res.empty())
                    return nullptr;
                else
                    return res.front();
            }
        }
    }
    return nullptr;
}

static CA::IXmlNode * findNode(CA::IXmlNode *tmp,CA::xmlnodeList & res,
                               tokenList::iterator &it,tokenList::iterator &stop,std::string & expr)
{
    while (it!=stop)
    {
        token & t = *it;
        if(t.type==t_test)
        {
            break;
        }
        if(t.type==t_right)
        {
            break;
        }
        if(t.type==t_left || t.type==t_end)
        {
            next_token(it,stop,expr,true);
            continue;
        }
        else if(t.type==t_ident)
        {
            // --expr node1.node2.mnode3[4].node5
            tmp=navigateXml(tmp,t.ident,res,it,stop,expr);
            t=*it;
            if(t.type==t_end)
            {
                next_token(it,stop,expr,true);
            }
            break;
        }
        else if(t.type==t_any)
        {
            //  * all node childs of node input
            next_token(it,stop,expr);
            t=*it;
            if(t.type==t_end)
            {
                next_token(it,stop,expr,true);
                break;
            }
            else
            {
                throw_error("Syntax error  on * ",t.pos,expr);
            }
            tmp->getChildNameList("*",&res,nullptr);
            if(res.empty())
                tmp= nullptr;
            else
                tmp=res.front();
        }
        else if(t.type==t_dot)
        {
            // . this node
            res.clear();
            res.push_back(tmp);
            auto tit=it;
            next_token(it,stop,expr,true);
            if(it->type==t_ident)
            {
                continue;
            }
            else
            {
                it=tit;
                break;
            }
        }
        else if(t.type==t_ddot)
        {
            // .. parent node
            if(tmp->getParent()!=nullptr)
                tmp=tmp->getParent();
            res.clear();
            res.push_back(tmp);
            auto tit=it;
            next_token(it,stop,expr,true);
            if(it->type==t_ident)
            {
                continue;
            }
            else
            {
                it=tit;
                break;
            }
        }
        else if(t.type==t_root)
        {
            // .. parent node
            while(tmp->getParent()!=nullptr)
                tmp=tmp->getParent();
            res.clear();
            res.push_back(tmp);
            auto tit=it;
            next_token(it,stop,expr,true);
            if(it->type==t_ident)
            {
                continue;
            }
            else
            {
                it=tit;
                break;
            }
        }
        else
        {
            throw_error("Syntax error on xml node search...",t.pos,expr);
        }
    }
    return tmp;
}

static bool  recur_expr_eval_get(CA::IXmlNode *tmp, tokenList::iterator &it,
                                 tokenList::iterator &stop, std::string &expr);


static bool  eval_test_get_by_value(CA::IXmlNode *tmp,
                                    CA::xmlnodeList  & res,
                                    tokenList::iterator &it,
                                    tokenList::iterator &stop,
                                    std::string &expr,
                                    bool & op_res )
{
    if(res.empty())
    {
        op_res=false;
        return false;
    }
    t_type aux=t_notype;
    token &t =*it;
    next_token(it,stop,expr,true);
    t=*it;
    if(t.type==t_len)
    {
        next_token(it, stop, expr, true);
        t = *it;
        aux=t_len;
    }
    if( t.type==t_eq || t.type==t_noteq  )
    {
        token mode=t;
        next_token(it,stop,expr,true);
        t=*it;
        if(t.type==t_ident)
        {
            bool flg_continue=false;
            auto tit=it;
            next_token(it, stop, expr,true);
            if (it->type == t_and)flg_continue = true;
            it=tit;
            for(auto nX : res )
            {
                tmp=nX;
                std::string trimmed;
                trim(tmp->getValue(),trimmed);
                op_res=apply_operator(trimmed,t.ident,mode,aux);
                if (op_res)
                {
                    if (!flg_continue)
                    {
                        std::cout << "true" << std::endl;
                        return true;
                    }
                    else
                    {
                        next_token(it,stop,expr,true);
                        t=*it;
                        if(t.type==t_and)
                            next_token(it,stop,expr,true);
                        recur_expr_eval_get(tmp, it, stop, expr);
                        return false;
                    }
                }
                else
                {
                    std::cout << "false" << std::endl;
                    return false;
                }
            }
        }
        else
        {
            throw_error("Missing identifier ",t.pos,expr);
        }
    }
    else if(aux==t_len)
    {
        op_res=!tmp->getValue().empty();
        std::cout << tmp->getValue().size() << std::endl;
    }
    else if(t.type==t_end || t.type==t_comma || t.type==t_right)
    {
        std::cout<<tmp->getValue()<<std::endl;
    }
    return true;
}



static bool  eval_test_get_by_attribute(CA::IXmlNode *tmp,
                                        CA::xmlnodeList  & res,
                                        tokenList::iterator &it,
                                        tokenList::iterator &stop,
                                        std::string &expr,
                                        bool & op_res)
{
    if(res.empty())
    {
        op_res=false;
        return false;
    }
    std::string attribute_name;
    //"@attribute(pippo)==pluto"
    token &t =*it;
    next_token(it,stop,expr,true);
    t=*it;
    if(t.type!=t_left)
    {
        throw_error("Missing ( after attribute",t.pos,expr);
    }
    next_token(it,stop,expr,true);
    t=*it;
    if(t.type==t_ident)
    {
        attribute_name=t.ident;
    }
    else if(t.type==t_any)
    {
        attribute_name="";
    }
    else
    {
        throw_error("Missing indent or * to find attribute",t.pos,expr);
    }
    next_token(it,stop,expr,true);
    t=*it;
    if(t.type!=t_right)
    {
        throw_error("Missing ) after attribute",t.pos,expr);
    }
    t_type aux=t_notype;
    next_token(it,stop,expr,true);
    t=*it;
    if(t.type==t_len)
    {
        next_token(it, stop, expr, true);
        t = *it;
        aux=t_len;
    }
    if( t.type==t_eq || t.type==t_noteq  )
    {
        token mode=t;
        next_token(it,stop,expr,true);
        t=*it;
        if(t.type==t_ident)
        {
            bool flg_continue=false;
            auto tit=it;
            next_token(it, stop, expr,true);
            if (it->type == t_and)flg_continue = true;
            it=tit;
            for(auto nX : res )
            {
                tmp=nX;
                op_res=apply_operator_attribute(tmp,attribute_name,t.ident,mode,aux);
                if (op_res)
                {
                    if (!flg_continue)
                    {
                        std::cout << "true" << std::endl;
                        return true;
                    }
                    else
                    {
                        next_token(it,stop,expr,true);
                        t=*it;
                        if(t.type==t_and)
                            next_token(it,stop,expr,true);
                        recur_expr_eval_get(tmp, it, stop, expr);
                        return false;
                    }
                }
                else
                {
                    std::cout << "false" << std::endl;
                    return false;
                }
            }
        }
        else
        {
            throw_error("Missing identifier ",t.pos,expr);
        }
    }
    else if(aux==t_len)
    {
        op_res=false;
        CA::optionsList & attrList=tmp->getOptions();
        if(!attrList.empty())
        {
            if(attribute_name.empty())
            {
                op_res=false;
                for (auto & nn : attrList)
                {
                    std::cout << nn.second.size() << std::endl;
                    op_res |= !nn.second.empty();
                }
            }
            else
            {
                auto lit = attrList.find(attribute_name);
                if (lit != attrList.end())
                {
                    op_res = !lit->second.empty();
                    std::cout << lit->second.size() << std::endl;
                }
            }
        }
    }
    else if(t.type==t_end || t.type==t_comma || t.type==t_right)
    {
        op_res=false;
        CA::optionsList & attrList=tmp->getOptions();
        if(!attrList.empty())
        {
            if(attribute_name.empty())
            {
                for (auto & nn : attrList)
                {
                    op_res=true;
                    std::cout << nn.second << std::endl;
                }
            }
            else
            {
                auto lit = attrList.find(attribute_name);
                if (lit != attrList.end())
                {
                    op_res=true;
                    std::cout << lit->second << std::endl;
                }
            }
        }
    }
    return true;
}




static bool  eval_test_get_by_child(CA::IXmlNode *tmp,
                                    CA::xmlnodeList  & res,
                                    tokenList::iterator &it,
                                    tokenList::iterator &stop,
                                    std::string &expr,
                                    bool & op_res)
{
    //" @childs# -> num childs "
    //" @childs  -> lista childs "
    if(res.empty())
    {
        op_res=false;
        return false;
    }
    auto flg_continue=false;
    t_type aux=t_notype;
    std::string req_child;
    next_token(it,stop,expr,true);
    token & t=*it;
    if(t.type==t_len)
    {
        next_token(it, stop, expr, true);
        t = *it;
        aux=t_len;
    }
    if(t.type==t_left)
    {
        next_token(it, stop, expr, true);
        t = *it;
        if(t.type==t_ident)
        {
            req_child=t.ident;
            next_token(it, stop, expr, true);
            t = *it;
            if(t.type==t_right)
            {
                aux=t_test;
                next_token(it, stop, expr, true);
                t = *it;
            }
            else
            {
                throw_error("Missing )",t.pos,expr);
            }
        }
        else
        {
            throw_error("Request a ident to find in child nodes",t.pos,expr);
        }
    }
    if(t.type==t_end || t.type==t_and || t.type==t_right)
    {
        if(res.size()==1)
        {
            tmp=res.front();
            CA::xmlnodeList childs;
            if(aux!=t_test)
                tmp->getChildNameList("*",&childs,nullptr);
            else
                tmp->getChildNameList(req_child,&childs,nullptr);
            if(!childs.empty())
            {
                if (it->type == t_and)
                    flg_continue = true;
                if(!flg_continue)
                {
                    if (aux == t_len)
                    {
                        std::cout << childs.size() << std::endl;
                    }
                    else if (aux == t_test)
                    {
                        std::cout << true << std::endl;
                    }
                    else
                    {
                        for (auto &lit: childs)
                        {
                            std::cout << lit->getName() << std::endl;
                        }
                    }
                }
                else
                {
                    if(it->type==t_and)
                        next_token(it,stop,expr,true);
                    return recur_expr_eval_get(tmp, it, stop, expr);
                }
                op_res=true;
            }
            else
            {
                if (aux == t_len)
                {
                    std::cout << childs.size() << std::endl;
                    op_res=true;
                }
                else if(aux == t_test)
                {
                    std::cout << false << std::endl;
                    op_res=false;
                }

            }
        }
        else
        {
            throw_error (" Invalid use of @childs command on array ",t.pos,expr);
        }
    }

    return true;
}


static bool eval_test_get(CA::IXmlNode *tmp,
                          CA::xmlnodeList  & res,
                          tokenList::iterator &it,
                          tokenList::iterator &stop,
                          std::string &expr)
{
    bool op_res=true;
    token & t= *it;
    if(t.type!=t_test)
    {
        next_token(it, stop, expr, true);
        t = *it;
    }
    if(t.type!=t_test)
    {
        throw_error("Missing test key '?'",t.pos,expr);
    }
    while(it!=stop  && op_res)
    {
        t=*it;
        if(t.type==t_right)break;
        next_token(it,stop,expr,true);
        t=*it;
        if(t.type==t_key_value)
        {
            if (eval_test_get_by_value(tmp, res, it, stop, expr,op_res))continue;
            else
                break;
        }
        else if(t.type==t_key_attrib)
        {
            if (eval_test_get_by_attribute(tmp, res, it, stop, expr,op_res))continue;
            else
                break;
        }
        else if(t.type==t_key_childs)
        {
            if (eval_test_get_by_child(tmp, res, it, stop, expr,op_res))continue;
            else
                break;
        }
    }
    return op_res;
}





static bool  recur_expr_eval_get(CA::IXmlNode *tmp, tokenList::iterator &it,
                                 tokenList::iterator &stop, std::string &expr)
{
    CA::xmlnodeList  res;
    tmp=findNode(tmp,res,it,stop,expr);
    token & t=*it;
    if(it!=stop  && tmp!=nullptr && t.type!=t_right)
    {
        return eval_test_get(tmp,res,it,stop,expr);
    }
    else
    {
        //no expr
        if (CA::IOptionArgvManager::checkOption(f_out_xml))
        {
            tmp->print(stdout);
        }
        else
        {
            std::string decoratename;
            tmp->getDiscendantDecorateName(decoratename);
            std::cout << decoratename << "\t " << tmp->getValue() << std::endl;
        }

    }
    return false;
}






/////////////////////////////////////// SET ///////////////////////////////////////////////



static bool  eval_set_del_childs(CA::IXmlNode *tmp,
                                 CA::xmlnodeList  & res,
                                 tokenList::iterator &it,
                                 tokenList::iterator &stop,
                                 std::string &expr,
                                 bool & op_res)
{
    std::string child_name;
    std::string child_value;
    //--set ( root.nodexx - @childs(pippo,pluto))
    token &t =*it;
    next_token(it,stop,expr,true);
    t=*it;
    if(t.type!=t_left)
    {
        throw_error("Missing ( after childs",t.pos,expr);
    }
    next_token(it,stop,expr,true);
    t=*it;
    if(t.type!=t_ident)
    {
        throw_error("Missing  childs name",t.pos,expr);
    }
    child_name=t.ident;
    next_token(it,stop,expr,true);
    t=*it;
    if(t.type!=t_right)
    {
        throw_error("Missing ) after child name ",t.pos,expr);
    }
    for (auto &vit : res)
    {
        tmp=vit;
        tmp->remove(child_name);
    }
    next_token(it,stop,expr,true);
    return true;
}

static bool  eval_set_add_childs(CA::IXmlNode *tmp,
                                 CA::xmlnodeList  & res,
                                 tokenList::iterator &it,
                                 tokenList::iterator &stop,
                                 std::string &expr,
                                 bool & op_res)
{
    std::string child_name;
    std::string child_value;
    //--set ( root.nodexx + @childs(pippo,pluto))
    token &t =*it;
    next_token(it,stop,expr,true);
    t=*it;
    if(t.type!=t_left)
    {
        throw_error("Missing ( after childs",t.pos,expr);
    }
    next_token(it,stop,expr,true);
    t=*it;
    if(t.type!=t_ident)
    {
        throw_error("Missing  childs name",t.pos,expr);
    }
    child_name=t.ident;
    next_token(it,stop,expr,true);
    t=*it;
    if(t.type==t_comma)
    {
        next_token(it,stop,expr,true);
        t=*it;
        if(t.type!=t_ident)
        {
            throw_error("Missing  childs value",t.pos,expr);
        }
        child_value = t.ident;
        next_token(it, stop, expr, true);
        t = *it;
    }
    if(t.type!=t_right)
    {
        throw_error("Missing ) after child name or value",t.pos,expr);
    }
    for (auto & vit : res)
    {
        tmp=vit;
        tmp->add(child_name,child_value);
    }
    next_token(it,stop,expr,true);
    return true;
}


static bool  eval_set_by_attribute(CA::IXmlNode *tmp,
                                   CA::xmlnodeList  & res,
                                   tokenList::iterator &it,
                                   tokenList::iterator &stop,
                                   std::string &expr,
                                   bool & op_res)
{
    std::string attribute_name;
    std::string attribute_value;
    //--set ( root.nodexx="@attribute(pippo,pluto))
    token &t =*it;
    next_token(it,stop,expr,true);
    t=*it;
    if(t.type!=t_left)
    {
        throw_error("Missing ( after attribute",t.pos,expr);
    }
    next_token(it,stop,expr,true);
    t=*it;
    if(t.type!=t_ident)
    {
        throw_error("Missing  attribute name",t.pos,expr);
    }
    attribute_name=t.ident;
    next_token(it,stop,expr,true);
    t=*it;
    if(t.type!=t_comma)
    {
        throw_error("Missing , after attribute name",t.pos,expr);
    }
    next_token(it,stop,expr,true);
    t=*it;
    if(t.type!=t_ident)
    {
        throw_error("Missing  attribute name",t.pos,expr);
    }
    attribute_value=t.ident;
    next_token(it,stop,expr,true);
    t=*it;
    if(t.type!=t_right)
    {
        throw_error("Missing ) after attribute value",t.pos,expr);
    }
    CA::optionsList newOpt;
    std::pair<std::string,std::string > p(attribute_name,attribute_value);
    newOpt.insert(p);
    for (auto & vit : res)
    {
        tmp=vit;
        tmp->mergeOptions(newOpt);
    }
    next_token(it,stop,expr,true);
    return true;
}




static bool  eval_set_by_value(CA::IXmlNode *tmp,
                               CA::xmlnodeList  & res,
                               tokenList::iterator &it,
                               tokenList::iterator &stop,
                               std::string &expr,
                               bool & op_res )
{
    // --set ( root.nodexx=@value(pippo) )
    std::string value;
    token &t =*it;
    next_token(it,stop,expr,true);
    t=*it;
    if(t.type!=t_left)
    {
        throw_error("Missing ( ",t.pos,expr);
    }
    next_token(it,stop,expr,true);
    t=*it;
    if(t.type!=t_ident)
    {
        throw_error("Missing identifier ",t.pos,expr);
    }
    value=t.ident;
    next_token(it,stop,expr,true);
    t=*it;
    if(t.type!=t_right)
    {
        throw_error("Missing ) ",t.pos,expr);
    }
    for (auto & vit : res)
    {
        tmp=vit;
        tmp->setValue(value);
    }
    next_token(it,stop,expr,true);
    return true;
}


static bool  recur_expr_eval_set(CA::IXmlNode *tmp, tokenList::iterator &it,
                                 tokenList::iterator &stop, std::string &expr);



static bool eval_op_set(CA::IXmlNode *tmp,
                        CA::xmlnodeList  & res,
                        tokenList::iterator &it,
                        tokenList::iterator &stop,
                        std::string &expr)
{

    // set
    // --set (node.childs.pippo=@value(valore)) &&
    // --set (node.childs.pippo=@attrib(id,pippo) ) &&
    // --set (node.childs +@childs(mario,valore) ) && aggiunge un node mario
    // --set (node.childs -@childs(mario) ) && rimuove un node mario
    bool op_res=true;
    token & t= *it;
    while(it!=stop)
    {
        t = *it;
        if (t.type == t_and)
        {
            next_token(it, stop, expr, true);
            return recur_expr_eval_set(tmp, it, stop, expr);
        }
        if (t.type == t_right)break;
        if (t.type != t_add && t.type != t_del && t.type != t_assign)
        {
            next_token(it, stop, expr, true);
            t = *it;
        }
        if(t.type==t_assign)
        {
            next_token(it,stop,expr,true);
            t=*it;
            if(t.type==t_key_value)
            {
                if (eval_set_by_value(tmp, res, it, stop, expr,op_res))continue;
                else
                    break;
            }
            else if(t.type==t_key_attrib)
            {
                if (eval_set_by_attribute(tmp, res, it, stop, expr,op_res))continue;
                else
                    break;
            }
            else
            {
                throw_error("Missing @value or @attrib key",t.pos,expr);
            }
        }
        else if(t.type==t_add)
        {
            next_token(it,stop,expr,true);
            t=*it;
            if(t.type==t_key_childs)
            {
                if (eval_set_add_childs(tmp, res, it, stop, expr,op_res))continue;
                else
                    break;
            }
            else
            {
                throw_error("Missing @childs key",t.pos,expr);
            }
        }

        else if (t.type==t_del)
        {
            next_token(it,stop,expr,true);
            t=*it;
            if(t.type==t_key_childs)
            {
                if (eval_set_del_childs(tmp, res, it, stop, expr,op_res))continue;
                else
                    break;
            }
            else
            {
                throw_error("Missing @childs key",t.pos,expr);
            }
        }
        else
        {
            throw_error("Missing =,+,-",t.pos,expr);
        }


    }
    return op_res;
}



static bool  recur_expr_eval_set(CA::IXmlNode *tmp, tokenList::iterator &it,
                                 tokenList::iterator &stop, std::string &expr)
{
    CA::xmlnodeList res;
    tmp = findNode(tmp, res, it, stop, expr);
    token &t = *it;
    if (it != stop && tmp != nullptr && t.type != t_right)
    {
        return eval_op_set(tmp, res, it, stop, expr);
    }
    return false;
}




static int  eval_expr_get(CA::IXmlNode * node, std::string & expr)
{
    int res=0;
    CA::IXmlNode *tmp=node;
    tokenList result;
    tokenize(expr,result,MODEGET);
    auto it=result.begin();
    auto stop=result.end();
    if(result.begin()->type!=t_left)
    {
        throw_error("Syntax error  : missing '(' at start expr ",result.begin()->pos,expr);
    }
    if(result.rbegin()->type!=t_right)
    {
        throw_error("Syntax error  : missing ')' at end expr ",result.begin()->pos,expr);
    }
    if(!result.empty())
    {
        bool opres = recur_expr_eval_get(tmp,it,stop,expr);
        if(!opres)
        {
            res=-1;
        }
    }
    return res;
}


static int exec_func_get(CA::IXmlNode *node)
{
    std::string expr=CA::IOptionArgvManager::getInstance()->
                     getOption(f_get).getStringValue();
    if(!expr.empty())
    {
        int res= eval_expr_get(node,expr);
        return res;
    }
    return 0;
}



static int  eval_expr_set(CA::IXmlNode * node, std::string & expr)
{
    int res=0;
    CA::IXmlNode *tmp=node;
    tokenList result;
    tokenize(expr,result,MODESET);
    auto it=result.begin();
    auto rit=result.rbegin();
    auto stop=result.end();
    if(result.begin()->type!=t_left)
    {
        throw_error("Syntax error  : missing '(' at start expr ",result.begin()->pos,expr);
    }
    if(result.rbegin()->type!=t_right)
    {
        throw_error("Syntax error  : missing ')' at end expr ",result.begin()->pos,expr);
    }
    if(!result.empty())
    {
        bool opres = recur_expr_eval_set(tmp,it,stop,expr);
        if(!opres)
        {
            res=-1;
        }
    }
    return res;
}

static int exec_func_set(CA::IXmlNode *node)
{
    std::string expr=CA::IOptionArgvManager::getInstance()->
                     getOption(f_set).getStringValue();
    if(!expr.empty())
    {
        int res= eval_expr_set(node,expr);
        return res;
    }
    return 0;
}

static int exec ( const std::string & filename)
{


    if(filename.empty())return 1;
    CA::miniXmlNode root("","");
    if (CA::IOptionArgvManager::checkOption(f_create))
    {
        //--create name
        std::string nodename=CA::IOptionArgvManager::getInstance()->
                             getOption(f_create).getStringValue();
        root.setName(nodename);
        return !root.save(filename);
    }
    else
    {
        if (root.load(filename))
        {
            if (CA::IOptionArgvManager::checkOption(f_get)) return exec_func_get(&root);
            if (CA::IOptionArgvManager::checkOption(f_set))
            {
                if(!exec_func_set(&root))
                    return !root.save(filename);
                else
                    return 1;
            }
        }
        else
        {
            std::string msg="Cannot load xml file : "+ filename;
            throw_error(msg.c_str(),0,(std::string &)filename);
        }
    }
    return 1;
}

int main ( int argc , const char *argv[])
{
    std::chrono::steady_clock::time_point t_start;
    std::chrono::steady_clock::time_point t_stop;
    t_start = std::chrono::steady_clock::now();
    CA::argvManager::InitManager(f_last_flags);
    CA::IOptionArgvManager * instance=CA::IOptionArgvManager::getInstance();
    instance->addOption(new CA::optionArgvBoolParser(f_help, "--help", Help));
    instance->addOption(new CA::optionArgvStringParser(f_get, "--get", Help_get));
    instance->addOption(new CA::optionArgvStringParser(f_set, "--set", Help_set));
    instance->addOption(new CA::optionArgvStringParser(f_create, "--create", Help_create));
    instance->addOption(new CA::optionArgvBoolParser(f_out_xml, "--outxml", Help_out_xml));
    instance->addOption(new CA::optionArgvBoolParser(f_time, "--time", Help_time));

    if(argc==1)
    {
        instance->getOption(f_help).getHelpFunctor()(instance);
        exit(0);
    }
    try
    {
        instance->Parse(argv, argc);
    }
    catch (std::runtime_error & e)
    {
        // trow exception with --help in input pass exception...
        if(!instance->getOption(f_help).isSelect())
        {
            std::cerr<<RED_LIGHT<<"Exception : "<<e.what()<<std::endl;
            exit(-1);
        }
    }
    catch(...)
    {
        std::cerr<<RED_LIGHT<<"Unknow Exception "<<std::endl;
        exit(-1);
    }
    if(instance->getOption(f_help).isSelect())
    {
        if(instance->getOption(f_get).isSelect())
        {
            instance->getOption(f_get).getHelpFunctor()(instance);
        }
        else if(instance->getOption(f_set).isSelect())
        {
            instance->getOption(f_set).getHelpFunctor()(instance);
        }
        else if(instance->getOption(f_create).isSelect())
        {
            instance->getOption(f_set).getHelpFunctor()(instance);
        }
        else if(instance->getOption(f_time).isSelect())
        {
            instance->getOption(f_time).getHelpFunctor()(instance);
        }
        else
            instance->getOption(f_help).getHelpFunctor()(instance);
        return 0;
    }
    else
    {
        if( ! instance->getArgs().empty())
        {
            for ( auto & it : instance->getArgs())
            {
                try
                {
                    int res=exec(it);
                    t_stop = std::chrono::steady_clock::now();
                    if(instance->getOption(f_time).isSelect())
                    {
                        std::cerr<<"elapsed time : "<<
                                 (t_stop - t_start).count()<<" ns"<< std::endl;
                    }
                    return res;

                }
                catch (std::runtime_error & e)
                {
                    std::cerr<<RED_LIGHT<<"Error : "<<REPLACE<<e.what()<<std::endl;
                    exit(-1);
                }
                catch(...)
                {
                    std::cerr<<RED_LIGHT<<"Unknow Exception "<<std::endl;
                    exit(-1);
                }
            }
        }
    }
    return 0;
}
