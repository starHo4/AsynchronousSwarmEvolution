#include "Agent.hpp"

#pragma region Constructor
Agent::Agent(mt19937_64 &mt, const Chromosome &_chr, const ll &_id)
{
    ID = _id;
    F_live = true;

    Genome = _chr;

    VisionAngle = 2 * PI - (N_SEGMENT_SENSOR * EACH_SEGMENT_ANGLE) / 180 * PI;
}

Agent::Agent(mt19937_64 &mt, const Chromosome &_chr, const PVector &_parentPos, const ll &_id)
{
    ID = _id;
    F_live = true;

    Genome = _chr;

    VisionAngle = 2 * PI - (N_SEGMENT_SENSOR * EACH_SEGMENT_ANGLE) / 180 * PI;
}
#pragma endregion Constructor

#pragma region PublicMethods
void Agent::Run(mt19937_64 &mt, Flock &f)
{
}

void Agent::Update()
{
    Pos += (Speed * Vel);
    Borders();
}
#pragma endregion Public Methods

#pragma region ProtectedMethods
void Agent::Detect(const Flock &f)
{
}

void Agent::TakeAction(const int &a)
{
    if (a < 0 || a > 3)
    {
        abort();
    }

    Vel = PVector(cos(Angle), sin(Angle));
    switch (a)
    {
    case 0:
        // Do nothing
        Vel = PVector(0, 0);
        break;

    case 1:
        // Turn Right
        Vel.Rotate(AngleSpeed);
        break;

    case 2:
        // Turn Left
        Vel.Rotate(-AngleSpeed);
        break;

    case 3:
        // Go straight
        break;

    default:
        break;
    }
}
#pragma endregion ProtectedMethods

#pragma region PrivateMethods
void Agent::Borders()
{
    if (Pos.x < -FIELD_W / 2)
    {
        Pos.x += FIELD_W;
    }
    else if (Pos.x > FIELD_W / 2)
    {
        Pos.x -= FIELD_W;
    }
    if (Pos.y < -FIELD_H / 2)
    {
        Pos.y += FIELD_H;
    }
    else if (Pos.y > FIELD_H / 2)
    {
        Pos.y -= FIELD_H;
    }
}
#pragma endregion PrivateMethods