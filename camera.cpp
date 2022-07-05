#include "camera.h"


Camera::Camera(point pos, vector dir) : Ray{pos, dir, this} {}