#include "XmlSceneLoader.h"
#include "PointLight.h"
#include "DirectionalLight.h"
#include "MaterialType.h"
#include "MonteCarloDiffuseMaterial.h"
#include "PhongDiffuseMaterial.h"
#include "SpecularMaterial.h"
#include "MaterialManager.h"

using namespace Pix::Engine;

void XmlSceneLoader::ConsumeWhitespace(std::stringstream& stream) const
{
    char dummy;
    while (!stream.eof())
    {
        char character = stream.peek();
        switch (stream.peek())
        {
        case L' ':
        case L'\t':
        case L'\r':
        case L'\n':
            stream.read(&dummy, 1);
            continue;
        }

        break;
    }
}

Color3 XmlSceneLoader::ParseColor3(const char* string) const
{
    std::stringstream stream(string);

    Color3 result;
    char dummy;

    ConsumeWhitespace(stream);
    stream >> result.Red;

    ConsumeWhitespace(stream);
    if (stream.peek() != ',')
    {
        result.Green = result.Red;
        result.Blue = result.Red;
    }
    else
    {
        stream.read(&dummy, 1); // Read the comma.

        ConsumeWhitespace(stream);
        stream >> result.Green;

        ConsumeWhitespace(stream);
        stream.read(&dummy, 1); // Read the comma.

        ConsumeWhitespace(stream);
        stream >> result.Blue;
    }

    return result;
}

Color4 XmlSceneLoader::ParseColor4(const char* string) const
{
    std::stringstream stream(string);

    Color4 result;
    char dummy;

    ConsumeWhitespace(stream);
    stream >> result.Red;

    ConsumeWhitespace(stream);
    stream.read(&dummy, 1); // Read the comma.

    ConsumeWhitespace(stream);
    stream >> result.Green;

    ConsumeWhitespace(stream);
    stream.read(&dummy, 1); // Read the comma.

    ConsumeWhitespace(stream);
    stream >> result.Blue;

    ConsumeWhitespace(stream);
    stream.read(&dummy, 1); // Read the comma.

    ConsumeWhitespace(stream);
    stream >> result.Alpha;

    return result;
}

Vector2 XmlSceneLoader::ParseVector2(const char* string) const
{
    std::stringstream stream(string);

    Vector2 result;
    char dummy;

    ConsumeWhitespace(stream);
    stream >> result.X;

    ConsumeWhitespace(stream);
    stream.read(&dummy, 1); // Read the comma.

    ConsumeWhitespace(stream);
    stream >> result.Y;

    return result;
}

Vector3 XmlSceneLoader::ParseVector3(const char* string) const
{
    std::stringstream stream(string);

    Vector3 result;
    char dummy;

    ConsumeWhitespace(stream);
    stream >> result.X;

    ConsumeWhitespace(stream);
    stream.read(&dummy, 1); // Read the comma.

    ConsumeWhitespace(stream);
    stream >> result.Y;

    ConsumeWhitespace(stream);
    stream.read(&dummy, 1); // Read the comma.

    ConsumeWhitespace(stream);
    stream >> result.Z;

    return result;
}

Vector4 XmlSceneLoader::ParseVector4(const char* string) const
{
    std::stringstream stream(string);

    Vector4 result;
    char dummy;

    ConsumeWhitespace(stream);
    stream >> result.X;

    ConsumeWhitespace(stream);
    stream.read(&dummy, 1); // Read the comma.

    ConsumeWhitespace(stream);
    stream >> result.Y;

    ConsumeWhitespace(stream);
    stream.read(&dummy, 1); // Read the comma.

    ConsumeWhitespace(stream);
    stream >> result.Z;

    ConsumeWhitespace(stream);
    stream.read(&dummy, 1); // Read the comma.

    ConsumeWhitespace(stream);
    stream >> result.W;

    return result;
}

Matrix44 XmlSceneLoader::ParseMatrix44(const pugi::xml_node& element) const
{
    std::string elementName = element.name();
    if (elementName == "ScaleMatrix44")
    {
        auto scale = ParseVector3(element.attribute("Scale").value());
        return Matrix44::CreateScale(scale);
    }

    auto translation = ParseVector3(element.attribute("Translation").value());
    return Matrix44::CreateTranslation(translation);
}

Matrix44 XmlSceneLoader::ParseMatrix44Stack(const pugi::xml_node& element) const
{
    Matrix44 matrix = Matrix44::CreateIdentity();
    for (auto& child : element.children())
        matrix = matrix * ParseMatrix44(child);

    return matrix;
}

MaterialNameMap* XmlSceneLoader::ParseMaterials() const
{
    auto materialNameMap = new MaterialNameMap();
    for (auto node : _document.select_nodes("//Materials/*"))
    {
        Material* material = ParseMaterial(node.node());
        std::string materialName = node.node().attribute("Name").value();

        if (material != nullptr)
            materialNameMap->insert_or_assign(materialName, material);
    }

    return materialNameMap;
}

Material* XmlSceneLoader::ParseMaterial(const pugi::xml_node& element) const
{
    std::string elementName = element.name();
    if (elementName == "PhongDiffuseMaterial")
    {
        auto ambientColor = ParseColor3(element.attribute("AmbientColor").value());
        auto diffuseColor = ParseColor3(element.attribute("DiffuseColor").value());
        auto diffuseCoefficient = element.attribute("DiffuseCoefficient").as_float();

        return new PhongDiffuseMaterial(ambientColor, diffuseColor, diffuseCoefficient);
    }
    else if (elementName == "MonteCarloDiffuseMaterial")
    {
        auto color = ParseColor3(element.attribute("Color").value());
        auto emissiveColor = ParseColor3(element.attribute("EmissiveColor").value());

        return new MonteCarloDiffuseMaterial(color, emissiveColor);
    }
    else if (elementName == "SpecularMaterial")
    {
        return new SpecularMaterial();
    }

    return nullptr;
}

Camera* XmlSceneLoader::ParseCamera(const pugi::xml_node& element) const
{
    std::string elementName = element.name();
    Camera* camera = nullptr;

    if (elementName == "PerspectiveCamera")
        camera = ParsePerspectiveCamera(element);
    else if (elementName == "OrthographicCamera")
        camera = ParseOrthographicCamera(element);

    return camera;
}

PerspectiveCamera* XmlSceneLoader::ParsePerspectiveCamera(const pugi::xml_node& element) const
{
    auto position = ParseVector3(element.attribute("Position").value());
    auto lookAt = ParseVector3(element.attribute("LookAt").value());
    auto up = ParseVector3(element.attribute("Up").value());

    auto windowWidth = element.attribute("ScreenWidth").as_int();
    auto windowHeight = element.attribute("ScreenHeight").as_int();

    auto fieldOfView = element.attribute("FieldOfView").as_float();

    return new PerspectiveCamera(position, lookAt, up, windowWidth, windowHeight, fieldOfView);
}

OrthographicCamera* XmlSceneLoader::ParseOrthographicCamera(const pugi::xml_node& element) const
{
    auto position = ParseVector3(element.attribute("Position").value());
    auto lookAt = ParseVector3(element.attribute("LookAt").value());
    auto up = ParseVector3(element.attribute("Up").value());

    auto windowWidth = element.attribute("ScreenWidth").as_int();
    auto windowHeight = element.attribute("ScreenHeight").as_int();

    auto orthoWidth = element.attribute("OrthoWidth").as_float();
    auto orthoHeight = element.attribute("OrthoHeight").as_float();

    return new OrthographicCamera(position, lookAt, up, windowWidth, windowHeight, orthoWidth, orthoHeight);
}

std::vector<const Light*>* XmlSceneLoader::ParseLights() const
{
    auto lights = new std::vector<const Light*>();
    for (auto node : _document.select_nodes("//Lights/*"))
    {
        std::string elementName = node.node().name();
        if (elementName == "DirectionalLight")
        {
            auto color = ParseColor3(node.node().attribute("Color").value());
            auto direction = ParseVector3(node.node().attribute("Direction").value());

            lights->push_back(new DirectionalLight(color, direction));
        }
        else if (elementName == "PointLight")
        {
            auto color = ParseColor3(node.node().attribute("Color").value());
            auto position = ParseVector3(node.node().attribute("Position").value());

            lights->push_back(new PointLight(color, position));
        }
    }

    return lights;
}

Geometry* XmlSceneLoader::ParseRootGeometry(const MaterialNameMap* materialNameMap, MaterialGeometryMap* materialGeometryMap) const
{
    auto rootGeometryElement = _document.select_single_node("//RootGeometry/*").node();
    return ParseGeometry(rootGeometryElement, materialNameMap, materialGeometryMap);
}

Geometry* XmlSceneLoader::ParseGeometry(const pugi::xml_node& element, const MaterialNameMap* materialNameMap, MaterialGeometryMap* materialGeometryMap) const
{
    std::string elementName = element.name();
    Geometry* geometry = nullptr;

    if (elementName == "GeometryGroup")
        geometry = ParseGeometryGroup(element, materialNameMap, materialGeometryMap);
    else if (elementName == "Sphere")
        geometry = ParseSphere(element);
    else if (elementName == "Plane")
        geometry = ParsePlane(element);
    else if (elementName == "PlaneD")
        geometry = ParsePlaneD(element);

    if (geometry != nullptr)
    {
        std::string materialName = element.attribute("MaterialName").as_string();
        if (materialNameMap->count(materialName) == 1)
        {
            const Material* material = materialNameMap->at(materialName);
            materialGeometryMap->insert_or_assign(geometry, material);
        }

        // Parse a local materia if present.
        auto materialElement = element.select_single_node("./Material/*");
        if (materialElement)
        {
            auto material = ParseMaterial(materialElement.node());
            if (material != nullptr)
                materialGeometryMap->insert_or_assign(geometry, material);
        }
    }

    return geometry;
}

GeometryGroup* XmlSceneLoader::ParseGeometryGroup(const pugi::xml_node& element, const MaterialNameMap* materialNameMap, MaterialGeometryMap* materialGeometryMap) const
{
    auto geometries = new std::vector<const Geometry*>();
    for (auto& child : element.select_single_node("./Geometries").node().children())
    {
        auto geometry = ParseGeometry(child, materialNameMap, materialGeometryMap);
        if (geometry != nullptr)
            geometries->push_back(geometry);
    }

    return new GeometryGroup(geometries);
}

Sphere* XmlSceneLoader::ParseSphere(const pugi::xml_node& element) const
{
    auto center = ParseVector3(element.attribute("Center").value());
    auto radius = element.attribute("Radius").as_float();

    return new Sphere(center, radius);
}

Plane* XmlSceneLoader::ParsePlane(const pugi::xml_node& element) const
{
    auto normal = ParseVector3(element.attribute("Normal").value());
    auto point = ParseVector3(element.attribute("Point").value());

    return new Plane(normal, point);
}

Plane* XmlSceneLoader::ParsePlaneD(const pugi::xml_node& element) const
{
    auto normal = ParseVector3(element.attribute("Normal").value());
    auto d = element.attribute("D").as_float();

    return new Plane(normal, d);
}

XmlSceneLoader::XmlSceneLoader(const char* xmlContent)
{
    _document.load_string(xmlContent);
}

SceneOptions* XmlSceneLoader::CreateSceneOptions() const
{
    auto optionsElement = _document.select_single_node("//Options").node();
    auto maxDepth = optionsElement.select_single_node("MaxDepth").node().text().as_int();
    auto defaultColor = ParseColor3(optionsElement.select_single_node("DefaultColor").node().first_child().value());
    auto antialiasingLevel = optionsElement.select_single_node("AntialiasingLevel").node().text().as_int();
    auto russianRouletteDepthStart = optionsElement.select_single_node("RussianRouletteDepthStart").node().text().as_int();
    auto russianRouletteStopProbability = optionsElement.select_single_node("RussianRouletteStopProbability").node().text().as_float();

    return new SceneOptions(maxDepth, defaultColor, antialiasingLevel, russianRouletteDepthStart, russianRouletteStopProbability);
}

Camera* XmlSceneLoader::CreateCamera() const
{
    auto cameraElement = _document.select_single_node("//Camera/*").node();
    return ParseCamera(cameraElement);
}

Scene* XmlSceneLoader::CreateScene(MaterialGeometryMap* materialGeometryMap) const
{
    auto sceneElement = _document.select_single_node("Scene").node();
    auto backgroundColor = ParseColor3(sceneElement.attribute("DefaultColor").as_string());
    auto antiAliasingLevel = sceneElement.attribute("AntialiasingLevel").as_int();

    auto materialNameMap = ParseMaterials();
    return new Scene(CreateSceneOptions(), CreateCamera(), ParseLights(), ParseRootGeometry(materialNameMap, materialGeometryMap), new MaterialManager(materialGeometryMap));
}