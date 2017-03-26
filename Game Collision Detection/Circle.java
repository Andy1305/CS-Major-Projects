/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

import static java.lang.Math.*;

/**
 *
 * @author Andy
 */
public class Circle extends Node
{

    double ID, x1, y1, R, size;

    Point p;

    public Circle()
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
    public double get_R()
    {
        return R;
    }

    @Override
    public Point getLowerLeftPoint()
    {
        p = new Point(x1 - R, y1 - R);

        return p;
    }

    @Override
    public Point getLowerRightPoint()
    {
        p = new Point(x1 + R, y1 - R);
        
        return p;
    }

    @Override
    public Point getUpperLeftPoint()
    {
        p = new Point(x1 - R, y1 + R);

        return p;
    }

    @Override
    public Point getUpperRightPoint()
    {
        p = new Point(x1 + R, y1 + R);

        return p;
    }

    @Override
    public int Point_Collision_Test_2(double x, double y)
    {
        double d;
        
        d = sqrt(pow((x - x1), 2) + pow((y - y1), 2));
        
        if(d <= this.get_R())
        {
            return 1;
        }
        
        return 0;
    }
}
