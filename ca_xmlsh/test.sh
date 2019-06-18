#!/bin/sh

make install

EXEC=""


if [ -e ../Debuglinux64 ]
then
    EXEC="../Debuglinux64/caxml  "
else
if [ -e ../Debuglinux32 ]
then
    EXEC="../Debuglinux32/caxml "
else
if [ -e ../Releaselinux64 ]
then
    EXEC="../Releaselinux64/caxml - "
else
if [ -e ../Releaselinux32 ]
then
    EXEC="../Releaselinux32/caxml  "
else
    error_c "No exec " "file " "available"
 fi
fi
fi
fi





#!/bin/bash  

#Colors
WHITE=" -e \E[1;37m"
GRAY_LIGHT=" -e \E[0;37m"
GRAY_DARK=" -e \E[1;30m"
BLUE=" -e \E[0;34m"
BLUE_LIGHT=" -e \E[1;34m"
GREEN=" -e \E[0;32m"
GREEN_LIGHT=" -e \E[1;32m"
CYAN=" -e \E[0;36m"
CYAN_LIGHT=" -e \E[1;36m"
RED=" -e \E[0;31m"
RED_LIGHT=" -e \E[1;31m"
PURPLE=" -e \E[0;35m"
PURPLE_LIGHT=" -e \E[1;35m"
BROWN=" -e \E[0;33m"
YELLOW=" -e \E[1;33m"
BLACK=" -e \E[0;30m"
REPLACE=" -e \E[0m"




#PUBLIC FUNCTION EXPORTED TO ALL GENERATED SCRIPTS 
#$1 color
#$2   string
function print_c(){ #EX
echo -e $(echo $1) "$2" $(echo $3) "$4"$(echo $5) "$6" $(echo $REPLACE)
} #EX


# $1..3 argv
function print_s_ita(){ #EX
local A1=$(printf "%-20s" "$1")
local A2=$(printf "%-20s" "$2")
local A3=$(printf "%-20s" "$3")
echo  $(echo $GREEN_LIGHT) "$A1" $(echo $WHITE) "$A2" $(echo $RED_LIGHT) "$A3" $(echo $REPLACE)
} #EX




#none
function print_del_ita(){ #EX
print_s_ita "--------------------" "--------------------" "--------------------"
} #EX

# $1..3 argv
function print_ita(){ #EX
print_del_ita
print_s_ita "$1" "$2" "$3"
} #EX

#$1   string
#$2   string
#$3   string
function error_c(){ #EX
print_del_ita
print_c "$RED_LIGHT" "ERROR : " "$BLUE_LIGHT" " - $1" 
if [ "$2" ]; then
	print_c "$WHITE" "	> " "$YELLOW" "- $2" 
	if [ "$3" ]; then
		print_c "$WHITE" "	> " "$YELLOW" "- $3" 
		if [ "$4" ]; then
			print_c "$WHITE" "	> " "$YELLOW" "- $4" 
			if [ "$5" ]; then
				print_c "$WHITE" "	> " "$YELLOW" "- $5" 
				if [ "$6" ]; then
					print_c "$WHITE" "	> " "$YELLOW" "- $6" 
				fi
			fi	
		fi
	fi
fi
print_c "$GRAY_DARK" "PATH  :" "$GRAY_LIGHT" $(pwd)
print_c "$GRAY_DARK" "FILE  :" "$GRAY_LIGHT" "$0"
print_c "$GRAY_DARK" "LINE  :" "$GRAY_LIGHT" "${BASH_LINENO[0]}"
print_del_ita
#TO DO ITERATIVE 
if [ $ITERATIVE -eq 0 ]; then
	exit 1
fi
} #EX


NTEST=1
OKTEST=0
KOTEST=0


OUTPATH=/tmp

#$1 0 ok else bad
function check_result_ok(){
if [ $1 -ne 0 ]
then
    print_c "$RED_LIGHT" "ERROR :" "$PURPLE_LIGHT" "TEST $NTEST" "$CYAN" "FAILED !"
    KOTEST=$((KOTEST+1))
else
    print_c "$GREEN_LIGHT"  "TEST $NTEST OK! "
    OKTEST=$((OKTEST+1))
fi
}


function check_result_ko(){
if [ $1 -eq 0 ]
then
    print_c "$RED_LIGHT" "ERROR :" "$PURPLE_LIGHT" "TEST $NTEST" "$CYAN" "FAILED !"
    KOTEST=$((KOTEST+1))
else
    print_c "$GREEN_LIGHT"  "TEST $NTEST OK! "
    OKTEST=$((OKTEST+1))
fi
}


#$1 ex --get  
#$2 expr content
#$3 file
function oktest(){
print_del_ita
$EXEC --time "$1"  "$2" $OUTPATH/$3
T=$?
#echo "----> $T"
check_result_ok $T
NTEST=$((NTEST+1))
}


#$1 ex --get 
#$2 expr content
#$3 file
function kotest(){
print_del_ita
$EXEC --time "$1"  "$2" $OUTPATH/$3
T=$?
check_result_ko $T
NTEST=$((NTEST+1))
}

function report(){
print_c "$YELLOW"  "TEST TOTALI : $NTEST" "$RED_LIGHT" "FALLITI : $KOTEST" "$GREEN_LIGHT" "OK : $OKTEST"
}


#create node on xml
oktest "--create" "root_node" filetest.xml
# add nodes
oktest "--set" "( root_node +@childs(node1,'value node 1'))" filetest.xml
oktest "--set" "( root_node +@childs(node2,'value node 2'))" filetest.xml
oktest "--set" "( root_node +@childs(node3,'value node 3'))" filetest.xml
oktest "--set" "( root_node.node1  =@attrib(name,pluto))" filetest.xml
rm -rf  $OUTPATH/filetest.xml

#create node on xml
oktest "--create" "root_node" filetest.xml
oktest "--set" "( root_node +@childs(node,'value node 1'))" filetest.xml
oktest "--set" "( root_node +@childs(node,'value node 2'))" filetest.xml
oktest "--set" "( root_node +@childs(node,'value node 3'))" filetest.xml
oktest "--set" "( root_node.node[2]  =@attrib(name,pluto))" filetest.xml
oktest "--get" "( root_node.node[2]  ? @attrib(name)==pluto )" filetest.xml
oktest "--get" "( root_node.node[2]  ? @childs# )" filetest.xml

oktest "--create" "root" file1.xml
oktest "--set" "(root =@value('root value') )" file1.xml
oktest "--set" "(root +@childs(pippo,'io sono pippo') )" file1.xml
oktest "--set" "(root +@childs(pluto,'io sono pluto') )" file1.xml
oktest "--set" "(root +@childs(topolino,'io sono topolino     ') )" file1.xml

cat $OUTPATH/file1.xml

oktest "--get" "(root ? @value )" file1.xml
oktest "--get" "(root? @value )" file1.xml
oktest "--get" "(root ?@value )" file1.xml
oktest "--get" "(root?@value )" file1.xml

oktest "--get" "( root.pippo ? @value )" file1.xml
oktest "--get" "( root.pippo? @value )" file1.xml
oktest "--get" "( root.pippo ?@value )" file1.xml
oktest "--get" "( root.pippo?@value )" file1.xml

oktest "--get" "( root.pluto ? @value )" file1.xml
oktest "--get" "( root.pluto? @value )" file1.xml
oktest "--get" "( root.pluto ?@value )" file1.xml
oktest "--get" "( root.pluto?@value )" file1.xml

oktest "--get" "( root.topolino ? @value )" file1.xml
oktest "--get" "( root.topolino? @value )" file1.xml
oktest "--get" "( root.topolino ?@value )" file1.xml
oktest "--get" "( root.topolino?@value )" file1.xml


oktest "--get" "(root ? @value# )" file1.xml
oktest "--get" "(root? @value# )" file1.xml
oktest "--get" "(root ?@value# )" file1.xml
oktest "--get" "(root?@value# )" file1.xml

oktest "--get" "( root.pippo ? @value# )" file1.xml
oktest "--get" "( root.pippo? @value# )" file1.xml
oktest "--get" "( root.pippo ?@value# )" file1.xml
oktest "--get" "( root.pippo?@value# )" file1.xml

oktest "--get" "( root.pluto ? @value# )" file1.xml
oktest "--get" "( root.pluto? @value# )" file1.xml
oktest "--get" "( root.pluto ?@value# )" file1.xml
oktest "--get" "( root.pluto?@value# )" file1.xml

oktest "--get" "( root.topolino ? @value# )" file1.xml
oktest "--get" "( root.topolino? @value# )" file1.xml
oktest "--get" "( root.topolino ?@value# )" file1.xml
oktest "--get" "( root.topolino?@value# )" file1.xml

oktest "--get" "( root   ?   @value#==10 )" file1.xml
oktest "--get" "(root? @value# == 10 )" file1.xml
oktest "--get" "(root ?@value#== 10 )" file1.xml
oktest "--get" "(root?@value# == 10 )" file1.xml

kotest "--get" "( root   ?   @value#==11 )" file1.xml
kotest "--get" "(root? @value# == 11 )" file1.xml
kotest "--get" "(root ?@value#== 12 )" file1.xml
kotest "--get" "(root?@value# == 13 )" file1.xml

kotest "--get" "( root.mario?@value )" file1.xml

oktest "--get" "( root ? @childs )" file1.xml
oktest "--get" "( root ? @childs# )" file1.xml

rm -rf  $OUTPATH/file1.xml

oktest "--create" "root" file1.xml
oktest "--set" "(root =@value('value') && . =@attrib(i1,1) && . =@attrib(name,mario) && . +@childs(node1) && . +@childs(node2) && . +@childs(node3))" file1.xml
cat $OUTPATH/file1.xml

kotest "--set"  "(root.node1 =@value('value1') && root.node2 =@value( value2 ))" file1.xml
cat $OUTPATH/file1.xml
oktest "--set"  "(root.node1=@value('value1') && .=@attrib(id,2))" file1.xml
kotest "--get"  "(root.node1 @value  && . @attrib)  " file1.xml
oktest "--get"  " ( root.node1 ? @value  && . ? @attrib(*) ) " file1.xml


#todo add fix : .. return at parent of node 
oktest "--set"  "(root.node1 =@value('value1') && ..node2 =@value( value2 ))" file1.xml
#todo add fix : / return to root min node
oktest "--set"  "(root.node1=@value('value1') && /root.node2=@value( value2 ))" file1.xml

rm -rf $OUTPATH/file1.xml


oktest "--create" "root" file1.xml
kotest "--set" "(root =@value('value') && . =@attrib(i1,1) && . =@attrib(name,mario) && . +@childs(node1) && . +@childs(node2) && . +@childs(node3)) && /root.node1=@vale(prova1) && .=@attrib(mode,test1) && .=@attrib(type,22) && /root.node2=@vale(picopo) && .=@attrib(mode,trillo) && .=@attrib(type,casa) && root.node3=@vale(popo) && .=@attrib(mode,trick) && .=@attrib(type,brick))" file1.xml
kotest "--set" "(root =@value('value') && . =@attrib(i1,1) && . =@attrib(name,mario) && . +@childs(node1) && . +@childs(node2) && . +@childs(node3) && /root.node1=@vale(prova1) && .=@attrib(mode,test1) && .=@attrib(type,22) && /root.node2=@vale(picopo) && .=@attrib(mode,trillo) && .=@attrib(type,casa) && root.node3=@vale(popo) && .=@attrib(mode,trick) && .=@attrib(type,brick))" file1.xml
kotest "--set" "(root =@value('value') && . =@attrib(i1,1) && . =@attrib(name,mario) && . +@childs(node1) && . +@childs(node2) && . +@childs(node3) && /root.node1=@value(prova1) && .=@attrib(mode,test1) && .=@attrib(type,22) && /root.node2=@value(picopo) && .=@attrib(mode,trillo) && .=@attrib(type,casa) && root.node3=@value(popo) && .=@attrib(mode,trick) && .=@attrib(type,brick))" file1.xml
oktest "--set" "(root =@value('value') && . =@attrib(i1,1) && . =@attrib(name,mario) && . +@childs(node1) && . +@childs(node2) && . +@childs(node3) && /root.node1=@value(prova1) && .=@attrib(mode,test1) && .=@attrib(type,22) && /root.node2=@value(picopo) && .=@attrib(mode,trillo) && .=@attrib(type,casa) && /root.node3=@value(popo) && .=@attrib(mode,trick) && .=@attrib(type,brick))" file1.xml
report 
