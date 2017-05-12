#pragma once

#include "Config.h"
#include "Transformable.h"

class Camera : public Placement
{
public:
        struct Axes
        {
                Axes(const Vec3D& dir, const Vec3D& right, const Vec3D& up);
                Vec3D dir;
                Vec3D right;
                Vec3D up;
        };

        Camera();
        Camera(const Point3D& position, const Point3D& target, GLfloat aspectRatio
                , GLfloat fovy = 120.0f, GLfloat znear = 0.1f, GLfloat zfar = 1000.0f);

        Camera(const Point3D& position, const Point3D& target, const Config& cfg);
        Camera(const Camera& cam);

        Camera&       operator=(const Camera& cam);
        void          lookAt(const Point3D& target);
        void          setAspectRatio(GLfloat ratio);
        void          setFovy(GLfloat fov);
        void          setZ(GLfloat znear, GLfloat zfar);
        void          moveWithTarget(const Point3D& delta);
        virtual void  rotate(Angle3D angle);
        Axes          getAxes() const;
        Point3D       getTarget() const;
        Mat4D         getVP() const;
        virtual Mat4D getTransformMatrix() const override;

        DECLARE_SERIAL(Camera)
        virtual void save(Ostream& out) const override;
        virtual void load(Istream& in) override;

private:
        GLfloat znear;
        GLfloat zfar;
        GLfloat aspectRatio;
        GLfloat fovy;
        Point3D target;
};
