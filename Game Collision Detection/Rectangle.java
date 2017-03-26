/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


/**
 *
 * @author Andy
 */
public class Rectangle extends Node
{

    double ID, x1, y1, x2, y2, size = -7;

    public Rectangle()
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
    public Point getLowerLeftPoint()
    {
        Point p = new Point(x1, y1);

        return p;
    }

    @Override
    public Point getLowerRightPoint()
    {
        Point p = new Point(x2, y1);

        return p;
    }

    @Override
    public Point getUpperLeftPoint()
    {
        Point p = new Point(x1, y2);

        return p;
    }

    @Override
    public Point getUpperRightPoint()
    {
        Point p = new Point(x2, y2);

        return p;
    }

    @Override
    public int Point_Collision_Test_2(double x, double y)
    {
        if (this.getLowerLeftPoint().x <= x && this.getLowerLeftPoint().y <= y && this.getUpperRightPoint().x >= x && this.getUpperRightPoint().y >= y)
        {
            return 1;
        }
        
        return 0;
    }
}
