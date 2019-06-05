ca_qxmlc is a c++ code generator to load  in transparent mode any file xml.

With ca_qmlc You can :

1)from a generic xml input file generate all c++ classes needed to load any xml file with the same  schema . ex.

if You have the simple xml file:

<root>
     <node1>
          <elemet1>value1</element1> 
        <elemet2>value2</element2>
        <elemet3>value3</element3>
        <elemet4>value4</element4>
     </node1>
</root>

so You can access from generate code ex  to element3 with  the class CAXml_Root as CAXML_Root.node1.element3 (public access, std::string)

THERE ARE AN IMPORTANT LIMITATION OF XML FORMAT  :
ca_qxmlc REQUIRE A SINGLE VALUE FOR A NODE ex this node generate an error even it is a formally correct xml

<node1>I am node 1 
        <childnode> I am a child node </childnode> 
        this string  on node 1 is correct but ca_qxmlc parse return error 
</node1>


anyway the xml can be complex with attributes and array and nested array.

So to use the C++ generate code to modify a xml You can Load a xml file with method LoadFromXml ( std::string filename ) ,  modify it with direct access to members of  generated classes  and save it with the method toString (std::stringstream &ss) upon a file.

2) (experimental) You can generate the Xslt file derived from  the input xml file .( option --createxslt ) 

3)it is also possible generate a output xml file with more info or debug  (--addxmlinfo or --debug ) 

4) Alternative use of qxmlc. If you have to start with new project with require a file load or save of data
   starting with the definition of schema of xml. Create a minimal xml as schema and use qxmlc to generate main class.
   Derived Your code from this class. If in the future have to change xml schema have only to recreate via qxmlc
   the code and all youtr developper code will be untouch of changes.

VERSION  1.0 Beta 0

TO TRY do ./test.sh and watch the generated code into TEST_FILES/testxx


for any of TEST_FILES/testxx You can compile the generate code with Makefile ( make all ) and run : test_qxmlc <filexx.xml> . Try to change the value of any node in the <filexx.xml> and retry to load the file. Add or remove nodes in accordance of <filexx.xml.xslt> and test_qxmlc to verifiry if continue to load the <filexx.xml>.


compiled with:

gcc --version
gcc (Ubuntu 8.1.0-5ubuntu1~16.04) 8.1.0
Copyright (C) 2018 Free Software Foundation, Inc.


Beta version 00 .


This is free software; see the source for copying conditions.  There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

@Angelo Coppi
