/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


/**
 *
 * @author Andy
 */
public class Node
{
    int size = 0;
    double ID, x1, y1, x2, y2, x3, y3, x4, y4, R;
    
    Node[] info;
    
    Node v[];       //retine fii
    
    public Node()
    {    
        info = new Node[10000];
        
        v = new Node[4];
    }
    
    public Node(Node n)
    {
        info = new Node[10000];
        
        v = new Node[4];
        
        this.ID = n.get_ID();
        
        this.x1 = n.get_x1();
        this.x2 = n.get_x2();
        this.x3 = n.get_x3();
        this.x4 = n.get_x4();
        
        this.y1 = n.get_y1();
        this.y2 = n.get_y2();
        this.y3 = n.get_y3();
        this.y4 = n.get_y4();
        
        this.R = n.get_R();
    }
    
    public double get_x1()
    {
        return x1;
    }
    
    public double get_y1()
    {
        return y1;
    }
    
    public double get_x2()
    {
        return x2;
    }
    
    public double get_y2()
    {
        return y2;
    }
    
    public double get_x3()
    {
        return x3;
    }
    
    public double get_y3()
    {
        return y3;
    }
    
    public double get_x4()
    {
        return x4;
    }
    public double get_y4()
    {
        return y4;
    }
    
    public double get_ID()
    {
        return ID;
    }
    
    public double get_R()
    {
        return R;
    }
    
    public Point getLowerLeftPoint()
    {
        Point p = new Point(x1, y1);
        
        return p;
    }
    
    public Point getLowerRightPoint()
    {
        Point p = new Point(x2, y1);
        
        return p;
    }
    
    public Point getUpperLeftPoint()
    {
        Point p = new Point(x1, y2);
        
        return p;
    }
    
    public Point getUpperRightPoint()
    {
        Point p = new Point(x2, y2);
        
        return p;
    }
    
    public int Point_Collision_Test_2(double x, double y)
    {
        return 0;
    }
}
