#include "DataManager.hpp"

#pragma region PublicMethods
void DataManager::SaveFlock_Timestep(const double &_N, const int &_ts, const Flock &f, const vector<Predator> &_preds)
{
    filePath = filesystem::current_path();
    filePath += FILEPATH;
    double N = _N * 10;
    MakeDirectory("N", (int)N);
    filePath += "/forMovie/";
    if (!filesystem::exists(filePath))
    {
        filesystem::create_directory(filePath);
    }
    filePath += "ts" + to_string(_ts + 1) + ".csv";

    ofstream ofs(filePath.string(), ios::app);

    string data_header = "ID,F_predator,F_Threat,pos_x,pos_y,vel_x,vel_y,angle,action";
    ofs << data_header << endl;

    for (int i = 0; i < f.flock.size(); i++)
    {
        ll id = f.flock[i]->ID;
        int f_predator = f.flock[i]->F_predator;
        int f_threat = f.flock[i]->F_threat;
        double pos_x = f.flock[i]->getPos().x;
        double pos_y = f.flock[i]->getPos().y;
        double vel_x = f.flock[i]->getVel().x;
        double vel_y = f.flock[i]->getVel().y;
        double angle = f.flock[i]->getAngle();
        double action = f.flock[i]->getAction();

        ofs << id << "," << f_predator << "," << f_threat << "," << pos_x << "," << pos_y << "," << vel_x << "," << vel_y << "," << angle << "," << action << endl;
    }
    for(int i=0; i<_preds.size(); i++)
    {
        ll id = _preds[i].ID;
        int f_predator = _preds[i].F_predator;
        int f_threat = _preds[i].F_threat;
        double pos_x = _preds[i].getPos().x;
        double pos_y = _preds[i].getPos().y;
        double vel_x = _preds[i].getVel().x;
        double vel_y = _preds[i].getVel().y;
        double angle = _preds[i].getAngle();
        double action = _preds[i].getAction();

        ofs << id << "," << f_predator << "," << f_threat << "," << pos_x << "," << pos_y << "," << vel_x << "," << vel_y << "," << angle << "," << action << endl;
    }

    ofs.close();
}
#pragma endregion PublicMethods

#pragma region PrivateMethods
void DataManager::MakeDirectory(const string &_s, const int &_val)
{
    filePath += _s + to_string(_val) + "/";
    if (!filesystem::exists(filePath))
    {
        filesystem::create_directory(filePath);
    }
}
#pragma endregion PrivateMethods