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
FC=
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_CONF=Release_Linux
CND_DISTDIR=dist

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=build/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/main.o


# C Compiler Flags
CFLAGS=`pkg-config --cflags irrBullet cAudio` 

# CC Compiler Flags
CCFLAGS=`pkg-config --cflags irrBullet cAudio` 
CXXFLAGS=`pkg-config --cflags irrBullet cAudio` 

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-Release_Linux.mk dist/Release_Linux/GNU-Linux-x86/fightorflight

dist/Release_Linux/GNU-Linux-x86/fightorflight: ${OBJECTFILES}
	${MKDIR} -p dist/Release_Linux/GNU-Linux-x86
	${LINK.cc} `pkg-config --libs irrBullet cAudio` -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/fightorflight  ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/main.o main.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/Release_Linux
	${RM} dist/Release_Linux/GNU-Linux-x86/fightorflight

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
