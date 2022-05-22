#ifndef __Header__
#define __Header__

#include <iostream>
#include <algorithm>
#include <chrono>
#include <cmath>
#include <filesystem>
#include <fstream>
#include <map>
#include <memory>
#include <random>
#include <thread>
#include <utility>
#include <vector>

using namespace std;

// Define PI
#define PI M_PI

// Global Consts for Reports
#define FILEPATH "/data/"
#define FILEPATH_GENOME "/genome/"
#define SAVEMOVIE true
#define SAVEMOVIE_INTERVAL 100
#define SAVEPOPUL_INTERVAL 100
#define SAVECHROM_INTERVAL 1000

// Include Parameters
#include "Parameter.hpp"
#include "PVector.hpp"

typedef long long ll;
typedef map<pair<ll, ll>, double> MatrixDistance;
typedef map<pair<ll, ll>, PVector> MatrixDiffPos;

#endif