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
    sed -e "s/template/${LIBNAME}/g" -e "s/tmpl/${PREFIXNAME}/g" -e "s/TMPL/${DEFINEPREFIX}/g" -i include/${LIBNAME}.h
    sed -e "s/template/${LIBNAME}/g" -e "s/tmpl/${PREFIXNAME}/g" -e "s/TMPL/${DEFINEPREFIX}/g" -i src/${LIBNAME}.c
    sed -e "s/template/${LIBNAME}/g" -e "s/tmpl/${PREFIXNAME}/g" -e "s/TMPL/${DEFINEPREFIX}/g" -i src/include/${PREFIXNAME}.h
    sed -e "s/template/${LIBNAME}/g" -e "s/tmpl/${PREFIXNAME}/g" -e "s/TMPL/${DEFINEPREFIX}/g" -i src/error.c
    sed -e "s/template/${LIBNAME}/g" -e "s/tmpl/${PREFIXNAME}/g" -e "s/TMPL/${DEFINEPREFIX}/g" -i tests/${LIBNAME}-tests.h
    sed -e "s/template/${LIBNAME}/g" -e "s/tmpl/${PREFIXNAME}/g" -e "s/TMPL/${DEFINEPREFIX}/g" -i tests/basic.cpp

    echo "Converting build script"
    sed -e "s/template/${LIBNAME}/g" -e "s/TMPL/${DEFINEPREFIX}/g" -i premake4.lua
else
    echo "usage: setup.sh LIBNAME [PREFIXNAME [DEFINEPREFIX]]"
fi
