from distutils.core import setup, Extension

ca_xml_lib_module = Extension('ca_xml_lib',
                    define_macros = [('MAJOR_VERSION', '1'),
                                     ('MINOR_VERSION', '0')],
                    include_dirs = ['./inc'],
                    libraries = ['ca_logger_static','xmlca_static'],
                    library_dirs = ['./libs'],
                    extra_compile_args=['-std=c++14'],
                    sources = ['src/model.cpp'])

setup (name = 'ca_xml_lib',
       version = '1.0',
       description = 'package to read xml from caqxml xml to c compiler',
       author = 'Angelo Coppi',
       author_email = 'angelogkcop@hotmail.com',
       url = 'https://github.com/ataima/qxmlc',
       long_description = '''
       copy your xml to decode on model.xml in this path.
       Running ./create_dylib.sh model.xml
       into ./dist path shared lib_ca_xml-lib.so for c++ users
        or   module for python users
''',
       ext_modules = [ca_xml_lib_module])