class Agent
{
    // From data
    int id;
    PVector pos;
    PVector vel;
    double angle;
    
    // Predator or not?
    boolean F_predator;
    boolean F_threat;
    
    // For drawing
    float r;
    
    Agent() {}
    
    Agent(int _id)
    {
        id = _id;
        
        F_predator = false;
        r = 3;
    }
    
    void setParameter(int _fpredator, int _fthreat, PVector _pos, PVector _vel, double _angle)
    {
        F_predator = false;
        F_threat = false;
        r = 3;
        if (_fpredator > 0)
        {
            F_predator = true;
            r = 5;
        }
        if (_fthreat > 0)
        {
            F_threat = true;
        }
        pos = _pos;
        vel = _vel;
        angle = _angle;
    }
    
    void display()
    {
        float apex = radians(36);
        float tmp = PI - apex;
        if (F_predator)
        {
            fill(255,10,10);
        }
        else if (F_threat)
        {
            fill(10, 255, 10);
        }
        else
        {
            fill(10,10,255);
        }
        stroke(0);
        pushMatrix();
        translate(width / 2, height / 2);
        translate(pos.x, pos.y);
        rotate((float)angle);
        beginShape(PConstants.TRIANGLES);
        vertex(r, 0);
        vertex(r * cos(tmp), r * sin(tmp));
        vertex(r * cos( -tmp), r * sin( -tmp));
        popMatrix();
    }
}