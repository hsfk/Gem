#include "Camera.h"
#include "Math.h"

Camera::Axes::Axes(const Vec3D& dir, const Vec3D& right, const Vec3D& up)
        : dir(dir), right(right), up(up)
{
}

Camera::Camera()
{
}

Camera::Camera(const Point3D& position, const Point3D& target, GLfloat aspectRatio
        , GLfloat fovy, GLfloat znear, GLfloat zfar)
{
        setZ(znear, zfar);
        setPos(position);
        setAspectRatio(aspectRatio);
        setFovy(fovy);
        lookAt(target);
}

Camera::Camera(const Point3D& position, const Point3D& target, const Config& cfg)
        : Camera(position, target, cfg.aspectRatio())
{
}

Camera::Camera(const Camera& cam)
        : Camera(cam.getPos(), cam.target, cam.aspectRatio, cam.fovy, cam.znear, cam.zfar)
{
}

Camera& Camera::operator=(const Camera& cam)
{
        setZ(cam.znear, cam.zfar);
        setPos(cam.getPos());
        setAspectRatio(cam.aspectRatio);
        setFovy(cam.fovy);
        lookAt(cam.target);
        return *this;
}

void Camera::lookAt(const Point3D& target)
{
        this->target = target;
}

void Camera::setAspectRatio(GLfloat ratio)
{
        aspectRatio = ratio;
}

void Camera::setFovy(GLfloat fov)
{
        fovy = fov;
}

void Camera::setZ(GLfloat znear, GLfloat zfar)
{
        this->zfar = zfar;
        this->znear = znear;
}

void Camera::moveWithTarget(const Point3D& delta)
{
        target += delta;
        setPos(getPos() + delta);
}

void Camera::rotate(Angle3D angle)
{
        Axes axes = getAxes();
        axes.dir = glm::rotate(axes.dir, angle.x, axes.up);
        axes.dir = glm::rotate(axes.dir, angle.y, axes.right);
        lookAt(getPos() - axes.dir);
}

Camera::Axes Camera::getAxes() const
{
        Vec3D dir = normalize(getPos() - target);
        Vec3D right = normalize(cross(Vec3D(0, 1, 0), dir));
        Vec3D up = normalize(cross(dir, right));
        return Axes(dir, right, up);
}

Point3D Camera::getTarget() const
{
        return target;
}

Mat4D Camera::getVP() const
{
        return glm::perspective(fovy, aspectRatio, znear, zfar)
                * glm::lookAt(getPos(), target, getAxes().up);
}

Mat4D Camera::getTransformMatrix() const
{
        return Placement::getTransformMatrix();
}

void Camera::save(Ostream& out) const
{
        Placement::save(out);
        out < znear < zfar < aspectRatio < fovy < target;
}

void Camera::load(Istream& in)
{
        Placement::load(in);
        in > znear > zfar > aspectRatio > fovy > target;
}
