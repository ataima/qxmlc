#include <pybind11/pybind11.h>
#include "caminiXml.h"
#include "calcfxml.h"
#include "model.h"



PYBIND11_MODULE(ca_xml_lib, m ) {
pybind11::class_<CAXml_Base>(m, "CAXml_Base" )
. def (pybind11::init<>())
. def ( "getICAXml_Name_Value" , &CAXml_Base::getICAXml_Name_Value )
. def ( "loadFromXml" , &CAXml_Base::loadFromXml )
. def_readwrite ( "node_internal_value" , &CAXml_Base::node_internal_value ) ;
}

