#pragma once

#include <sstream>
#include <vector>

#include "pugixml.h"
#include "Color3.h"
#include "Color4.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix.h"
#include "PerspectiveCamera.h"
#include "OrthographicCamera.h"
#include "Geometry.h"
#include "GeometryGroup.h"
#include "Sphere.h"
#include "Scene.h"
#include "Light.h"
#include "DirectionalLight.h"

using namespace Pix::Base;
using namespace Pix::Base::Cameras;
using namespace Pix::Base::Geometries;
using namespace Pix::Engine::Lights;

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

        Matrix ParseMatrix(const pugi::xml_node& element) const;
        Matrix ParseMatrixStack(const pugi::xml_node& element) const;

        Camera* ParseCamera(const pugi::xml_node& element) const;
        PerspectiveCamera* ParsePerspectiveCamera(const pugi::xml_node& element) const;
        OrthographicCamera* ParseOrthographicCamera(const pugi::xml_node& element) const;

        std::vector<const Light*>* ParseLights() const;
        DirectionalLight* ParseDirectionalLight(const pugi::xml_node& element) const;

        Geometry* ParseRootGeometry() const;
        Geometry* ParseGeometry(const pugi::xml_node& element) const;

        Geometry* ParseGeometryGroup(const pugi::xml_node& element) const;
        Geometry* ParseSphere(const pugi::xml_node& element) const;

    public:
        XmlSceneLoader(const char* xmlContent);

        SceneOptions* CreateSceneOptions() const;
        Camera* CreateCamera() const;
        Scene* CreateScene(const SceneOptions* sceneOptions, const Camera* camera) const;
    };
}