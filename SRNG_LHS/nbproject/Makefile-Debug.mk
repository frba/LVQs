#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/1555912452/ArffData.o \
	${OBJECTDIR}/_ext/988543167/DebugOut.o \
	${OBJECTDIR}/_ext/798864506/Defines.o \
	${OBJECTDIR}/_ext/798864506/StringHelper.o \
	${OBJECTDIR}/_ext/365430446/GRLVQ.o \
	${OBJECTDIR}/_ext/365430446/LVQ21.o \
	${OBJECTDIR}/_ext/365430446/NodeW.o \
	${OBJECTDIR}/_ext/365430446/SRNG.o \
	${OBJECTDIR}/_ext/1946162385/MatUtils.o \
	${OBJECTDIR}/_ext/918271420/LHSParameters.o \
	${OBJECTDIR}/_ext/918271420/Parameters.o \
	${OBJECTDIR}/main.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-Wno-comment
CXXFLAGS=-Wno-comment

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-lX11 -lpthread

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/srng_lhs

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/srng_lhs: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/srng_lhs ${OBJECTFILES} ${LDLIBSOPTIONS} -L/usr/X11/lib

${OBJECTDIR}/_ext/1555912452/ArffData.o: ../Libs/Data/ArffData.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1555912452
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../Libs/MatMatrix -I../Libs/SOM -I../Libs/Parameters -I../Libs/Debug -I../Libs/Defines -I../Libs/CImg -I../Libs/Cluster -I../Libs/Data -I. -I/opt/X11/include -I../Libs/LVQOLD -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1555912452/ArffData.o ../Libs/Data/ArffData.cpp

${OBJECTDIR}/_ext/988543167/DebugOut.o: ../Libs/Debug/DebugOut.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/988543167
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../Libs/MatMatrix -I../Libs/SOM -I../Libs/Parameters -I../Libs/Debug -I../Libs/Defines -I../Libs/CImg -I../Libs/Cluster -I../Libs/Data -I. -I/opt/X11/include -I../Libs/LVQOLD -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/988543167/DebugOut.o ../Libs/Debug/DebugOut.cpp

${OBJECTDIR}/_ext/798864506/Defines.o: ../Libs/Defines/Defines.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/798864506
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../Libs/MatMatrix -I../Libs/SOM -I../Libs/Parameters -I../Libs/Debug -I../Libs/Defines -I../Libs/CImg -I../Libs/Cluster -I../Libs/Data -I. -I/opt/X11/include -I../Libs/LVQOLD -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/798864506/Defines.o ../Libs/Defines/Defines.cpp

${OBJECTDIR}/_ext/798864506/StringHelper.o: ../Libs/Defines/StringHelper.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/798864506
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../Libs/MatMatrix -I../Libs/SOM -I../Libs/Parameters -I../Libs/Debug -I../Libs/Defines -I../Libs/CImg -I../Libs/Cluster -I../Libs/Data -I. -I/opt/X11/include -I../Libs/LVQOLD -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/798864506/StringHelper.o ../Libs/Defines/StringHelper.cpp

${OBJECTDIR}/_ext/365430446/GRLVQ.o: ../Libs/LVQOLD/GRLVQ.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/365430446
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../Libs/MatMatrix -I../Libs/SOM -I../Libs/Parameters -I../Libs/Debug -I../Libs/Defines -I../Libs/CImg -I../Libs/Cluster -I../Libs/Data -I. -I/opt/X11/include -I../Libs/LVQOLD -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/365430446/GRLVQ.o ../Libs/LVQOLD/GRLVQ.cpp

${OBJECTDIR}/_ext/365430446/LVQ21.o: ../Libs/LVQOLD/LVQ21.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/365430446
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../Libs/MatMatrix -I../Libs/SOM -I../Libs/Parameters -I../Libs/Debug -I../Libs/Defines -I../Libs/CImg -I../Libs/Cluster -I../Libs/Data -I. -I/opt/X11/include -I../Libs/LVQOLD -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/365430446/LVQ21.o ../Libs/LVQOLD/LVQ21.cpp

${OBJECTDIR}/_ext/365430446/NodeW.o: ../Libs/LVQOLD/NodeW.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/365430446
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../Libs/MatMatrix -I../Libs/SOM -I../Libs/Parameters -I../Libs/Debug -I../Libs/Defines -I../Libs/CImg -I../Libs/Cluster -I../Libs/Data -I. -I/opt/X11/include -I../Libs/LVQOLD -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/365430446/NodeW.o ../Libs/LVQOLD/NodeW.cpp

${OBJECTDIR}/_ext/365430446/SRNG.o: ../Libs/LVQOLD/SRNG.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/365430446
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../Libs/MatMatrix -I../Libs/SOM -I../Libs/Parameters -I../Libs/Debug -I../Libs/Defines -I../Libs/CImg -I../Libs/Cluster -I../Libs/Data -I. -I/opt/X11/include -I../Libs/LVQOLD -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/365430446/SRNG.o ../Libs/LVQOLD/SRNG.cpp

${OBJECTDIR}/_ext/1946162385/MatUtils.o: ../Libs/MatMatrix/MatUtils.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1946162385
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../Libs/MatMatrix -I../Libs/SOM -I../Libs/Parameters -I../Libs/Debug -I../Libs/Defines -I../Libs/CImg -I../Libs/Cluster -I../Libs/Data -I. -I/opt/X11/include -I../Libs/LVQOLD -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1946162385/MatUtils.o ../Libs/MatMatrix/MatUtils.cpp

${OBJECTDIR}/_ext/918271420/LHSParameters.o: ../Libs/Parameters/LHSParameters.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/918271420
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../Libs/MatMatrix -I../Libs/SOM -I../Libs/Parameters -I../Libs/Debug -I../Libs/Defines -I../Libs/CImg -I../Libs/Cluster -I../Libs/Data -I. -I/opt/X11/include -I../Libs/LVQOLD -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/918271420/LHSParameters.o ../Libs/Parameters/LHSParameters.cpp

${OBJECTDIR}/_ext/918271420/Parameters.o: ../Libs/Parameters/Parameters.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/918271420
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../Libs/MatMatrix -I../Libs/SOM -I../Libs/Parameters -I../Libs/Debug -I../Libs/Defines -I../Libs/CImg -I../Libs/Cluster -I../Libs/Data -I. -I/opt/X11/include -I../Libs/LVQOLD -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/918271420/Parameters.o ../Libs/Parameters/Parameters.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../Libs/MatMatrix -I../Libs/SOM -I../Libs/Parameters -I../Libs/Debug -I../Libs/Defines -I../Libs/CImg -I../Libs/Cluster -I../Libs/Data -I. -I/opt/X11/include -I../Libs/LVQOLD -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/srng_lhs

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
