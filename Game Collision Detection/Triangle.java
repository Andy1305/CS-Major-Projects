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
public class Triangle extends Node
{

    double ID, x1, y1, x2, y2, x3, y3, size;

    public Triangle()
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
    public Point getLowerLeftPoint()
    {
        Point p = null;

        if ((x1 >= x2) && (x1 <= x3) && (y1 >= y2) && (y1 >= y3))
        {
            p = new Point(x2, y2);
        }

        if ((x1 <= x2) && (x1 <= x3) && (y1 >= y2) && (y1 <= y3))
        {
            p = new Point(x1, y2);
        }

        if ((x1 >= x3) && (x1 <= x2) && (y1 <= y3) && (y1 <= y2))
        {
            p = new Point(x3, y1);
        }

        if ((x1 >= x2) && (x1 <= x3) && (y1 <= y3) && (y1 <= y2))
        {
            p = new Point(x2, y1);
        }

        if ((x1 >= x2) && (x1 >= x3) && (y1 >= y3) && (y1 <= y2))
        {
            p = new Point(x3, y3);
        }

        return p;
    }

    @Override
    public Point getLowerRightPoint()
    {
        Point p = null;

        if ((x1 >= x2) && (x1 <= x3) && (y1 >= y2) && (y1 >= y3))
        {
            p = new Point(x3, y3);
        }

        if ((x1 <= x2) && (x1 <= x3) && (y1 >= y2) && (y1 <= y3))
        {
            p = new Point(x2, y2);
        }

        if ((x1 >= x3) && (x1 <= x2) && (y1 <= y3) && (y1 <= y2))
        {
            p = new Point(x2, y1);
        }

        if ((x1 >= x2) && (x1 <= x3) && (y1 <= y3) && (y1 <= y2))
        {
            p = new Point(x3, y1);
        }

        if ((x1 >= x2) && (x1 >= x3) && (y1 >= y3) && (y1 <= y2))
        {
            p = new Point(x1, y3);
        }

        return p;
    }

    @Override
    public Point getUpperLeftPoint()
    {
        Point p = null;

        if ((x1 >= x2) && (x1 <= x3) && (y1 >= y2) && (y1 >= y3))
        {
            p = new Point(x2, y1);
        }

        if ((x1 <= x2) && (x1 <= x3) && (y1 >= y2) && (y1 <= y3))
        {
            p = new Point(x1, y3);
        }

        if ((x1 >= x3) && (x1 <= x2) && (y1 <= y3) && (y1 <= y2))
        {
            p = new Point(x3, y3);
        }

        if ((x1 >= x2) && (x1 <= x3) && (y1 <= y3) && (y1 <= y2))
        {
            p = new Point(x2, y2);
        }

        if ((x1 >= x2) && (x1 >= x3) && (y1 >= y3) && (y1 <= y2))
        {
            p = new Point(x2, y2);
        }

        return p;
    }

    @Override
    public Point getUpperRightPoint()
    {
        Point p = null;

        if ((x1 >= x2) && (x1 <= x3) && (y1 >= y2) && (y1 >= y3))
        {
            p = new Point(x3, y1);
        }

        if ((x1 <= x2) && (x1 <= x3) && (y1 >= y2) && (y1 <= y3))
        {
            p = new Point(x3, y3);
        }

        if ((x1 >= x3) && (x1 <= x2) && (y1 <= y3) && (y1 <= y2))
        {
            p = new Point(x2, y2);
        }

        if ((x1 >= x2) && (x1 <= x3) && (y1 <= y3) && (y1 <= y2))
        {
            p = new Point(x3, y3);
        }

        if ((x1 >= x2) && (x1 >= x3) && (y1 >= y3) && (y1 <= y2))
        {
            p = new Point(x1, y2);
        }

        return p;
    }

    @Override
    public int Point_Collision_Test_2(double x, double y)
    {
        double area, area_PAB, area_PAC, area_PBC, p, p_PAB, p_PAC, p_PBC;
        
        p = (abs(x1 - x2) + abs(x2 - x3) + abs(x3 - x1)) / 2;
        
        area = sqrt(p * (p - abs(x1 - x2)) * (p - abs(x2 - x3)) * (p - abs(x3 - x1)));
        
        p_PAB = (abs(x - x1) + abs(x1 - x2) + abs(x2 - x)) / 2;
        
        area_PAB = sqrt(p_PAB * (p_PAB - abs(x - x1)) * (p_PAB - abs(x1 - x2)) * (p_PAB - abs(x2 - x)));
        
        p_PAC = (abs(x - x1) + abs(x1 - x3) + abs(x3 - x)) / 2;
        
        area_PAC = sqrt(p_PAC * (p_PAC - abs(x - x1) * (p_PAC - abs(x1 - x3)) * (p_PAC - abs(x3 - x1))));
        
        p_PBC = (abs(x - x2) + abs(x2 - x3) + abs(x3 - x)) / 2;
        
        area_PBC = sqrt(p_PBC * (p_PBC - abs(x - x2)) * (p_PBC - abs(x2 - x3)) * (p_PBC - abs(x3 - x)));
        
        if(area == area_PAB + area_PAC + area_PBC && x != x1 && x != x2)
        {
            return 1;
        }
        
        return 0;
    }
}
