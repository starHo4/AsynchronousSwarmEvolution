#include "Predator.hpp"

#pragma region Constructor
Predator::Predator(mt19937_64 &mt, const Chromosome &_chr) : Agent::Agent(mt, _chr)
{
    F_predator = true;

    // Init Pos and Vel
    uniform_real_distribution<double> udd_X(-FIELD_W / 2, FIELD_W / 2);
    uniform_real_distribution<double> udd_Y(-FIELD_H / 2, FIELD_H / 2);
    uniform_real_distribution<double> udd_pi(0, 2 * PI);
    Pos = PVector(udd_X(mt), udd_Y(mt));
    Angle = udd_pi(mt);
    Vel = PVector(cos(Angle), sin(Angle));
    Action = -1;

    // Init Radius and Speed
    Radius = RADIUS_PREDATOR;
    Speed = SPEED_PREDATOR;
    AngleSpeed = ANGLESPEED_PREDATOR;

    // Init Brain
    Brain = RNN(_chr.Genotype, N_SENSOR, N_MEMORY, N_ACTUATOR);

    // Init parameters for making a kill
    Radius_kill = RADIUS_KILL;
    Delay = KILL_DELAY;

    AttackNum = 0;
}
#pragma endregion Constructor

#pragma region PublicMethods
void Predator::Run(mt19937_64 &mt, Flock &f)
{
    Detect(f);
    Brain.FeedForward();
    Action = ((Brain.State[Brain.State.size() - 1] & 1) << 1) +
             ((Brain.State[Brain.State.size() - 2] & 1));
    TakeAction(Action);

    // Try to predate a target prey
    TryPredation(mt, f);

    Vel.Normalize();
    if (Vel != PVector(0, 0))
    {
        Angle = atan2(Vel.y, Vel.x);
    }
}
#pragma endregion PublicMethods

#pragma region PrivateMethods
void Predator::Detect(const Flock &f)
{
    Brain.ClearSensor();
    for (int i = 0; i < f.flock.size(); i++)
    {
        if (f.flock[i]->F_live && !f.flock[i]->F_predator)
        {
            PVector toA = f.MatDiffPos[ID][i];
            double toA_Norm = f.MatDistance[ID][i];
            if (0 < toA_Norm && toA_Norm <= Radius)
            {
                double bAngle = Vel.CalcBetweenAngle(toA);
                if (abs(bAngle) < VisionAngle / 2)
                {
                    Brain.State[(int)((bAngle + VisionAngle / 2) / ((double)EACH_SEGMENT_ANGLE / 180 * PI))] = 1;
                }
            }
        }
    }
}

void Predator::TryPredation(mt19937_64 &mt, Flock &f)
{
    uniform_real_distribution<double> udd(0, 1);
    if (f.NumAlive > 1)
    {
        if (Delay < 1)
        {
            bool killed = false;
            for (int i = 0; !killed && i < f.flock.size(); i++)
            {
                PVector toPrey = f.MatDiffPos[ID][i];
                if (f.flock[i]->F_live &&                                     // whether the prey is alive?
                    (0 < toPrey.Norm()) && (toPrey.Norm() < Radius_kill) &&   // whether the prey is within R_kill?
                    abs(Vel.CalcBetweenAngle(toPrey)) < VisionAngle / 2)      // whether the prey is within vision angle of the predator?
                {
                    AttackNum++;
                    int nearbyCount = 0;

                    for (int j = 0; j < f.flock.size(); j++)
                    {
                        PVector toJ = f.MatDiffPos[ID][j];
                        if (f.flock[j]->F_live &&                                               // whether the prey j is alive ?
                            (0 < f.MatDistance[i][j]) && (f.MatDistance[i][j] < SAFETY_DIST) && // whether the distance between prey i and prey j is within DIST_SAFETY?
                            (0 < toJ.Norm()) && (toJ.Norm() < Radius) &&                        // whether the prey j is within R?
                            abs(Vel.CalcBetweenAngle(toJ)) < VisionAngle / 2)                   // whether the prey j is within vision angle of the predator?
                        {
                            nearbyCount++;
                        }
                    }

                    //* CONFUSION EFFECT *//
                    double killChance = 1.0 / (double)nearbyCount;

                    if (udd(mt) < killChance)
                    {
                        killed = true;
                        f.flock[i]->F_live = false;
                        f.NumAlive--;
                    }

                    Delay = KILL_DELAY;
                    break;
                }
            }
        }
        else
        {
            Delay--;
        }
    }
}
#pragma endregion PrivateMethods