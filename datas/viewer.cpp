#include "viewer.h"

Viewer::Viewer() {}

Camera *Viewer::pCamera() const
{
    return m_pCamera;
}

void Viewer::setPCamera(Camera *newPCamera)
{
    m_pCamera = newPCamera;
}

Light *Viewer::pLight() const
{
    return m_pLight;
}

void Viewer::setPLight(Light *newPLight)
{
    m_pLight = newPLight;
}
