#include "Prey.hpp"

#pragma region Constructor
Prey::Prey(mt19937_64 &mt, const Chromosome &_chr, const ll &_id) : Agent::Agent(mt, _chr, _id)
{
    F_predator = false;

    uniform_real_distribution<double> udd_X(0.6 * -FIELD_W / 2, 0.6 * FIELD_W / 2);
    uniform_real_distribution<double> udd_Y(0.6 * -FIELD_H / 2, 0.6 * FIELD_H / 2);
    uniform_real_distribution<double> udd_pi(0, 2 * PI);
    Pos = PVector(udd_X(mt), udd_Y(mt));
    Angle = udd_pi(mt);
    Vel = PVector(cos(Angle), sin(Angle));
    Action = -1;

    Radius = RADIUS_PREY;
    Speed = SPEED_PREY;
    AngleSpeed = ANGLESPEED_PREY / 180 * PI;

    // Init Brain
    Brain = RNN(_chr.Genotype, N_SENSOR_LAYER_PREY * N_SENSOR, N_MEMORY, N_ACTUATOR);
}
#pragma endregion Constructor

#pragma region PublicMethods
void Prey::Run(mt19937_64 &mt, Flock &f)
{
    Detect(f);
    Brain.FeedForward();
    Action = ((Brain.State[Brain.State.size() - 1] & 1) << 1) +
             ((Brain.State[Brain.State.size() - 2] & 1));
    TakeAction(Action);

    Vel.Normalize();
    if (Vel != PVector(0, 0))
    {
        Angle = atan2(Vel.y, Vel.x);
    }
}
#pragma endregion

#pragma region ProtectedMethods
void Prey::Detect(const Flock &f)
{
    Brain.ClearSensor();
    NearbyCount = 0;
    NearestDistance = 100000000;
    for (int i = 0; i < f.flock.size(); i++)
    {
        if (f.flock[i]->F_live)
        {
            ll firstID = ID;
            ll secondID = f.flock[i]->ID;
            bool swaped = false;
            if (firstID > secondID)
            {
                swap(firstID, secondID);
                swaped = true;
            }
            pair<ll, ll> p = make_pair(firstID, secondID);
            PVector toA = (swaped) ? -1 * f.MatDiffPos.at(p) : f.MatDiffPos.at(p);
            double toA_Norm = f.MatDistance.at(p);
            if (0 < toA_Norm && toA_Norm < NearestDistance)
            {
                NearestDistance = toA_Norm;
            }
            if (0 < toA_Norm && toA_Norm <= SAFETY_DIST)
            {
                NearbyCount++;
            }
            if (0 < toA_Norm && toA_Norm <= Radius)
            {
                double bAngle = Vel.CalcBetweenAngle(toA);
                if (abs(bAngle) < VisionAngle / 2)
                {
                    if (!f.flock[i]->F_predator)
                    /* The case of detecting other preys */
                    {
                        Brain.State[(int)((bAngle + VisionAngle / 2) / ((double)EACH_SEGMENT_ANGLE / 180 * PI))] = 1;
                    }
                    else
                    /* The case of detecting the predator */
                    {
                        Brain.State[(int)((bAngle + VisionAngle / 2) / ((double)EACH_SEGMENT_ANGLE / 180 * PI)) + (N_SENSOR_LAYER_PREY - 1) * N_SENSOR] = 1;
                    }
                }
            }
        }
    }
}

void Prey::CheckDead()
{
    if (Energy < 0)
    {
        F_live = false;
    }
}
#pragma endregion ProtectedMethods