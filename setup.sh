#!/bin/bash

if [ ${1} ] ; then
    LIBNAME=${1}
    PREFIXNAME=${1}
    DEFINEPREFIX=${1}
    if [ ${2} ] ; then 
	PREFIXNAME=${2}
	DEFINEPREFIX=${2}
    fi
    if [ ${3} ] ; then
	DEFINEPREFIX=${3}
    fi

    echo "Renaming files"
    mv include/template.h include/${LIBNAME}.h
    mv src/template.c src/${LIBNAME}.c
    mv src/include/tmpl.h src/include/${PREFIXNAME}.h
    mv tests/tmpl-tests.h tests/${PREFIXNAME}-tests.h

    echo "Updating references"
    
    FILES="include/${LIBNAME}.h src/${LIBNAME}.c src/include/${PREFIXNAME}.h src/error.c tests/${LIBNAME}-tests.h tests/basic.cpp"

    for file in ${FILES} ; do
        cat ${file} | sed -e "s/template/${LIBNAME}/g" -e "s/tmpl/${PREFIXNAME}/g" -e "s/TMPL/${DEFINEPREFIX}/g" > ${file}-tmp
        mv ${file}-tmp $file
    done

    echo "Converting build script"
    cat premake4.lua | sed -e "s/template/${LIBNAME}/g" -e "s/TMPL/${DEFINEPREFIX}/g" > premake4.lua-tmp
    mv premake4.lua-tmp premake4.lua
else
    echo "usage: setup.sh LIBNAME [PREFIXNAME [DEFINEPREFIX]]"
fi
