int TimeSteps = 1000;
int FlockSize = 201;
int HeaderNum = 9;

Agent[] flock = new Agent[FlockSize];
double[][][] Data_timestep = new double[TimeSteps + 1][FlockSize][HeaderNum];

void setup()
{
    size(512, 512);
    
    // Init Data_timestep
    for (int i = 0; i < TimeSteps + 1; i++)
    {
        for (int j = 0; j < FlockSize; j++)
        {
            for (int k = 0; k < HeaderNum; k++)
            {
                Data_timestep[i][j][k] = -1024;
            }
        }
    }

    readData();
    
    // Init flock
    for (int i = 0; i < FlockSize; i++)
    {
        flock[i] = new Agent(i);
    }
    
    drawFlock();
}

void draw()
{
    if (frameCount >= TimeSteps)
    {
        exit();
    }
    
    background(255,240,237);
    
    drawFlock();
}

void readData()
{    
    // Read Pos, Vel, and angle of Flock in each time step
    for (int i = 0; i < TimeSteps; i++)
    {
        String filename_timestep = "../../data/N0/forMovie/ts" + str(i + 1) + ".csv";
        Table tbl_timestep = loadTable(filename_timestep, "header");
        
        int rowNum = tbl_timestep.getRowCount();
        
        for (int j = 0; j < rowNum; j++)
        {
            for (int k = 0; k < HeaderNum; k++)
            {
                Data_timestep[i][j][k] = tbl_timestep.getDouble(j, k);
            }
        }
    }
}

void drawFlock()
{
    for (int i = 0; i < FlockSize; i++)
    {
        double[] each_Data = new double[HeaderNum];

        if(Data_timestep[frameCount][i][0] < -1000)
        {
            continue;
        }

        for (int j = 0; j < HeaderNum; j++)
        {
            each_Data[j] = Data_timestep[frameCount][i][j];
        }
        
        int fpredator_tmp = (int)each_Data[1];
        PVector pos_tmp = new PVector((float)each_Data[3],(float)each_Data[4]);
        PVector vel_tmp = new PVector((float)each_Data[5],(float)each_Data[6]);
        double angle_tmp = each_Data[7];
        
        flock[i].setParameter(fpredator_tmp, pos_tmp, vel_tmp, angle_tmp);
        flock[i].display();
    }
}