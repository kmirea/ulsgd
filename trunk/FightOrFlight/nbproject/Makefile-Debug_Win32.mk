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
CC=gcc.exe
CCC=g++.exe
CXX=g++.exe
FC=gfortran.exe
AS=as.exe

# Macros
CND_PLATFORM=MinGW-Windows
CND_CONF=Debug_Win32
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/Types.o \
	${OBJECTDIR}/GameManager.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/NetworkManager.o \
	${OBJECTDIR}/NetworkObject.o \
	${OBJECTDIR}/WorldManager.o \
	${OBJECTDIR}/Client.o \
	${OBJECTDIR}/SceneLoader.o \
	${OBJECTDIR}/NetProtocolStruct.o \
	${OBJECTDIR}/Timer.o \
	${OBJECTDIR}/PhysicsObject.o \
	${OBJECTDIR}/ReferenceCountedObject.o \
	${OBJECTDIR}/Entity.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-Llib -lirrBullet -lBulletSoftBody -lBulletDynamics -lBulletCollision -lBulletMultiThreaded -lConvexDecomposition -lBulletSoftBodySolvers_CPU -lGIMPACTUtils -lLinearMath -lenet -lws2_32 -lwinmm -lIrrlicht.dll

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/fightorflight.exe

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/fightorflight.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/fightorflight ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/Types.o: Types.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -DDEBUG -Iinclude -Iinclude/bullet -MMD -MP -MF $@.d -o ${OBJECTDIR}/Types.o Types.cpp

${OBJECTDIR}/GameManager.o: GameManager.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -DDEBUG -Iinclude -Iinclude/bullet -MMD -MP -MF $@.d -o ${OBJECTDIR}/GameManager.o GameManager.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -DDEBUG -Iinclude -Iinclude/bullet -MMD -MP -MF $@.d -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/NetworkManager.o: NetworkManager.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -DDEBUG -Iinclude -Iinclude/bullet -MMD -MP -MF $@.d -o ${OBJECTDIR}/NetworkManager.o NetworkManager.cpp

${OBJECTDIR}/NetworkObject.o: NetworkObject.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -DDEBUG -Iinclude -Iinclude/bullet -MMD -MP -MF $@.d -o ${OBJECTDIR}/NetworkObject.o NetworkObject.cpp

${OBJECTDIR}/WorldManager.o: WorldManager.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -DDEBUG -Iinclude -Iinclude/bullet -MMD -MP -MF $@.d -o ${OBJECTDIR}/WorldManager.o WorldManager.cpp

${OBJECTDIR}/Client.o: Client.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -DDEBUG -Iinclude -Iinclude/bullet -MMD -MP -MF $@.d -o ${OBJECTDIR}/Client.o Client.cpp

${OBJECTDIR}/SceneLoader.o: SceneLoader.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -DDEBUG -Iinclude -Iinclude/bullet -MMD -MP -MF $@.d -o ${OBJECTDIR}/SceneLoader.o SceneLoader.cpp

${OBJECTDIR}/NetProtocolStruct.o: NetProtocolStruct.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -DDEBUG -Iinclude -Iinclude/bullet -MMD -MP -MF $@.d -o ${OBJECTDIR}/NetProtocolStruct.o NetProtocolStruct.cpp

${OBJECTDIR}/Timer.o: Timer.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -DDEBUG -Iinclude -Iinclude/bullet -MMD -MP -MF $@.d -o ${OBJECTDIR}/Timer.o Timer.cpp

${OBJECTDIR}/PhysicsObject.o: PhysicsObject.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -DDEBUG -Iinclude -Iinclude/bullet -MMD -MP -MF $@.d -o ${OBJECTDIR}/PhysicsObject.o PhysicsObject.cpp

${OBJECTDIR}/ReferenceCountedObject.o: ReferenceCountedObject.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -DDEBUG -Iinclude -Iinclude/bullet -MMD -MP -MF $@.d -o ${OBJECTDIR}/ReferenceCountedObject.o ReferenceCountedObject.cpp

${OBJECTDIR}/Entity.o: Entity.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -DDEBUG -Iinclude -Iinclude/bullet -MMD -MP -MF $@.d -o ${OBJECTDIR}/Entity.o Entity.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/fightorflight.exe

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
