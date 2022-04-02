#include "components.h"

void Ground::update() { 

#if 0
    std::cout << "ground update" << getX() << std::endl;
#endif

    if (getX() < -20) {                                       // Reset ground
        setX(0);
    }
    else {
        object2D::update();
    }
}


void Bird::draw() {

    int PI = 3.14159265359;
    float angle = 0;

    if (getSpeedY() != 0) {
        angle = PI / 3 * max(-1, (float)getSpeedY() / SPEED_UP);
    }
    else if (getSpeedY() < 0) {
        angle = PI / 3.5 * ((float)getSpeedY() / SPEED_UP);
    }

    IMAGE current_image;
    IMAGE current_mask;
    rotateimage(&current_image, &image[frame], angle);
    rotateimage(&current_mask, &mask[frame], angle, WHITE);

    putimage(x, y, &current_mask, SRCAND);
    putimage(x, y, &current_image, SRCPAINT);
}
