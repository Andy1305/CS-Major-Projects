/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


import java.util.Scanner;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;

import java.util.Arrays;

/**
 *
 * @author Andy
 */
public class GameCollisionDetection
{

    public static int[] String_to_Int(String str)
    {
        int i;

        String straux[] = str.split(" ");

        int intArray[] = new int[straux.length];

        for (i = 0; i < straux.length; i++)
        {
            intArray[i] = Integer.parseInt(straux[i]);
        }

        return intArray;
    }

    /**
     * @param args the command line arguments
     * @throws java.io.FileNotFoundException
     */
    public static void main(String[] args) throws FileNotFoundException
    {
        double x_min, y_min, x_max, y_max, op, fig, ID, x, y;

        Rectangle aux = new Rectangle();

        aux.ID = -1;

        QuadTree q = new QuadTree(aux);

        q.root.size = -2;

        Scanner s = new Scanner(new File("quadtree.in"));

        PrintWriter writer = new PrintWriter("quadtree.out");

        x_min = s.nextDouble();
        y_min = s.nextDouble();
        x_max = s.nextDouble();
        y_max = s.nextDouble();

        while (s.hasNextDouble())
        {
            op = s.nextDouble();
            fig = s.nextDouble();

            if (op == 11)
            {
                if (fig == 1)
                {
                    Rectangle r = new Rectangle();

                    r.ID = s.nextInt();
                    r.x1 = s.nextDouble();
                    r.y1 = s.nextDouble();
                    r.x2 = s.nextDouble();
                    r.y2 = s.nextDouble();

                    q.Insert(q.root, r, x_min, y_min, x_max, y_max, 0);

                    continue;
                }

                if (fig == 2)
                {
                    Triangle t = new Triangle();

                    t.ID = s.nextInt();
                    t.x1 = s.nextDouble();
                    t.y1 = s.nextDouble();
                    t.x2 = s.nextDouble();
                    t.y2 = s.nextDouble();
                    t.x3 = s.nextDouble();
                    t.y3 = s.nextDouble();

                    q.Insert(q.root, t, x_min, y_min, x_max, y_max, 0);

                    continue;
                }

                if (fig == 3)
                {
                    Circle c = new Circle();

                    c.ID = s.nextInt();
                    c.R = s.nextDouble();
                    c.x1 = s.nextDouble();
                    c.y1 = s.nextDouble();

                    q.Insert(q.root, c, x_min, y_min, x_max, y_max, 0);

                    continue;

                }

                if (fig == 4)
                {
                    Diamond d = new Diamond();

                    d.ID = s.nextInt();
                    d.x1 = s.nextDouble();
                    d.y1 = s.nextDouble();
                    d.x2 = s.nextDouble();
                    d.y2 = s.nextDouble();
                    d.x3 = s.nextDouble();
                    d.y3 = s.nextDouble();
                    d.x4 = s.nextDouble();
                    d.y4 = s.nextDouble();

                    d.Order(d.x1, d.y1, d.x2, d.y2, d.x3, d.y3, d.x4, d.y4);

                    q.Insert(q.root, d, x_min, y_min, x_max, y_max, 0);

                    continue;
                }
            }

            if (op == 22)
            {
                q.Delete(q.root, fig);

                continue;
            }

            if (op == 33)
            {
                String str = "";

                y = s.nextInt();

                str = q.Point_Collision_Test(q.root, str, fig, y);

                if ("".equals(str))
                {
                    writer.println("NIL");
                } else
                {
                    str = str.substring(0, str.length() - 1);

                    int intArray[] = String_to_Int(str).clone();

                    Arrays.sort(intArray);

                    writer.println(Arrays.toString(intArray).replace("[", "").replace("]", "").replace(",", ""));
                }

                continue;
            }

            if (op == 44)
            {
                String str = "";

                if (fig == 1)
                {
                    Rectangle r = new Rectangle();

                    r.x1 = s.nextDouble();
                    r.y1 = s.nextDouble();
                    r.x2 = s.nextDouble();
                    r.y2 = s.nextDouble();

                    str = q.Collision_Test(q.root, r, str);

                    if ("".equals(str))
                    {
                        writer.println("NIL");
                    } else
                    {
                        str = str.substring(0, str.length() - 1);

                        int intArray[] = String_to_Int(str).clone();

                        Arrays.sort(intArray);

                        writer.println(Arrays.toString(intArray).replace("[", "").replace("]", "").replace(",", ""));
                    }

                    continue;
                }

                if (fig == 2)
                {
                    Triangle t = new Triangle();

                    t.x1 = s.nextDouble();
                    t.y1 = s.nextDouble();
                    t.x2 = s.nextDouble();
                    t.y2 = s.nextDouble();
                    t.x3 = s.nextDouble();
                    t.y3 = s.nextDouble();

                    str = q.Collision_Test(q.root, t, str);

                    if ("".equals(str))
                    {
                        writer.println("NIL");
                    } else
                    {
                        str = str.substring(0, str.length() - 1);

                        int intArray[] = String_to_Int(str).clone();

                        Arrays.sort(intArray);

                        writer.println(Arrays.toString(intArray).replace("[", "").replace("]", "").replace(",", ""));
                    }

                    continue;
                }

                if (fig == 3)
                {
                    Circle c = new Circle();

                    c.R = s.nextDouble();
                    c.x1 = s.nextDouble();
                    c.y1 = s.nextDouble();

                    str = q.Collision_Test(q.root, c, str);

                    if ("".equals(str))
                    {
                        writer.println("NIL");
                    } else
                    {
                        str = str.substring(0, str.length() - 1);

                        int intArray[] = String_to_Int(str).clone();

                        Arrays.sort(intArray);

                        writer.println(Arrays.toString(intArray).replace("[", "").replace("]", "").replace(",", ""));
                    }

                    continue;
                }

                if (fig == 4)
                {
                    Diamond d = new Diamond();

                    d.x1 = s.nextDouble();
                    d.y1 = s.nextDouble();
                    d.x2 = s.nextDouble();
                    d.y2 = s.nextDouble();
                    d.x3 = s.nextDouble();
                    d.y3 = s.nextDouble();
                    d.x4 = s.nextDouble();
                    d.y4 = s.nextDouble();

                    str = q.Collision_Test(q.root, d, str);

                    if ("".equals(str))
                    {
                        writer.println("NIL");
                    } else
                    {
                        str = str.substring(0, str.length() - 1);

                        int intArray[] = String_to_Int(str).clone();

                        Arrays.sort(intArray);

                        writer.println(Arrays.toString(intArray).replace("[", "").replace("]", "").replace(",", ""));
                    }
                }
            }
        }

        s.close();
        writer.close();

        //q.Display(q.root);
    }
}
