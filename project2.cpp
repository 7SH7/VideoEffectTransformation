//#include "opencv2/opencv.hpp"
//#include <iostream>
//
//using namespace std;
//using namespace cv;
//
//int main() {
//    VideoCapture cap("Project2_video.mp4");
//    Mat background, background_copy, image, gray, foregroundMask, foregroundImg;
//    Rect all(0, 140, 205, 100); // 이동 여부 체크하는 상단
//    Rect rect(260, 260, 170, 200); // 관심 영역(차)의 좌표 및 크기
//    Mat prev_roi_all, prev_roi_rect;
//
//    // 처음을 배경으로
//    cap >> background;
//    background_copy = background.clone();
//    cvtColor(background_copy, background_copy, COLOR_BGR2GRAY);
//
//    Mat frame, canny;
//    float rho, theta, a, b, x0, y0, total_rho, total_theta;
//    Point p1, p2;
//    vector<Vec2f> lane;
//
//    int start_x = 360;
//    int start_y = 250;
//    Rect rect_lane(start_x, start_y, 70, 170);
//
//    int fps = cap.get(CAP_PROP_FPS);
//    bool line_depart_bool = false;
//    bool start_bool = false;
//    int line_depart_start_time = 0;
//    int start_start_time = 0;
//
//    while (1) {
//        cap >> frame;
//        if (frame.empty()) {
//            cout << "end of video" << endl;
//            break;
//        }
//
//        cvtColor(frame, gray, COLOR_BGR2GRAY);
//
//        // roi 하기 -> 원본에서 roi 빼내기
//        Mat seg_all = gray(all);
//        Mat seg_rect = gray(rect);
//
//        // 배경 - 현재 것
//        Mat seg_fore_all, seg_fore_rect;
//        absdiff(background_copy(all), seg_all, seg_fore_all);
//        absdiff(background_copy(rect), seg_rect, seg_fore_rect);
//
//        // 차이 극대화 
//        threshold(seg_fore_all, seg_fore_all, 70, 255, THRESH_BINARY);
//        threshold(seg_fore_rect, seg_fore_rect, 85, 255, THRESH_BINARY);
//
//        canny = frame(rect_lane);
//        cvtColor(canny, canny, CV_BGR2GRAY);
//        blur(canny, canny, Size(5, 5));
//        Canny(canny, canny, 10, 60, 3);
//        HoughLines(canny, lane, 1, CV_PI / 180, 60, 0, 0, 3 * CV_PI / 4, 5 * CV_PI / 4);
//
//        if (lane.size()) {
//            total_rho = 0;
//            total_theta = 0;
//            for (int i = 0; i < lane.size(); i++) {
//                rho = lane[i][0];
//                theta = lane[i][1];
//
//                total_rho += rho;
//                total_theta += theta;
//            }
//            total_rho /= lane.size();
//            total_theta /= lane.size();
//
//            a = cos(total_theta);
//            b = sin(total_theta);
//            x0 = a * total_rho;
//            y0 = b * total_rho;
//            p1 = Point(cvRound(x0 + 1000 * (-b)) + start_x, cvRound(y0 + 1000 * a) + start_y);
//            p2 = Point(cvRound(x0 - 1000 * (-b)) + start_x, cvRound(y0 - 1000 * a) + start_y);
//
//            double degree = total_theta * 180 / CV_PI;
//            //cout << degree << endl;
//
//            if (140 <= degree && degree <= 170) {
//                line_depart_bool = true;
//                line_depart_start_time = (int)cap.get(CAP_PROP_POS_MSEC);
//            }
//        }
//
//        if (line_depart_bool && (int)(cap.get(CAP_PROP_POS_MSEC)) - line_depart_start_time <= 1000) {
//            putText(frame, "Lane departure", Point(frame.cols / 2 - 50, 50), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 0, 255), 2);
//        }
//        else {
//            line_depart_bool = false;
//        }
//
//        // 이전 ROI와 현재 ROI 비교
//        if (!prev_roi_all.empty() && !prev_roi_rect.empty()) {
//            Mat diff_all, diff_rect;
//            absdiff(prev_roi_all, seg_fore_all, diff_all);
//            absdiff(prev_roi_rect, seg_fore_rect, diff_rect);
//
//            // diff_all / diff_rect 의 하얀색의 개수가 특정 개수면, start 띄우기
//            int all_cnt = 0;
//            for (int i = 0; i < diff_all.rows; i++) {
//                for (int j = 0; j < diff_all.cols; j++) {
//                    if (diff_all.at<uchar>(i, j) > 0) {
//                        all_cnt++;
//                    }
//                }
//            }
//
//            int rect_cnt = 0;
//            for (int i = 0; i < diff_rect.rows; i++) {
//                for (int j = 0; j < diff_rect.cols; j++) {
//                    if (diff_rect.at<uchar>(i, j) > 0) {
//                        rect_cnt++;
//                    }
//                }
//            }
//
//            if (all_cnt <= 300 && rect_cnt >= 800) {
//                start_bool = true;
//                start_start_time = (int)cap.get(CAP_PROP_POS_MSEC);
//            }
//        }
//
//        if (start_bool && (int)cap.get(CAP_PROP_POS_MSEC) - start_start_time <= 1000) {
//            putText(frame, "Start Moving", Point(frame.cols / 2 - 50, 50), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 0, 255), 2);
//        }
//        else {
//            start_bool = false;
//        }
//
//        // 현재 ROI -> 이전 ROI
//        seg_fore_all.copyTo(prev_roi_all);
//        seg_fore_rect.copyTo(prev_roi_rect);
//
//        //rectangle(frame, all, Scalar(255, 0, 0), 5, 8, 0);
//        //rectangle(frame, rect, Scalar(255, 255, 0), 3, 8, 0);
//        //rectangle(frame, rect_lane, Scalar(255, 0, 0), 4, 8, 0);
//        imshow("Project2", frame);
//
//        waitKey(1000 / fps);
//    }
//
//    return 0;
//}
