#include "diffuse.h"


DiffuseIntegrator::DiffuseIntegrator()
{
    _handle = "Diffuse";
}

embree::Vec3f DiffuseIntegrator::GetPixelColor(Ray& ray,
    PixelSample& pixelSample,
    SceneManager &sceneManager,
    const RenderGlobals& renderGlobals)
{
    RTCIntersectContext intersectContext;
    rtcInitIntersectContext(&intersectContext);

    rtcIntersect1(sceneManager._scene, &intersectContext, RTCRayHit_(ray));

    if (ray.instID == RTC_INVALID_GEOMETRY_ID)
    {
        // TODO: Hardcoded sky color value for now.
        return embree::Vec3f(0.7, 0.8, 0.9);
    }

    // We setup all the necessary data describing the shading point.
    ShadingPoint shadingPoint(SetupShadingPoint(sceneManager, ray));

    float diffuse(std::fabs(embree::dot(shadingPoint.Nw, ray.direction)));

    return embree::Vec3f(shadingPoint.geometry->_displayColor * diffuse * (1.0f / M_PI));
}
