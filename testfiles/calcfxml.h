#ifndef LCF_XML_HEADER
#define LCF_XML_HEADER


#ifdef _DOUBLE_UNICODE
typedef  char32_t     _cbt;
#else
#ifdef _UNICODE
typedef  char16_t     _cbt;
#else
typedef  char     _cbt;
#endif
#endif



class IKeyValue;
class IClonable;
class IClonableOption;


typedef struct node_simple
{
    std::string *simple;
} nodeSimple;

typedef struct node_simple_with_option
{

    std::string *simple;
    CA::optionsList *options;
} nodeOption;


typedef struct node_simple_array_tag
{
    std::vector <std::string> *array;
} nodeArray;


typedef struct node_simple_array_with_option_tag
{
    std::vector <CA::pairValue> *array;
} nodeArrayOption;

typedef struct node_child_tag
{
    std::string *value;
    IKeyValue * childs;
} nodeChild;

typedef struct node_child_with_option_tag
{
    std::string *value;
    CA::optionsList *options;
    IKeyValue * childs;
} nodeChildOption;


typedef struct node_child_array_tag
{
    std::vector <IClonable *  > *childs_array;
    IClonable * obj;
} nodeChildArray;

typedef struct node_child_array_tag_with_option
{
    std::vector <IClonableOption *  > *childs_array;
    IClonableOption * obj;
} nodeChildArrayOption;

typedef union tag_access_data
{
    nodeSimple S;
    // inode simple with option
    nodeOption O;
    //inode_array
    nodeArray N;
    //inode_array with option
    nodeArrayOption W;
    // inode_childs
    nodeChild C;
    // inode_childs with option
    nodeChildOption F;
    // inode_childs_array
    nodeChildArray A;
    // inode_childs_array with option
    nodeChildArray Y;
    // inode_childs_array with option
    nodeChildArrayOption Z;
} dataAccessType ;


#define DEBUG_XML_NODE_SPEC 0

class xmlNodeSpec
{
public:
    std::string name;
    std::string fullname;
    CA::IXmlNode::xmlNodeType type;
    dataAccessType        D;
    explicit xmlNodeSpec( const _cbt * _name ,const _cbt * qualified,std::string  *_simple):
        name(_name),
        fullname(qualified)
    {
#if DEBUG_XML_NODE_SPEC
        std::cout<<"Name : "<<_name<< " : inode_simple"<<" ( "<<qualified<<" )"<<std::endl;
#endif
        type=CA::IXmlNode::xmlNodeType::inode_simple;
        memset(&D,0,sizeof(dataAccessType));
        D.S.simple=_simple;
    }
    explicit xmlNodeSpec( const _cbt * _name ,const _cbt * qualified,std::string  *_simple,
                          CA::optionsList * optl):
        name(_name),
        fullname(qualified)
    {
#if DEBUG_XML_NODE_SPEC
        std::cout<<"Name : "<<_name<< " : inode_simple_with_options"<<" ( "<<qualified<<" )"<<std::endl;
#endif
        type= CA::IXmlNode::xmlNodeType::inode_simple_with_options;
        memset(&D,0,sizeof(dataAccessType));
        D.O.simple=_simple;
        D.O.options=optl;
    }
    explicit xmlNodeSpec(const _cbt * _name ,const _cbt * qualified,std::vector <std::string> *_array ):
        name(_name),
        fullname(qualified)
    {
#if DEBUG_XML_NODE_SPEC
        std::cout<<"Name : "<<_name<< " : inode_array"<<" ( "<<qualified<<" )"<<std::endl;
#endif
        type=CA::IXmlNode::xmlNodeType::inode_array;
        memset(&D,0,sizeof(dataAccessType));
        D.N.array=_array;
    }
    explicit xmlNodeSpec(const _cbt * _name ,const _cbt * qualified,std::vector <CA::pairValue> *_array ):
        name(_name),
        fullname(qualified)
    {
#if DEBUG_XML_NODE_SPEC
        std::cout<<"Name : "<<_name<< " : inode_array_with_options"<<" ( "<<qualified<<" )"<<std::endl;
#endif
        type=CA::IXmlNode::xmlNodeType::inode_array_with_options;
        memset(&D,0,sizeof(dataAccessType));
        D.W.array=_array;
    }
    explicit xmlNodeSpec( const _cbt * _name ,const _cbt * qualified,std::string  *_simple,
                          IKeyValue * _childs ):
        name(_name),
        fullname(qualified)
    {
#if DEBUG_XML_NODE_SPEC
        std::cout<<"Name : "<<_name<< " : inode_childs"<<" ( "<<qualified<<" )"<<std::endl;
#endif
        type=CA::IXmlNode::xmlNodeType::inode_childs;
        memset(&D,0,sizeof(dataAccessType));
        D.C.value=_simple;
        D.C.childs=_childs;
    }
    explicit xmlNodeSpec( const _cbt * _name ,const _cbt * qualified,std::string  *_simple,
                          IKeyValue * _childs ,CA::optionsList * optl):
        name(_name),
        fullname(qualified)
    {
#if DEBUG_XML_NODE_SPEC
        std::cout<<"Name : "<<_name<< " : inode_childs_with_options"<<" ( "<<qualified<<" )"<<std::endl;
#endif
        type=CA::IXmlNode::xmlNodeType::inode_childs_with_options;
        memset(&D,0,sizeof(dataAccessType));
        D.F.value=_simple;
        D.F.childs=_childs;
        D.F.options=optl;
    }

    explicit xmlNodeSpec(const _cbt * _name ,const _cbt * qualified,
                         std::vector <IClonable *  > *_childs_array,
                         IClonable *_base):
        name(_name),
        fullname(qualified)
    {
#if DEBUG_XML_NODE_SPEC
        std::cout<<"Name : "<<_name<< " : inode_array_childs"<<" ( "<<qualified<<" )"<<std::endl;
#endif
        type=CA::IXmlNode::xmlNodeType::inode_array_childs;
        memset(&D,0,sizeof(dataAccessType));
        D.A.childs_array=_childs_array;
        D.A.obj=_base;
    }
    explicit xmlNodeSpec(const _cbt * _name ,const _cbt * qualified,
                         std::vector <IClonableOption *  > *_childs_array,
                         IClonableOption *_base):
        name(_name),
        fullname(qualified)
    {
#if DEBUG_XML_NODE_SPEC
        std::cout<<"Name : "<<_name<< " : inode_array_childs_with_options"<<" ( "<<qualified<<" )"<<std::endl;
#endif
        type=CA::IXmlNode::xmlNodeType::inode_array_childs_with_options;
        memset(&D,0,sizeof(dataAccessType));
        D.Z.childs_array=_childs_array;
        D.Z.obj=_base;
    }
};


typedef std::list< xmlNodeSpec > keyList;

class IKeyValue
{
public:
    virtual const _cbt * getICAXml_Name_Value()=0;
    virtual keyList *  getICAXml_Predef_List()=0;
    virtual void  loadFromXml(CA::IXmlNode * node)=0;
    virtual ~IKeyValue()=default;
};

class IClonable
    :public  IKeyValue
{
public:
    virtual IClonable* clone()=0;
    virtual const _cbt * getInternalValue()=0;
    virtual void setInternalValue(std::string &str) =0;
    virtual ~IClonable()=default;
};


class IClonableOption
    :public  IClonable
{
public:
    virtual CA::optionsList & getOptionsList()=0;
    virtual void setOptionList(CA::optionsList & newlist)=0;
    virtual ~IClonableOption()=default;
};



class LCFXml
{
public:
    static void  loadFromXml(CA::IXmlNode *node,IKeyValue *obj);
    static void  copyOptions(CA::optionsList * src,CA::optionsList * dest);
    static void  toString(std::stringstream &ss,CA::optionsList * optl);
    static void  toString(std::stringstream &ss,IKeyValue *obj,std::string &parent);
    static void  deleteChildsArray(std::vector<IClonable *> *objs);
    static void  deleteChildsArray(std::vector<IClonableOption *> *objs);
    static void  setError(CA::IXmlNode *node,std::string what,std::string & name,std::string & fullname);
    static void  setWarning(CA::IXmlNode *node,std::string  what,std::string & name,std::string & fullname);
    static bool  checkOptions(CA::IXmlNode::xmlNodeType one , CA::IXmlNode::xmlNodeType two);
};


#endif
