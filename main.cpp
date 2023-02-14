#include <iostream>
#include <string>
#include <vector>

#include "include.hpp"

int main() {
    cv::Mat frame = cv::imread("wallpaper.jpg");

    BallisticCalc bal_calc;

    int len_meter = 350;

    cv::Point c = bal_calc.calculate(len_meter, 1200, 2, 0.42, 12, -20, 90);

    draw_crosshair_d(frame, 500, 500, c);

    cv::putText(frame, "Lenght: " + std::to_string(len_meter) + "m", cv::Point(0, 50), 0, 1, cv::Scalar(0, 255, 0), 2);

    cv::imshow("Frame", frame);

    while (cv::waitKey(3) != 'a')
        ;

    return 0;
}
