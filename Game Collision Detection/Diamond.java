/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author Andy
 */
public class Diamond extends Node
{

    double ID, x1, y1, x2, y2, x3, y3, x4, y4, size;

    Point p = null;

    public Diamond()
    {

    }

    @Override
    public double get_ID()
    {
        return ID;
    }

    @Override
    public double get_x1()
    {
        return x1;
    }

    @Override
    public double get_y1()
    {
        return y1;
    }

    @Override
    public double get_x2()
    {
        return x2;
    }

    @Override
    public double get_y2()
    {
        return y2;
    }

    @Override
    public double get_x3()
    {
        return x3;
    }

    @Override
    public double get_y3()
    {
        return y3;
    }

    @Override
    public double get_x4()
    {
        return x4;
    }

    @Override
    public double get_y4()
    {
        return y4;
    }

    public void Order(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4)
    {
        double temp;

//        if(x1 < x2)
//        {
//            temp = x1;
//            
//            this.x1 = x2;
//            
//            this.x2 = temp;
//        }
//        if(x1 > x4)
//        {
//            temp = x1;
//            
//            this.x1 = x4;
//            
//            this.x4 = temp;
//        }
//        
//        if(x3 < x2)
//        {
//            temp = x3;
//            
//            this.x3 = x2;
//            
//            this.x2 = temp;
//        }
//        
//        if(x3 > x4)
//        {
//            temp = x3;
//            
//            this.x3 = x4;
//            
//            this.x4 = temp;
//        }
//        
//        if(x2 > x4)
//        {
//            temp = x2;
//            
//            this.x2 = x4;
//            
//            this.x4 = temp;
//        }
//        
//        if(y1 < y2)
//        {
//            temp = y1;
//            
//            this.y1 = y2;
//            
//            this.y2 = temp;
//        }
//        if(y1 < y4)
//        {
//            temp = y1;
//            
//            this.y1 = y4;
//            
//            this.y4 = temp;
//        }
//        
        if (y1 < y3)
        {
            temp = y1;

            this.y1 = y3;

            this.y3 = temp;

            temp = x1;

            this.x1 = x3;

            this.x3 = temp;
        }

//        if(y2 < y3)
//        {
//            temp = y2;
//            
//            this.y2 = y3;
//            
//            this.y3 = temp;
//        }
//        if(y4 < y3)
//        {
//            temp = y4;
//            
//            this.y4 = y3;
//            
//            this.y3 = temp;
//            
//            temp = x4;
//            
//            this.x4 = x3;
//            
//            this.x3 = temp;
//        }
    }

    @Override
    public Point getLowerLeftPoint()
    {
        if ((x1 > x2) && (x1 < x4) && (y1 > y2) && (y1 > y3) && (y1 > y4))
        {
            p = new Point(x2, y3);
        }

        if ((x3 > x4) && (x3 < x2) && (y3 > y4) && (y3 > y2) && (y3 > y1))
        {
            p = new Point(x4, y1);
        }

        if ((x3 > x2) && (x3 < x4) && (y3 > y2) && (y3 > y4) && (y3 > y1))
        {
            p = new Point(x2, y1);
        }

        if ((x4 > x1) && (x4 < x3) && (y4 > y1) && (y4 > y3) && (y4 > y2))
        {
            p = new Point(x1, y2);
        }

        if ((x2 > x3) && (x2 < x1) && (y2 > y3) && (y2 > y1) && (y2 > y4))
        {
            p = new Point(x3, y4);
        }

        return p;
    }

    @Override
    public Point getLowerRightPoint()
    {
        if ((x1 > x2) && (x1 < x4) && (y1 > y2) && (y1 > y3) && (y1 > y4))
        {
            p = new Point(x4, y3);
        }

        if ((x3 > x4) && (x3 < x2) && (y3 > y4) && (y3 > y2) && (y3 > y1))
        {
            p = new Point(x2, y1);
        }

        if ((x3 > x2) && (x3 < x4) && (y3 > y2) && (y3 > y4) && (y3 > y1))
        {
            p = new Point(x4, y1);
        }

        if ((x4 > x1) && (x4 < x3) && (y4 > y1) && (y4 > y3) && (y4 > y2))
        {
            p = new Point(x3, y2);
        }

        if ((x2 > x3) && (x2 < x1) && (y2 > y3) && (y2 > y1) && (y2 > y4))
        {
            p = new Point(x1, y4);
        }

        return p;
    }

    @Override
    public Point getUpperLeftPoint()
    {
        if ((x1 > x2) && (x1 < x4) && (y1 > y2) && (y1 > y3) && (y1 > y4))
        {
            p = new Point(x2, y1);
        }

        if ((x3 > x4) && (x3 < x2) && (y3 > y4) && (y3 > y2) && (y3 > y1))
        {
            p = new Point(x4, y3);
        }

        if ((x3 > x2) && (x3 < x4) && (y3 > y2) && (y3 > y4) && (y3 > y1))
        {
            p = new Point(x2, y3);
        }

        if ((x4 > x1) && (x4 < x3) && (y4 > y1) && (y4 > y3) && (y4 > y2))
        {
            p = new Point(x1, y4);
        }

        if ((x2 > x3) && (x2 < x1) && (y2 > y3) && (y2 > y1) && (y2 > y4))
        {
            p = new Point(x3, y2);
        }

        return p;
    }

    @Override
    public Point getUpperRightPoint()
    {
        if ((x1 > x2) && (x1 < x4) && (y1 > y2) && (y1 > y3) && (y1 > y4))
        {
            p = new Point(x4, y1);
        }

        if ((x3 > x4) && (x3 < x2) && (y3 > y4) && (y3 > y2) && (y3 > y1))
        {
            p = new Point(x2, y3);
        }

        if ((x3 > x2) && (x3 < x4) && (y3 > y2) && (y3 > y4) && (y3 > y1))
        {
            p = new Point(x4, y3);
        }

        if ((x4 > x1) && (x4 < x3) && (y4 > y1) && (y4 > y3) && (y4 > y2))
        {
            p = new Point(x3, y4);
        }

        if ((x2 > x3) && (x2 < x1) && (y2 > y3) && (y2 > y1) && (y2 > y4))
        {
            p = new Point(x1, y2);
        }

        return p;
    }

    @Override
    public int Point_Collision_Test_2(double x, double y)
    {
        int i, j;

        double x_coord[] = new double[4];
        double y_coord[] = new double[4];

        x_coord[0] = this.x1;
        x_coord[1] = this.x2;
        x_coord[2] = this.x3;
        x_coord[3] = this.x4;

        y_coord[0] = this.y1;
        y_coord[1] = this.y2;
        y_coord[2] = this.y3;
        y_coord[3] = this.y4;
        
        

        for (i = 0, j = 3; i < 4; j = i++)
        {
            if (((y_coord[i] > y) != (y_coord[j] > y)) && (x < (x_coord[j] - x_coord[i]) * (y - y_coord[i]) / (y_coord[j] - y_coord[i]) + x_coord[i]))
            {
                if (x <= this.get_x2())
                {
                    return 0;
                }

                if (x >= this.get_x4())
                {
                    return 0;
                }

                if (y >= this.get_y3())
                {
                    return 0;
                }

                if (y <= this.get_y1())
                {
                    return 0;
                }

                return 1;
            }
        }

        return 0;
    }
}
