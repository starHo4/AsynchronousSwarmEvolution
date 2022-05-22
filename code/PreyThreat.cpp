#include "PreyThreat.hpp"

#pragma region Constructor
PreyThreat::PreyThreat(mt19937_64 &mt, Chromosome &_chr, const long long &_id) : Prey::Prey(mt, _chr, _id)
{
    F_threat = true;
    TakeEnergyRate = _chr.TakeEnergyRate;
}
#pragma endregion Constructor

#pragma region PublicMethods
void PreyThreat::Run(mt19937_64 &mt, Flock &f)
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

void PreyThreat::RobEnergy(mt19937_64 &mt, Flock &f)
{
    vector<ll> CandOfTarget = vector<ll>();
    for (int i = 0; i < f.flock.size(); i++)
    {
        if (f.flock[i]->F_live && !f.flock[i]->F_predator && f.flock[i]->Energy > 0)
        {
            ll firstID = ID;
            ll secondID = f.flock[i]->ID;
            if (firstID > secondID)
            {
                swap(firstID, secondID);
            }
            if (firstID != secondID)
            {
                double toA_Norm = f.MatDistance[make_pair(firstID, secondID)];
                if (0 < toA_Norm && toA_Norm <= SAFETY_DIST)
                {
                    CandOfTarget.push_back(i);
                }
            }
        }
    }
    shuffle(CandOfTarget.begin(), CandOfTarget.end(), mt);

    ll TargetID = CandOfTarget[0];
    Energy += (TakeEnergyRate * INIT_MEAN_ENERGY);
    auto target = find_if(f.flock.begin(), f.flock.end(), [&TargetID](shared_ptr<Prey> &p)
                          { return p->ID == TargetID; });
    size_t index = distance(f.flock.begin(), target);
    f.flock[index]->Energy -= (TakeEnergyRate * INIT_MEAN_ENERGY);
    f.flock[index]->ListOfThreat.push_back(ID);
}
#pragma endregion PublicMethods