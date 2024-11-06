#ifndef VIEWER_H
#define VIEWER_H
#include <QList>
class Model;

class Camera;
class Light;
class Viewer
{
public:
    Viewer();

    Camera *pCamera() const;
    void setPCamera(Camera *newPCamera);

    Light *pLight() const;
    void setPLight(Light *newPLight);

private:
    QList <Model*> m_models;

    Camera* m_pCamera;
    Light* m_pLight;
};

#endif // VIEWER_H
