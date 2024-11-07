#ifndef VIEWER_H
#define VIEWER_H
#include <QList>
class Model;
#include <QObject>
class Camera;
class Light;
class OpenglWidget;
class Viewer: public QObject
{
    Q_OBJECT
public:
    Viewer(OpenglWidget* wgt);

    Camera *pCamera() const;
    void setPCamera(Camera *newPCamera);

    Light *pLight() const;
    void setPLight(Light *newPLight);
    OpenglWidget *pParWgt() const;
    void setPParWgt(OpenglWidget *newPParWgt);

    void bindToViewer(Model* model);
    void updateAllDataToShader(Model* model);
protected:
    void init();

    void onLightChanged();
    void onCameraMoved();
    void onCameraPerspectiveChanged();

private:
    QList <Model*> m_models;

    Camera* m_pCamera = nullptr;
    Light* m_pLight = nullptr;
    OpenglWidget* m_pParWgt = nullptr;
};

#endif // VIEWER_H
