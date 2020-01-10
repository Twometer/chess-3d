//
// Created by Twometer on 10/01/2020.
//

#ifndef CHESS_3D_ANIMATOR_H
#define CHESS_3D_ANIMATOR_H

class Animated {
private:
    float srcValue;

    float curValue;

    float targetValue;

    float progress;

private:
    void Reset() {
        progress = 0.0f;
        srcValue = curValue;
    }

public:

    Animated(float value) {
        this->srcValue = value;
        this->targetValue = value;
    }

    void SetValue(float value) {
        targetValue = value;
        Reset();
    }

    float GetValue() {
        return curValue;
    }

    void Update() {
        if (progress < 1.0f)
            progress += 0.1f;
        curValue = srcValue + (targetValue - srcValue) * glm::sin(progress * M_PI_2);
    }

    Animated &operator+=(const float other) {
        this->targetValue += other;
        Reset();
        return *this;
    }

    Animated &operator-=(const float other) {
        this->targetValue -= other;
        Reset();
        return *this;
    }

    void ClampTo(float min, float max) {
        this->targetValue = glm::clamp(this->targetValue, min, max);
    }

};

#endif //CHESS_3D_ANIMATOR_H
