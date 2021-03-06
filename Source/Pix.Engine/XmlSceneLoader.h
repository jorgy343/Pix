#pragma once

#include <sstream>
#include <vector>

#include "pugixml.h"
#include "Color3.h"
#include "Color4.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix44.h"
#include "PerspectiveCamera.h"
#include "OrthographicCamera.h"
#include "Geometry.h"
#include "GeometryGroup.h"
#include "Sphere.h"
#include "Plane.h"
#include "Scene.h"
#include "Light.h"
#include "Material.h"
#include "MaterialAliases.h"

using namespace Pix::Base;
using namespace Pix::Base::Cameras;
using namespace Pix::Base::Geometries;
using namespace Pix::Engine::Lights;
using namespace Pix::Engine::Materials;

namespace Pix::Engine
{
    class XmlSceneLoader
    {
    private:
        pugi::xml_document _document;

        void ConsumeWhitespace(std::stringstream& stream) const;

        Color3 ParseColor3(const char* string) const;
        Color4 ParseColor4(const char* string) const;

        Vector2 ParseVector2(const char* string) const;
        Vector3 ParseVector3(const char* string) const;
        Vector4 ParseVector4(const char* string) const;

        Matrix44 ParseMatrix44(const pugi::xml_node& element) const;
        Matrix44 ParseMatrix44Stack(const pugi::xml_node& element) const;

        MaterialNameMap* ParseMaterials() const;
        Material* ParseMaterial(const pugi::xml_node& element) const;

        Camera* ParseCamera(const pugi::xml_node& element) const;
        PerspectiveCamera* ParsePerspectiveCamera(const pugi::xml_node& element) const;
        OrthographicCamera* ParseOrthographicCamera(const pugi::xml_node& element) const;

        std::vector<const Light*>* ParseLights() const;

        Geometry* ParseRootGeometry(const MaterialNameMap* materialNameMap, MaterialGeometryMap* materialGeometryMap) const;
        Geometry* ParseGeometry(const pugi::xml_node& element, const MaterialNameMap* materialNameMap, MaterialGeometryMap* materialGeometryMap) const;

        GeometryGroup* ParseGeometryGroup(const pugi::xml_node& element, const MaterialNameMap* materialNameMap, MaterialGeometryMap* materialGeometryMap) const;
        Sphere* ParseSphere(const pugi::xml_node& element) const;
        Plane* ParsePlane(const pugi::xml_node& element) const;
        Plane* ParsePlaneD(const pugi::xml_node& element) const;

        SceneOptions* CreateSceneOptions() const;
        Camera* CreateCamera() const;

    public:
        XmlSceneLoader(const char* xmlContent);
        Scene* CreateScene(MaterialGeometryMap* materialGeometryMap) const;
    };
}