#ifndef DOC_MACRO_INCLUDED
#define DOC_MACRO_INCLUDED

/**************************************************************
Copyright(c) 2005 Angelo Coppi

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

#ifdef _SAFE_MEMORY_LEAK
#define _START()			{MemoryValidator::disableRecordMem();}
#define _STOP()				{MemoryValidator::enableRecordMem();}
#else
#define _START()
#define _STOP()
#endif


#define _INFO(a)			{result[currentTest]->add(const_cast<char *>("Doc"),const_cast<char *>("Objective"),a);}
#define _INFO1(a,b)			{result[currentTest]->add(const_cast<char *>("Doc"),const_cast<char *>("Objective"),a,b);}
#define _INFO2(a,b,c)		{result[currentTest]->add(const_cast<char *>("Doc"),const_cast<char *>("Objective"),a,b,c);}
#define _CONF(a)			{result[currentTest]->add(const_cast<char *>("Doc"),const_cast<char *>("Conf_override"),a);}
#define _CONF1(a,b)			{result[currentTest]->add(const_cast<char *>("Doc"),const_cast<char *>("Conf_override"),a,b);}
#define _CONF2(a,b,c)		{result[currentTest]->add(const_cast<char *>("Doc"),const_cast<char *>("Conf_override"),a,b,c);}
#define _INPUT(a)			{result[currentTest]->add(const_cast<char *>("Doc"),const_cast<char *>("Input_data"),a);}
#define _INPUT1(a,b)		{result[currentTest]->add(const_cast<char *>("Doc"),const_cast<char *>("Input_data"),a,b);}
#define _INPUT2(a,b,c)		{result[currentTest]->add(const_cast<char *>("Doc"),const_cast<char *>("Input_data"),a,b,c);}
#define _REQ(a)			    {result[currentTest]->add(const_cast<char *>("Doc"),const_cast<char *>("Output_req"),a);}
#define _REQ1(a,b)			{result[currentTest]->add(const_cast<char *>("Doc"),const_cast<char *>("Output_req"),a,b);}
#define _REQ2(a,b,c)		{result[currentTest]->add(const_cast<char *>("Doc"),const_cast<char *>("Output_req"),a,b,c);}
#define _CODE(a)			{result[currentTest]->add(const_cast<char *>("Doc"),const_cast<char *>("Code_req"),a);}
#define _CODE1(a,b)			{result[currentTest]->add(const_cast<char *>("Doc"),const_cast<char *>("Code_req"),a,b);}
#define _CODE2(a,b,c)		{result[currentTest]->add(const_cast<char *>("Doc"),const_cast<char *>("Code_req"),a,b,c);}
#define _RESULT(a)			{result[currentTest]->add(const_cast<char *>("Doc"),const_cast<char *>("Result"),a);}
#define _RESULT1(a,b)		{result[currentTest]->add(const_cast<char *>("Doc"),const_cast<char *>("Result"),a,b);}
#define _RESULT2(a,b,c)		{result[currentTest]->add(const_cast<char *>("Doc"),const_cast<char *>("Result"),a,b,c);}
#define _FAIL(a)			{result[currentTest]->add(const_cast<char *>("Doc"),const_cast<char *>("Failure_reason"),a);}
#define _FAIL1(a,b)			{result[currentTest]->add(const_cast<char *>("Doc"),const_cast<char *>("Failure_reason"),a,b);}
#define _FAIL2(a,b,c)		{result[currentTest]->add(const_cast<char *>("Doc"),const_cast<char *>("Failure_reason"),a,b,c);}
#define _ENCLOSES(a)		{result[currentTest]->add(const_cast<char *>("Doc"),const_cast<char *>("Encloses"),a);}
#define _ENCLOSES1(a,b)		{result[currentTest]->add(const_cast<char *>("Doc"),const_cast<char *>("Encloses"),a,b);}
#define _ENCLOSES2(a,b,c)	{result[currentTest]->add(const_cast<char *>("Doc"),const_cast<char *>("Encloses"),a,b,c);}
#define _AUTHOR(a)			{result[currentTest]->add(const_cast<char *>("Doc"),const_cast<char *>("Author"),a);}
#define _AUTHOR1(a,b)		{result[currentTest]->add(const_cast<char *>("Doc"),const_cast<char *>("Author"),a,b);}
#define _AUTHOR2(a,b,c)		{result[currentTest]->add(const_cast<char *>("Doc"),const_cast<char *>("Author"),a,b,c);}
#define _IMAGE(a)			{result[currentTest]->add(const_cast<char *>("Doc"),const_cast<char *>("Image"),a);}


#endif
