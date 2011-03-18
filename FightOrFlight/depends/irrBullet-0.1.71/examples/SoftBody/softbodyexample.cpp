#include "softbodyexample.h"
#include <irrlicht.h>
#include <irrBullet.h>

using namespace irr;
using namespace core;
using namespace video;
using namespace scene;
using namespace io;
using namespace std;


CSoftbodyExample::CSoftbodyExample()
{
}



bool CSoftbodyExample::OnEvent(const SEvent& event)
{
	if (!device)
		return false;

    switch(event.EventType)
    {
        case EET_MOUSE_INPUT_EVENT:
        {
            if(event.MouseInput.Event==EMIE_LMOUSE_PRESSED_DOWN)
            {
                IRigidBody* body = shootCube(vector3df(10,10,10), 2);

                ICollisionObjectAffectorDelete *deleteAffector = new ICollisionObjectAffectorDelete(4000);
                body->addAffector(deleteAffector);
                return true;
            }

            else
            if(event.MouseInput.Event==EMIE_RMOUSE_PRESSED_DOWN)
            {
                IRigidBody* body = shootSphere(vector3df(0.2,0.2,0.2), 0.2);

                ICollisionObjectAffectorDelete *deleteAffector = new ICollisionObjectAffectorDelete(4000);
                body->addAffector(deleteAffector);
                return true;
            }
        }
        break;

        case EET_KEY_INPUT_EVENT:
        {
            if(event.KeyInput.Key == KEY_KEY_P && event.KeyInput.PressedDown == false)
            {
                world->pauseSimulation(!world->simulationPaused());
                return true;
            }
        }
        break;
        default:
            break;
    }
    return false;
}

void CSoftbodyExample::runExample()
{
    debugDraw = true;
    drawProperties = true;
    drawWireFrame = false;

    int choice = 1;
    int rows = 10;
    int columns = 10;

    printf("Select the softbody type: \n");
    printf("1 = Sphere\n2 = Newspaper(Aero)\n3 = Cloth\n4 = Feather(Aero)\n");
    cin >> choice;
    printf("Select the number of rows: \n");
    cin >> rows;
    printf("Select the number of columns: \n");
    cin >> columns;
    printf("Enable soft-soft collision?\n");
    cin >> softVersusSoft;

    device =
        createDevice( video::EDT_OPENGL, dimension2d<u32>(640, 480), 16,
            false, false, false, this);


    device->setWindowCaption(L"irrBullet Softbody Example");

    device->getFileSystem()->addFolderFileArchive("../../media/");


    ILightSceneNode* light = device->getSceneManager()->addLightSceneNode(0, vector3df(20, 40, -50), SColorf(1.0f, 1.0f, 1.0f), 4000.0f);
    light->setLightType(ELT_DIRECTIONAL);
    light->setRotation(vector3df(0,200,30));

    device->getSceneManager()->setAmbientLight(SColor(100,100,100,100));

    camera = device->getSceneManager()->addCameraSceneNodeFPS();
	camera->setPosition(vector3df(50,15,4));
	camera->setTarget(vector3df(0,0,0));


    ////////////////////////////
    // Create irrBullet World //
    ////////////////////////////
    world = createIrrBulletWorld(device, true, debugDraw);

    world->setDebugMode(EPDM_DrawAabb |
            EPDM_DrawContactPoints);

    world->setGravity(vector3df(0,-10,0));

    world->getSoftBodyWorldInfo().air_density = 0.05;

    createGround();


    for(u32 i=0; i < rows; i++)
    {
        for(u32 j=0; j < columns; j++)
            createSoftbodyType(choice, vector3df(56*(j+i), 200+i, 56*(j+i)));
    }
    //loadRoomScene();

    /*for(u32 i=1; i < 10; i++)
        createSoftbodyType(3, vector3df(106*i, 200+i, 106*i));*/

    //createSoftbodyType(4, vector3df(0,100,0));

    // Set our delta time and time stamp
    u32 TimeStamp = device->getTimer()->getTime();
    u32 DeltaTime = 0;
    while(device->run())
    {
        device->getVideoDriver()->beginScene(true, true, SColor(255,100,101,140));

        DeltaTime = device->getTimer()->getTime() - TimeStamp;
		TimeStamp = device->getTimer()->getTime();

		// Step the simulation with our delta time
        world->stepSimulation(DeltaTime*0.001f, 120);
        //static_cast<ISoftBody*>(world->getCollisionObjectByName("SOFTBODY1"))->addForce(vector3df(-2,0,0));


        //world->debugDrawWorld(debugDraw);
        // This call will draw the technical properties of the physics simulation
        // to the GUI environment.
        world->debugDrawProperties(drawProperties);


        device->getSceneManager()->drawAll();
        device->getGUIEnvironment()->drawAll();

        device->getVideoDriver()->endScene();
    }
    //delete water;

    // We're done with the IrrBullet world, so we free the memory that it takes up.
    if(world)
        delete world;

    if(device)
        device->drop();
}

// 1 = sphere, 2 = cube, 3 = plane, 4 = rope
ISoftBody* CSoftbodyExample::createSoftbodyType(u32 type, const vector3df& position)
{
    IMeshSceneNode* softbodyNode;
    switch(type)
    {
        case 1:
        {
            device->getSceneManager()->getMeshCache()->removeMesh(device->getSceneManager()->getMeshCache()->getMeshByName("sphere.b3d"));
            //IMesh* mesh = device->getSceneManager()->getGeometryCreator()->createSphereMesh();
            //softbodyNode = device->getSceneManager()->addCubeSceneNode(10.0f, 0, -1, vector3df(0, 0, 0), core::vector3df(0, 0, 0), vector3df(1.0f, 1.0f, 1.0f));
            IMesh* mesh = device->getSceneManager()->getMesh("sphere.b3d");

            //device->getSceneManager()->getMeshManipulator()->flipSurfaces(mesh);
            /*SMesh* newMesh = new SMesh();
            newMesh->addMeshBuffer(mesh->getMeshBuffer(0));
            printf("LINE 163\n");
            for(int i=1; i < mesh->getMeshBufferCount(); i++)
            {
                newMesh->getMeshBuffer(0)->append(mesh->getMeshBuffer(i));
            }*/

            softbodyNode = device->getSceneManager()->addMeshSceneNode(mesh);
            //softbodyNode = device->getSceneManager()->addSphereSceneNode(50.0f, 2, 0, -1, vector3df(0, 0, 0), vector3df(0, 0, 0), vector3df(1.0f, 1.0f, 1.0f));
            softbodyNode->setMaterialTexture(0, device->getVideoDriver()->getTexture("detailmap3.jpg"));
            softbodyNode->setAutomaticCulling(EAC_OFF);
            softbodyNode->setScale(vector3df(10,10,10));
            softbodyNode->setMaterialFlag(EMF_NORMALIZE_NORMALS, true);
        }
        break;

        case 2:
        {
            device->getSceneManager()->getMeshCache()->removeMesh(device->getSceneManager()->getMeshCache()->getMeshByName("newspaperMesh"));

            //IMesh* mesh = device->getSceneManager()->getMesh("newspaper.obj");

            IMesh* mesh = device->getSceneManager()->addHillPlaneMesh("newspaperMesh",
                core::dimension2d<f32>(22,22),
                core::dimension2d<u32>(3,3), 0, 0,
                core::dimension2d<f32>(0,0),
                core::dimension2d<f32>(1,1));

            //mesh->getMeshBuffer(0)->getMaterial().TextureLayer[0].TextureWrapU = ETC_CLAMP_TO_BORDER;
            //mesh->getMeshBuffer(0)->getMaterial().TextureLayer[0].TextureWrapV = ETC_CLAMP_TO_BORDER;


            softbodyNode = device->getSceneManager()->addMeshSceneNode(mesh);
            softbodyNode->setMaterialFlag(EMF_BACK_FACE_CULLING, false);
            softbodyNode->setMaterialTexture(0, device->getVideoDriver()->getTexture("newspaper.png"));

            softbodyNode->setAutomaticCulling(EAC_OFF);

            //IMeshSceneNode* softbodyNode = smgr->addMeshSceneNode(smgr->getMesh("dwarf.x"));
            //IMeshSceneNode* softbodyNode = smgr->addCubeSceneNode(10.0f, 0, -1, vector3df(0, 0, 0), core::vector3df(0, 0, 0), vector3df(1.0f, 1.0f, 1.0f));
            //IMeshSceneNode* softbodyNode = smgr->addSphereSceneNode(5.0f, 16, 0, -1, vector3df(0, 0, 0), vector3df(0, 0, 0), vector3df(1.0f, 1.0f, 1.0f));
        }
        break;

        case 3:
        {
            device->getSceneManager()->getMeshCache()->removeMesh(device->getSceneManager()->getMeshCache()->getMeshByName("myHill"));

            IMesh* mesh = device->getSceneManager()->addHillPlaneMesh("myHill",
                core::dimension2d<f32>(10,10),
                core::dimension2d<u32>(10,10), 0, 0,
                core::dimension2d<f32>(0,0),
                core::dimension2d<f32>(10,10));


            softbodyNode = device->getSceneManager()->addMeshSceneNode(mesh);
            softbodyNode->setMaterialFlag(EMF_BACK_FACE_CULLING, false);
            softbodyNode->setMaterialTexture(0, device->getVideoDriver()->getTexture("detailmap3.jpg"));

            softbodyNode->setRotation(vector3df(0,0,-90));

            softbodyNode->setAutomaticCulling(EAC_OFF);

            //IMeshSceneNode* softbodyNode = smgr->addMeshSceneNode(smgr->getMesh("dwarf.x"));
            //IMeshSceneNode* softbodyNode = smgr->addCubeSceneNode(10.0f, 0, -1, vector3df(0, 0, 0), core::vector3df(0, 0, 0), vector3df(1.0f, 1.0f, 1.0f));
            //IMeshSceneNode* softbodyNode = smgr->addSphereSceneNode(5.0f, 16, 0, -1, vector3df(0, 0, 0), vector3df(0, 0, 0), vector3df(1.0f, 1.0f, 1.0f));
        }
        break;

        case 4:
        {
            device->getSceneManager()->getMeshCache()->removeMesh(device->getSceneManager()->getMeshCache()->getMeshByName("featherMesh"));

            //IMesh* mesh = device->getSceneManager()->getMesh("newspaper.obj");

            IMesh* mesh = device->getSceneManager()->addHillPlaneMesh("featherMesh",
                core::dimension2d<f32>(22,22),
                core::dimension2d<u32>(1,4), 0, 0,
                core::dimension2d<f32>(0,0),
                core::dimension2d<f32>(1,1));

            //mesh->getMeshBuffer(0)->getMaterial().TextureLayer[0].TextureWrapU = ETC_CLAMP_TO_BORDER;
            //mesh->getMeshBuffer(0)->getMaterial().TextureLayer[0].TextureWrapV = ETC_CLAMP_TO_BORDER;


            softbodyNode = device->getSceneManager()->addMeshSceneNode(mesh);
            softbodyNode->setMaterialFlag(EMF_BACK_FACE_CULLING, false);
            softbodyNode->setMaterialTexture(0, device->getVideoDriver()->getTexture("feather.png"));
            softbodyNode->setMaterialType(EMT_TRANSPARENT_ALPHA_CHANNEL);


            softbodyNode->setAutomaticCulling(EAC_OFF);
        }
        break;
    }
    softbodyNode->setPosition(position);
    //softbodyNode->setRotation(vector3df(0,0,0));
    softbodyNode->setDebugDataVisible(EDS_BBOX);

    ISoftBody* softbody = world->addSoftBody(softbodyNode);

    softbody->setName("SOFTBODY1");
    softbody->setActivationState(EAS_DISABLE_DEACTIVATION);

    if(softVersusSoft)
    {
        softbody->generateClusters(60.0f);
        softbody->addCollisionFlag(ESBCM_CLUSTER_SOFT_VERSUS_SOFT);
    }

    switch(type)
    {
        case 1:
        {
            softbody->getConfiguration().poseMatchingCoefficient = 0.0;
            softbody->updateConfiguration();
        }
        break;

        case 2:
        {
            //softbody->getConfiguration().aeroModel = btSoftBody::eAeroModel::V_TwoSided;

            softbody->getConfiguration().liftCoefficient = 1.004;
            softbody->getConfiguration().dragCoefficient = 0.0003;
            softbody->getConfiguration().dampingCoefficient = 0.0;
            softbody->getConfiguration().aeroModel = ESBAM_VERTEX_TWO_SIDED;
            softbody->updateConfiguration();

            softbody->setTotalMass(0.001);
            softbody->setScale(vector3df(0.1,0.1,0.1));
        }
        break;

        case 3:
        {
            IRigidBody* body = addCube(bulletToIrrlichtVector(softbody->getPointer()->m_nodes[0].m_x), vector3df(1,1,1), 0.0f);
            softbody->appendAnchor(0, body, true);

            body = addCube(bulletToIrrlichtVector(softbody->getPointer()->m_nodes[20].m_x), vector3df(1,1,1), 0.0f);
            softbody->appendAnchor(20, body, true);
        }
        break;

        case 4:
        {
            //softbody->getConfiguration().aeroModel = btSoftBody::eAeroModel::V_TwoSided;

            softbody->getConfiguration().liftCoefficient = 1.004;
            softbody->getConfiguration().dragCoefficient = 0.0;
            softbody->getConfiguration().dampingCoefficient = 0.0;
            softbody->getConfiguration().aeroModel = ESBAM_VERTEX_TWO_SIDED;
            softbody->updateConfiguration();

            softbody->setTotalMass(0.00001);
            softbody->setScale(vector3df(0.1,0.1,0.1));
        }
        break;
    }

    return softbody;

}


CSoftbodyExample::~CSoftbodyExample()
{
    //dtor
}
