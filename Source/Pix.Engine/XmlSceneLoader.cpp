#include "XmlSceneLoader.h"

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
    stream.read(&dummy, 1); // Read the comma.

    ConsumeWhitespace(stream);
    stream >> result.Green;

    ConsumeWhitespace(stream);
    stream.read(&dummy, 1); // Read the comma.

    ConsumeWhitespace(stream);
    stream >> result.Blue;

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

Matrix XmlSceneLoader::ParseMatrix(const pugi::xml_node& element) const
{
    std::string elementName = element.name();
    if (elementName == "ScaleMatrix")
    {
        auto scale = ParseVector3(element.attribute("Scale").value());
        return Matrix::CreateScale(scale);
    }

    auto translation = ParseVector3(element.attribute("Translation").value());
    return Matrix::CreateTranslation(translation);
}

Matrix XmlSceneLoader::ParseMatrixStack(const pugi::xml_node& element) const
{
    Matrix matrix = Matrix::CreateIdentity();
    for (auto& child : element.children())
        matrix = matrix * ParseMatrix(child);

    return matrix;
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

Geometry* XmlSceneLoader::ParseRootGeometry() const
{
    auto rootGeometryElement = _document.select_single_node("//RootGeometry/*").node();
    return ParseGeometry(rootGeometryElement);
}

Geometry* XmlSceneLoader::ParseGeometry(const pugi::xml_node& element) const
{
    std::string elementName = element.name();
    Geometry* geometry = nullptr;

    if (elementName == "GeometryGroup")
        geometry = ParseGeometryGroup(element);
    else if (elementName == "Sphere")
        geometry = ParseSphere(element);

    return geometry;
}

Geometry* XmlSceneLoader::ParseGeometryGroup(const pugi::xml_node& element) const
{
    auto geometries = new std::vector<const Geometry*>();
    for (auto& child : element.select_single_node("./Surfaces").node().children())
    {
        auto geometry = ParseGeometry(child);
        if (geometry != nullptr)
            geometries->push_back(geometry);
    }

    return new GeometryGroup(geometries);
}

Geometry* XmlSceneLoader::ParseSphere(const pugi::xml_node& element) const
{
    auto center = ParseVector3(element.attribute("Center").value());
    auto radius = element.attribute("Radius").as_float();

    return new Sphere(center, radius);
}

XmlSceneLoader::XmlSceneLoader(const char* xmlContent)
{
    _document.load_string(xmlContent);
}


SceneOptions* XmlSceneLoader::CreateSceneOptions() const
{
    auto optionsElement = _document.select_single_node("//Options").node();
    auto defaultColor = ParseColor3(optionsElement.select_single_node("DefaultColor").node().first_child().value());
    auto antialiasingLevel = optionsElement.select_single_node("AntialiasingLevel").node().text().as_int();

    return new SceneOptions(defaultColor, antialiasingLevel);
}

Camera* XmlSceneLoader::CreateCamera() const
{
    auto cameraElement = _document.select_single_node("//Camera/*").node();
    return ParseCamera(cameraElement);
}

Scene* XmlSceneLoader::CreateScene(const SceneOptions* sceneOptions, const Camera* camera) const
{
    auto sceneElement = _document.select_single_node("Scene").node();
    auto backgroundColor = ParseColor3(sceneElement.attribute("DefaultColor").as_string());
    auto antiAliasingLevel = sceneElement.attribute("AntialiasingLevel").as_int();

    return new Scene(sceneOptions, camera, nullptr, ParseRootGeometry()); // TODO: Don't pass in nulltpr!
}