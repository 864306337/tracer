#ifndef XMLSCENE_H
#define XMLSCENE_H

#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <cstring>

#include "tinyxml2.h"

#include "vector.h"
#include "sphere.h"
#include "mesh.h"
#include "geolight.h"
#include "material.h"
#include "render_helper.h"


class XMLScene
{
    public:
        XMLScene();

        int loadSceneFile(const std::string& scenePath);

        void loadMaterials(std::vector<BSDF> &materialList);
        void loadSpheres(std::vector<Sphere> &sphereList,
            std::vector<BSDF>& materialList);
        void loadMeshes(std::vector<Mesh> &meshList,
            std::vector<BSDF>& materialList);
        void loadLights(std::vector<GeoLight> &lightList,
            std::vector<BSDF>& materialList);
        void loadCamera(cameraData &sceneCamera);
        void loadSettings(settingsData &sceneSettings);

        void getFloatAttribute(float& floatAttr,
            const std::string& floatName,
            const tinyxml2::XMLNode& objectParameter);
        void getDoubleAttribute(double& doubleAttr,
            const std::string& floatName,
            const tinyxml2::XMLNode& objectParameter);
        void getStringAttribute(std::string& stringAttr,
            const std::string& stringName,
            const tinyxml2::XMLNode& objectParameter);
        void getVectorAttribute(Vector3& vectorAttr,
            const std::vector<std::string>& vectorNameList,
            const tinyxml2::XMLNode& objectParameter);

    private:
        tinyxml2::XMLDocument xmlSceneFile;
};


#endif // XMLSCENE_H