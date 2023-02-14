#pragma once

#include <ballistics/ballistics.h>
#include <math.h>

#include <opencv4/opencv2/highgui.hpp>
#include <opencv4/opencv2/imgproc.hpp>

class Gun {
   public:
};

class BallisticCalc {
    Ballistics* result;
    int k;
    double bc = 0.5;

   public:
    void calc_atmosphereDrag(double, double, double, double);
    cv::Point calculate(int, double, double, double, double, double, double, double);
    ~BallisticCalc();
};

void BallisticCalc::calc_atmosphereDrag(double altitude, double barometer, double temp, double relative_humidity) {
    this->bc = atmosphere_correction(this->bc, altitude, barometer, temp, relative_humidity);
}

cv::Point BallisticCalc::calculate(int l, double velocity, double sight_height, double angle, double zero, double wind_speed, double wind_angle, double y_intercept = 0) {
    l *= 1.0936133;
    sight_height *= 0.393700787;

    double zeroangle = zero_angle(G1, bc, velocity, sight_height, zero, y_intercept);
    this->k = Ballistics_solve(&this->result, G1, bc, velocity, sight_height, angle, zeroangle, wind_speed, wind_angle);

    cv::Point _res;
    _res.x = (int)(Ballistics_get_windage(this->result, l) * 2.54);
    _res.y = (int)(Ballistics_get_path(this->result, l) * 2.54);

    return _res;
}

BallisticCalc::~BallisticCalc() {
    Ballistics_free(this->result);
}

void draw_crossight_d(cv::Mat frame, int x, int y, cv::Point d) {
    cv::drawMarker(frame, cv::Point(x, y), cv::Scalar(255, 0, 255), cv::MARKER_CROSS, 50, 2);

    x += d.x;
    y -= d.y;

    cv::drawMarker(frame, cv::Point(x, y), cv::Scalar(255, 0, 0), cv::MARKER_DIAMOND, 30, 2);
}