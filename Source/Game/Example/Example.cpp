#include "Example.h"
#include "../Rendering/RenderTech.h"

ExampleResources::ExampleResources()
{
        initialize(Resources::defaultDir());
}

void ExampleResources::loadAll(Scene& scene)
{
        loadMeshes(scene);
        loadShaders(scene);
}

void ExampleResources::loadMeshes(Scene& scene)
{
        Mesh meshes[] =
        {
                Resources::Meshes::loadTriangleMesh(),
                Resources::Meshes::loadRectMesh(),
                Resources::Meshes::loadCubeMesh(),
                Resources::Meshes::loadCubeFaceMesh(0),
                Resources::Meshes::loadCubeFaceMesh(1),
                Resources::Meshes::loadCubeFaceMesh(2),
                Resources::Meshes::loadCubeFaceMesh(3),
                Resources::Meshes::loadCubeFaceMesh(4),
                Resources::Meshes::loadCubeFaceMesh(5),
        };
        ResID meshIDs[] =
        {
                ridTriangleMesh,
                ridRectMesh,
                ridCubeMesh,
                ridCubeFaceMesh0,
                ridCubeFaceMesh1,
                ridCubeFaceMesh2,
                ridCubeFaceMesh3,
                ridCubeFaceMesh4,
                ridCubeFaceMesh5,
        };
        Package& pack = scene.getPackage();
        for (int i = 0; i < sizeof(meshIDs) / sizeof(ResID); i++)
                pack.addAlias(meshIDs[i], pack.loadMesh(meshes[i]));
}

void ExampleResources::loadShaders(Scene& scene)
{
        Package& pack = scene.getPackage();
        Index edge = pack.loadShaderData(ShaderData(loadShaderCode("eVert.c"), loadShaderCode("eFrag.c")));
        Index litTex = pack.loadShaderData(ShaderData(loadShaderCode("ftVert.c"), loadShaderCode("ftFrag.c")));
        pack.addAlias(ridEdgeShader, edge);
        pack.addAlias(ridForwardShader, litTex);
}

void ExampleLevel::initialize()
{
        res.loadAll(scene);
        renderer = new GemRenderer(scene.getPackage(), *Engine::context);

        player = new Actor();
        player->cam = Camera(Point3D(), Point3D(), cfg.aspectRatio());
        player->setPos(Point3D(4, 4, 10));
        player->cam.lookAt(Point3D(0, 0, 0));
        scene.loadNode(player);

        Model* cube = new Model(scene.getPackage().getAlias(ridCubeMesh));
        scene.loadModel(cube);
}
