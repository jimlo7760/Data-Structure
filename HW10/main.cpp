#include <cstdlib>
#include <cmath>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>

#include "image.h"
#include "priority_queue.h"

// ===================================================================================================

// distance field method functions
double NaiveDistanceFieldMethod(Image<Color> &input, Image<DistancePixel> &distance_image);

double ImprovedDistanceFieldMethod(Image<Color> &input, Image<DistancePixel> &distance_image);

double FastMarchingMethod(Image<Color> &input, Image<DistancePixel> &distance_image);

// visualization style helper functions
Color Rainbow(double distance, double max_distance);

Color GreyBands(double distance, double max_distance, int num_bands);

// ===================================================================================================

class hash_string_obj{
public:
    unsigned int operator() (const std::pair<int, int> &key) const{
        return key.first * 10000000 + key.second;
    }
};



int main(int argc, char *argv[]) {
    if (argc != 5) {
        std::cerr << "Usage: " << argv[0] << " input.ppm output.ppm distance_field_method visualization_style"
                  << std::endl;
        exit(1);
    }

    // open the input image
    Image<Color> input;
    if (!input.Load(argv[1])) {
        std::cerr << "ERROR: Cannot open input file: " << argv[1] << std::endl;
        exit(1);
    }

    // a place to write the distance values
    Image<DistancePixel> distance_image;
    distance_image.Allocate(input.Width(), input.Height());

    // calculate the distance field (each function returns the maximum distance value)
    double max_distance = 0;
    if (std::string(argv[3]) == std::string("naive_method")) {
        max_distance = NaiveDistanceFieldMethod(input, distance_image);
    } else if (std::string(argv[3]) == std::string("improved_method")) {
        max_distance = ImprovedDistanceFieldMethod(input, distance_image);
    } else if (std::string(argv[3]) == std::string("pq_with_map")) {
        max_distance = FastMarchingMethod(input, distance_image);
    } else if (std::string(argv[3]) == std::string("pq_with_hash_table")) {
        // EXTRA CREDIT: implement FastMarchingMethod with a hash table
    } else {
        std::cerr << "ERROR: Unknown distance field method: " << argv[3] << std::endl;
        exit(1);
    }

    // convert distance values to a visualization
    Image<Color> output;
    output.Allocate(input.Width(), input.Height());
    for (int i = 0; i < input.Width(); i++) {
        for (int j = 0; j < input.Height(); j++) {
            double v = distance_image.GetPixel(i, j).getValue();
            if (std::string(argv[4]) == std::string("greyscale")) {
                output.SetPixel(i, j, GreyBands(v, max_distance * 1.01, 1));
            } else if (std::string(argv[4]) == std::string("grey_bands")) {
                output.SetPixel(i, j, GreyBands(v, max_distance, 4));
            } else if (std::string(argv[4]) == std::string("rainbow")) {
                output.SetPixel(i, j, Rainbow(v, max_distance));
            } else {
                // EXTRA CREDIT: create other visualizations
                std::cerr << "ERROR: Unknown visualization style" << std::endl;
                exit(0);
            }
        }
    }
    // save output
    if (!output.Save(argv[2])) {
        std::cerr << "ERROR: Cannot save to output file: " << argv[2] << std::endl;
        exit(1);
    }

    return 0;
}

// ===================================================================================================

double NaiveDistanceFieldMethod(Image<Color> &input, Image<DistancePixel> &distance_image) {
    int w = input.Width();
    int h = input.Height();
    // return the maximum distance value
    double answer = 0;
    // loop over the pixels in the input image
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++) {
            double closest = -1;
            // loop over all other pixels in the input image
            for (int i2 = 0; i2 < w; i2++) {
                for (int j2 = 0; j2 < h; j2++) {
                    const Color &c = input.GetPixel(i2, j2);
                    // skip all pixels that are not black
                    if (!c.isBlack()) continue;
                    // calculate the distance between the two pixels
                    double distance = sqrt((i - i2) * (i - i2) + (j - j2) * (j - j2));
                    // store the closest distance to a black pixel
                    if (closest < 0 || distance < closest) {
                        closest = distance;
                    }
                }
            }
            assert (closest >= 0);
            answer = std::max(answer, closest);
            // save the data to the distance image
            DistancePixel &p = distance_image.GetPixel(i, j);
            p.setValue(closest);
        }
    }
    return answer;
}


double ImprovedDistanceFieldMethod(Image<Color> &input, Image<DistancePixel> &distance_image) {

    //
    // IMPLEMENT THIS FUNCTION
    //
    // a small improvement on the NaiveDistanceFieldMethod
    //
    int w = input.Width();
    int h = input.Height();
    // return the maximum distance value
    double answer = 0;
    // store the position of each black point as a pair
    std::vector<std::pair<int, int> > blackPos;
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++) {
            const Color &c = input.GetPixel(i, j);
            if (c.isBlack()) {
                blackPos.push_back(std::make_pair(i, j));
            }
        }
    }
    for (int i = 0; i < w; i++){
        for (int j = 0; j < h; j++){
            double closest = -1;
            for (unsigned int k = 0; k < blackPos.size(); k++){
                int curX = blackPos[k].first;
                int curY = blackPos[k].second;
                double curDis = sqrt((curX - i) * (curX - i) + (curY - j) * (curY - j));
                if (closest < 0 || curDis < closest){
                    closest = curDis;
                }
            }
            distance_image.GetPixel(i, j).setValue(closest);
            answer = std::max(closest, answer);
        }
    }
    return answer;
}

void updateQueueAndImg(DistancePixel_PriorityQueue &priQue, Image<DistancePixel> &distance_image, int curX, int curY, const double &newDis){
    double oldDis = distance_image.GetPixel(curX, curY).getValue();
    // create an object with info. in old position.
    DistancePixel* posObj = new DistancePixel;
    posObj ->setX(curX);
    posObj ->setY(curY);
    posObj ->setValue(oldDis);
    double minDis = std::min(oldDis, newDis);
    if (minDis < oldDis){
        if (priQue.in_heap(posObj)){
            posObj ->setValue(minDis);
            // update the position object when the current position already in the heap
            priQue.update_position(posObj);
        }else{
            posObj ->setValue(minDis);
            // otherwise add this position into the heap
            priQue.push(posObj);
        }
        distance_image.GetPixel(curX, curY).setValue(minDis);
    }
}

double FastMarchingMethod(Image<Color> &input, Image<DistancePixel> &distance_image) {

    //
    // IMPLEMENT THIS FUNCTION
    //
    // (using the advancing front method, and a priority queue)
    //
    int w = input.Width();
    int h = input.Height();
    // vector store all the valid position among the eight directions of each back points.
    std::vector<DistancePixel *> initialPos;
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++) {
            const Color &c = input.GetPixel(i, j);
            if (c.isBlack()) {
                DistancePixel *curPix = new DistancePixel;
                curPix->setX(i);
                curPix->setY(j);
                curPix->setValue(0);
                initialPos.push_back(curPix);
                distance_image.GetPixel(i, j).setValue(0);
            }
        }
    }

    DistancePixel_PriorityQueue priQue(initialPos);
    while (priQue.size() > 0) {
        const DistancePixel *curPix = priQue.top();
        int curPixX = curPix->getX();
        int curPixY = curPix->getY();
        priQue.pop();

        // assign value to the adjacent neighbours
        double newDis = distance_image.GetPixel(curPixX, curPixY).getValue() + 1;

        if (curPixX - 1 >= 0) {
            // left neighbour
            updateQueueAndImg(priQue, distance_image, curPixX - 1, curPixY, newDis);
        }
        if (curPixX + 1 < w) {
            // right neighbour
            updateQueueAndImg(priQue, distance_image, curPixX + 1, curPixY, newDis);
        }
        if (curPixY - 1 >= 0){
            // bottom neighbour
            updateQueueAndImg(priQue, distance_image, curPixX, curPixY - 1, newDis);
        }
        if (curPixY + 1 < h){
            // top neighbour
            updateQueueAndImg(priQue, distance_image, curPixX, curPixY + 1, newDis);
        }

        // assign value to the diagonal neighbours
        newDis = distance_image.GetPixel(curPixX, curPixY).getValue() + sqrt(2);
        if (curPixX - 1 >= 0 && curPixY - 1 >= 0){
            // bottom-left neighbour
            updateQueueAndImg(priQue, distance_image, curPixX - 1, curPixY - 1, newDis);
        }
        if (curPixX - 1 >= 0 && curPixY + 1 < h){
            // top-left neighbour
            updateQueueAndImg(priQue, distance_image, curPixX - 1, curPixY + 1, newDis);
        }
        if (curPixX + 1 < w && curPixY - 1 >= 0){
            // bottom-right neighbour
            updateQueueAndImg(priQue, distance_image, curPixX + 1, curPixY - 1, newDis);
        }
        if (curPixX + 1 < w && curPixY + 1 < h){
            // top-right neighbour
            updateQueueAndImg(priQue, distance_image, curPixX + 1, curPixY + 1, newDis);
        }
    }

    // find the maximum in the image
    double answer2 = -1;
    for (int i = 0; i < w; i++){
        for (int j = 0; j < h; j++){
            answer2 = std::max(answer2, distance_image.GetPixel(i, j).getValue());
        }
    }
    return answer2;
}

// ===================================================================================================

Color Rainbow(double distance, double max_distance) {
    Color answer;
    if (distance < 0.001) {
        // black
        answer.r = 0;
        answer.g = 0;
        answer.b = 0;
    } else if (distance < 0.2 * max_distance) {
        // blue -> cyan
        double tmp = distance * 5.0 / max_distance;
        answer.r = 0;
        answer.g = tmp * 255;
        answer.b = 255;
    } else if (distance < 0.4 * max_distance) {
        // cyan -> green
        double tmp = (distance - 0.2 * max_distance) * 5.0 / max_distance;
        answer.r = 0;
        answer.g = 255;
        answer.b = (1 - tmp * tmp) * 255;
    } else if (distance < 0.6 * max_distance) {
        // green -> yellow
        double tmp = (distance - 0.4 * max_distance) * 5.0 / max_distance;
        answer.r = sqrt(tmp) * 255;
        answer.g = 255;
        answer.b = 0;
    } else if (distance < 0.8 * max_distance) {
        // yellow -> red
        double tmp = (distance - 0.6 * max_distance) * 5.0 / max_distance;
        answer.r = 255;
        answer.g = (1 - tmp * tmp) * 255;
        answer.b = 0;
    } else if (distance < max_distance) {
        // red -> white
        double tmp = (distance - 0.8 * max_distance) * 5.0 / max_distance;
        answer.r = 255;
        answer.g = tmp * 255;
        answer.b = tmp * 255;
    } else {
        // white
        answer.r = answer.g = answer.b = 255;
    }
    return answer;
}

Color GreyBands(double distance, double max_value, int num_bands) {
    Color answer;
    if (distance < 0.001) {
        // red
        answer.r = 255;
        answer.g = 0;
        answer.b = 0;
    } else {
        // shades of grey
        answer.r = answer.g = answer.b = int(num_bands * 256 * distance / double(max_value)) % 256;
    }
    return answer;
}

// ===================================================================================================
