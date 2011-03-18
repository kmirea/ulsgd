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
CND_CONF=Debug_Linux
CND_DISTDIR=dist

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=build/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/Types.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/NetworkObject.o \
	${OBJECTDIR}/ReferenceCountedObject.o


# C Compiler Flags
CFLAGS=`pkg-config --cflags irrBullet cAudio enet` 

# CC Compiler Flags
CCFLAGS=`pkg-config --cflags irrBullet cAudio enet` 
CXXFLAGS=`pkg-config --cflags irrBullet cAudio enet` 

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-Debug_Linux.mk dist/Debug_Linux/GNU-Linux-x86/fightorflight

dist/Debug_Linux/GNU-Linux-x86/fightorflight: ${OBJECTFILES}
	${MKDIR} -p dist/Debug_Linux/GNU-Linux-x86
	${LINK.cc} `pkg-config --libs irrBullet cAudio enet` -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/fightorflight  ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/Types.o: Types.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/Types.o Types.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/NetworkObject.o: NetworkObject.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/NetworkObject.o NetworkObject.cpp

${OBJECTDIR}/ReferenceCountedObject.o: ReferenceCountedObject.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/ReferenceCountedObject.o ReferenceCountedObject.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/Debug_Linux
	${RM} dist/Debug_Linux/GNU-Linux-x86/fightorflight

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
