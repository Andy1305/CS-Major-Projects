/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


/**
 *
 * @author Andy
 */
public class QuadTree
{

    Node root;

    public QuadTree()
    {
        this.root = new Node();
    }

    public QuadTree(Node n)
    {
        this.root = new Node();

        this.root.info[this.root.size] = new Node(n);
    }

    public int get_Quadrant(Node n, double x_min, double y_min, double x_max, double y_max)
    {
        int flag = 0;

        Point half = new Point((x_min + x_max) / 2, (y_min + y_max) / 2);

        //cadranul 1
        if (n.getLowerLeftPoint().x >= half.x && n.getLowerLeftPoint().y >= half.y)
        {
            flag = 1;
        }

        //cadranul 2
        if (n.getLowerLeftPoint().x <= half.x && (n.getLowerLeftPoint().x <= x_min || n.getLowerLeftPoint().x >= x_min) && n.getLowerLeftPoint().y >= half.y)
        {
            if (n.getUpperRightPoint().x <= half.x && n.getUpperRightPoint().y <= y_max)
            {
                flag = 2;
            } else if (n.getUpperRightPoint().x >= half.x && (n.getUpperRightPoint().y <= y_max || n.getUpperRightPoint().y >= y_max))
            {
                flag = 6;
            } else
            {
                flag = 2;
            }
        }

        //cadranul 3
        if (n.getLowerLeftPoint().x <= half.x && n.getLowerLeftPoint().y <= half.y)
        {
            if (n.getUpperRightPoint().x <= half.x && n.getUpperRightPoint().y <= half.y)
            {
                flag = 3;
            }

            if (n.getUpperRightPoint().x >= half.x && n.getUpperRightPoint().y <= half.y)
            {
                flag = 5;
            }

            if (n.getUpperRightPoint().x <= half.x && n.getUpperRightPoint().y >= half.y)
            {
                flag = 7; //cadranele 2 si 3
            }

            if (n.getUpperRightPoint().x >= half.x && n.getUpperRightPoint().y >= half.y)
            {
                flag = 9;
            }
        }

        //cadranul 4
        if (n.getLowerLeftPoint().x >= half.x && n.getLowerLeftPoint().y <= half.y)
        {
            if (n.getUpperRightPoint().x <= x_max && n.getUpperRightPoint().y <= y_max)
            {
                flag = 4;
            } else if ((n.getUpperRightPoint().x <= x_max || n.getUpperRightPoint().x >= x_max) && n.getUpperRightPoint().y >= half.y)
            {
                flag = 8;
            } else
            {
                flag = 4;
            }
        }

        return flag;
    }

    public int Insert_Collision_Test(Node n1, Node n2)  //n1 = nod de inserat   n2 = nodul deja inserat
    {
        if (n1.getLowerLeftPoint().x <= n2.getLowerRightPoint().x && n1.getLowerLeftPoint().x >= n2.getLowerLeftPoint().x && n1.getLowerLeftPoint().y >= n2.getLowerLeftPoint().y && n1.getLowerLeftPoint().y <= n2.getUpperLeftPoint().y)
        {
            return 1;
        }

        if (n1.getUpperLeftPoint().x <= n2.getLowerRightPoint().x && n1.getUpperLeftPoint().x >= n2.getLowerLeftPoint().x && n1.getUpperLeftPoint().y >= n2.getLowerLeftPoint().y && n1.getUpperLeftPoint().y <= n2.getUpperLeftPoint().y)
        {
            return 1;
        }

        if (n1.getLowerRightPoint().x <= n2.getLowerRightPoint().x && n1.getLowerRightPoint().x >= n2.getLowerLeftPoint().x && n1.getLowerRightPoint().y >= n2.getLowerLeftPoint().y && n1.getLowerRightPoint().y <= n2.getUpperLeftPoint().y)
        {
            return 1;
        }

        if (n1.getUpperRightPoint().x <= n2.getLowerRightPoint().x && n1.getUpperRightPoint().x >= n2.getLowerLeftPoint().x && n1.getUpperRightPoint().y >= n2.getLowerLeftPoint().y && n1.getUpperRightPoint().y <= n2.getUpperLeftPoint().y)
        {
            return 1;
        }

        if (n1.getLowerLeftPoint().x <= n2.getLowerLeftPoint().x && n1.getLowerLeftPoint().y >= n2.getLowerLeftPoint().y && n1.getUpperRightPoint().x >= n2.getUpperRightPoint().x && n1.getUpperRightPoint().y <= n2.getUpperRightPoint().y)
        {
            return 1;
        }

        if (n1.getLowerLeftPoint().x >= n2.getLowerLeftPoint().x && n1.getLowerLeftPoint().y <= n2.getLowerLeftPoint().y && n1.getUpperRightPoint().x <= n2.getUpperRightPoint().x && n1.getUpperRightPoint().y >= n2.getUpperRightPoint().y)
        {
            return 1;
        }

        if (n1.getLowerLeftPoint().x == n2.getLowerLeftPoint().x && n1.getLowerLeftPoint().y == n2.getLowerLeftPoint().y && n1.getUpperRightPoint().x == n2.getUpperRightPoint().x && n1.getUpperRightPoint().y == n2.getUpperRightPoint().y)
        {
            return 1;
        }

        if (n1.getLowerLeftPoint().x <= n2.getLowerLeftPoint().x && n1.getLowerLeftPoint().y <= n2.getLowerLeftPoint().y && n1.getUpperRightPoint().x >= n2.getUpperRightPoint().x && n1.getUpperRightPoint().y >= n2.getUpperRightPoint().y)
        {
            return 1;
        }

        return 0;
    }

    public void Insert(Node node, Node ob, double x_min, double y_min, double x_max, double y_max, int flag)
    {
        int i, quadrant, test = 0, test2 = 0;

        quadrant = get_Quadrant(ob, x_min, y_min, x_max, y_max);

        if (node.size == 0)
        {
            node.info[node.size] = ob;

            node.size++;

            return;
        }

        if (node.size != 0)
        {
            if (quadrant == 1)
            {
                if (node.v[0] == null)
                {
                    node.v[0] = new Node();
                } else if (node.v[0].size != -1)
                {
                    for (i = 0; i < node.v[0].size; i++)
                    {
                        test = Insert_Collision_Test(node.v[0].info[i], ob);
                        test2 = Insert_Collision_Test(ob, node.v[0].info[i]);
                    }

                    if (test == 1 || test2 == 1)
                    {
                        node.v[0].info[node.v[0].size] = ob;

                        node.v[0].size++;

                        if (flag == 0)
                        {
                            return;
                        }
                    }
                }
                if (test == 0 && test2 == 0)
                {
                    Insert(node.v[0], ob, (x_min + x_max) / 2, (y_min + y_max) / 2, x_max, y_max, 0);
                }
            }

            if (quadrant == 2)
            {
                if (node.v[1] == null)
                {
                    node.v[1] = new Node();
                } else if (node.v[1].size != -1)
                {
                    for (i = 0; i < node.v[1].size; i++)
                    {
                        test = Insert_Collision_Test(node.v[1].info[i], ob);
                        test2 = Insert_Collision_Test(ob, node.v[1].info[i]);
                    }

                    if (test == 1 || test2 == 1)
                    {
                        node.v[1].info[node.v[1].size] = ob;

                        node.v[1].size++;
                    }
                }
                if (test == 0 && test2 == 0)
                {
                    Insert(node.v[1], ob, x_min, (y_min + y_max) / 2, (x_min + x_max) / 2, y_max, 0);
                }
            }

            if (quadrant == 3)
            {
                if (node.v[2] == null)
                {
                    node.v[2] = new Node();
                } else if (node.v[2].size != -1)
                {
                    for (i = 0; i < node.v[2].size; i++)
                    {
                        test = Insert_Collision_Test(node.v[2].info[i], ob);
                        test2 = Insert_Collision_Test(ob, node.v[2].info[i]);
                    }

                    if (test == 1 || test2 == 1)
                    {
                        node.v[2].info[node.v[2].size] = ob;

                        node.v[2].size++;
                    }
                }
                if (test == 0 && test2 == 0)
                {
                    Insert(node.v[2], ob, x_min, y_min, (x_min + x_max) / 2, (y_min + y_max) / 2, 0);
                }
            }

            if (quadrant == 4)
            {
                if (node.v[3] == null)
                {
                    node.v[3] = new Node();
                } else if (node.v[3].size != -2)
                {
                    for (i = 0; i < node.v[3].size; i++)
                    {
                        test = Insert_Collision_Test(node.v[3].info[i], ob);
                        test2 = Insert_Collision_Test(ob, node.v[3].info[i]);
                    }

                    if (test == 1 || test2 == 1)
                    {
                        node.v[3].info[node.v[3].size] = ob;

                        node.v[3].size++;
                    }
                }
                if (test == 0 && test2 == 0)
                {
                    Insert(node.v[3], ob, (x_min + x_max) / 2, y_min, x_max, (y_min + y_max) / 2, 0);
                }
            }

            if (quadrant == 5)   //3 si 4
            {
                if (node.v[2] == null)
                {
                    node.v[2] = new Node();
                } else if (node.v[2].size != -1)
                {
                    for (i = 0; i < node.v[2].size; i++)
                    {
                        test = Insert_Collision_Test(node.v[2].info[i], ob);
                        test2 = Insert_Collision_Test(ob, node.v[2].info[i]);
                    }

                    if (test == 1 || test2 == 1)
                    {
                        node.v[2].info[node.v[2].size] = ob;

                        node.v[2].size++;
                    }
                }

                if (test == 0 && test2 == 0)
                {
                    Insert(node.v[2], ob, x_min, y_min, (x_min + x_max) / 2, (y_min + y_max) / 2, 0);
                }

                if (node.v[3] == null)
                {
                    node.v[3] = new Node();
                } else if (node.v[3].size != -1)
                {
                    for (i = 0; i < node.v[3].size; i++)
                    {
                        test = Insert_Collision_Test(node.v[3].info[i], ob);
                        test2 = Insert_Collision_Test(ob, node.v[3].info[i]);
                    }

                    if (test == 1 || test2 == 1)
                    {
                        node.v[3].info[node.v[3].size] = ob;

                        node.v[3].size++;
                    }
                }

                if (test == 0 && test2 == 0)
                {
                    Insert(node.v[3], ob, (x_min + x_max) / 2, y_min, x_max, (y_min + y_max) / 2, 0);
                }
            }

            if (quadrant == 6)   //1 si 2
            {
                if (node.v[0] == null)
                {
                    node.v[0] = new Node();
                } else if (node.v[0].size != -1)
                {
                    for (i = 0; i < node.v[0].size; i++)
                    {
                        test = Insert_Collision_Test(node.v[0].info[i], ob);
                        test2 = Insert_Collision_Test(ob, node.v[0].info[i]);
                    }

                    if (test == 1 || test2 == 1)
                    {
                        node.v[0].info[node.v[0].size] = ob;

                        node.v[0].size++;
                    }
                }

                if (test == 0 && test2 == 0)
                {
                    Insert(node.v[0], ob, (x_min + x_max) / 2, (y_min + y_max) / 2, x_max, y_max, 0);
                }

                {
                    if (node.v[1] == null)
                    {
                        node.v[1] = new Node();
                    } else if (node.v[1].size != -1)
                    {
                        for (i = 0; i < node.v[1].size; i++)
                        {
                            test = Insert_Collision_Test(node.v[1].info[i], ob);
                            test2 = Insert_Collision_Test(ob, node.v[1].info[i]);
                        }

                        if (test == 1 || test2 == 1)
                        {
                            node.v[1].info[node.v[1].size] = ob;

                            node.v[1].size++;
                        }
                    }
                }

                if (test == 0 && test2 == 0)
                {
                    Insert(node.v[1], ob, x_min, (y_min + y_max) / 2, (x_min + x_max) / 2, y_max, 0);
                }
            }

            if (quadrant == 7)   //2 si 3
            {
                if (node.v[1] == null)
                {
                    node.v[1] = new Node();
                } else if (node.v[1].size != -1)
                {
                    for (i = 0; i < node.v[1].size; i++)
                    {
                        test = Insert_Collision_Test(node.v[1].info[i], ob);
                        test2 = Insert_Collision_Test(ob, node.v[1].info[i]);
                    }

                    if (test == 1 || test2 == 1)
                    {
                        node.v[1].info[node.v[1].size] = ob;

                        node.v[1].size++;
                    }
                }

                if (test == 0 && test2 == 0)
                {
                    Insert(node.v[1], ob, x_min, (y_min + y_max) / 2, (x_min + x_max) / 2, y_max, 0);
                }

                {
                    if (node.v[2] == null)
                    {
                        node.v[2] = new Node();
                    } else if (node.v[2].size != -1)
                    {
                        for (i = 0; i < node.v[2].size; i++)
                        {
                            test = Insert_Collision_Test(node.v[2].info[i], ob);
                            test2 = Insert_Collision_Test(ob, node.v[2].info[i]);
                        }

                        if (test == 1 || test2 == 1)
                        {
                            node.v[2].info[node.v[2].size] = ob;

                            node.v[2].size++;
                        }
                    }
                }

                if (test == 0 && test2 == 0)
                {
                    Insert(node.v[2], ob, x_min, y_min, (x_min + x_max) / 2, (y_min + y_max) / 2, 0);
                }

            }

            if (quadrant == 8)   //1 si 4
            {
                if (node.v[0] == null)
                {
                    node.v[0] = new Node();
                } else if (node.v[0].size != -1)
                {
                    for (i = 0; i < node.v[0].size; i++)
                    {
                        test = Insert_Collision_Test(node.v[0].info[i], ob);
                        test2 = Insert_Collision_Test(ob, node.v[0].info[i]);
                    }

                    if (test == 1 || test2 == 1)
                    {
                        node.v[0].info[node.v[0].size] = ob;

                        node.v[0].size++;
                    }
                }

                if (test == 0 && test2 == 0)
                {
                    Insert(node.v[0], ob, (x_min + x_max) / 2, (y_min + y_max) / 2, x_max, y_max, 0);
                }

                if (node.v[3] == null)
                {
                    node.v[3] = new Node();
                } else if (node.v[3].size != -1)
                {
                    for (i = 0; i < node.v[3].size; i++)
                    {
                        test = Insert_Collision_Test(node.v[3].info[i], ob);
                        test2 = Insert_Collision_Test(ob, node.v[3].info[i]);
                    }

                    if (test == 1 || test2 == 1)
                    {
                        node.v[3].info[node.v[3].size] = ob;

                        node.v[3].size++;
                    }
                }

                if (test == 0 && test2 == 0)
                {
                    Insert(node.v[3], ob, (x_min + x_max) / 2, y_min, x_max, (y_min + y_max) / 2, 0);
                }
            }

            if (quadrant == 9)   //toate
            {
                if (node.v[0] == null)
                {
                    node.v[0] = new Node();
                } else if (node.v[0].size != -1 && node.size != -2)
                {
                    for (i = 0; i < node.v[0].size; i++)
                    {
                        test = Insert_Collision_Test(node.v[0].info[i], ob);
                        test2 = Insert_Collision_Test(ob, node.v[0].info[i]);
                    }

                    if (test == 1 || test2 == 1)
                    {
                        node.v[0].info[node.v[0].size] = ob;

                        node.v[0].size++;
                    }
                }

                if (test == 0 && test2 == 0)
                {
                    Insert(node.v[0], ob, (x_min + x_max) / 2, (y_min + y_max) / 2, x_max, y_max, 0);
                }

                if (node.v[1] == null)
                {
                    node.v[1] = new Node();
                } else if (node.v[1].size != -1)
                {
                    for (i = 0; i < node.v[1].size; i++)
                    {
                        test = Insert_Collision_Test(node.v[1].info[i], ob);
                        test2 = Insert_Collision_Test(ob, node.v[1].info[i]);
                    }

                    if (test == 1 || test2 == 1)
                    {
                        node.v[1].info[node.v[1].size] = ob;

                        node.v[1].size++;
                    }
                }

                if (test == 0 && test2 == 0)
                {
                    Insert(node.v[1], ob, x_min, (y_min + y_max) / 2, (x_min + x_max) / 2, y_max, 0);
                }

                if (node.v[2] == null)
                {
                    node.v[2] = new Node();
                } else if (node.v[2].size != -1)
                {
                    for (i = 0; i < node.v[2].size; i++)
                    {
                        test = Insert_Collision_Test(node.v[2].info[i], ob);
                        test2 = Insert_Collision_Test(ob, node.v[2].info[i]);
                    }

                    if (test == 1 || test2 == 1)
                    {
                        node.v[2].info[node.v[2].size] = ob;

                        node.v[2].size++;
                    }
                }

                if (test == 0 && test2 == 0)
                {
                    Insert(node.v[2], ob, x_min, y_min, (x_min + x_max) / 2, (y_min + y_max) / 2, 0);
                }

                if (node.v[3] == null)
                {
                    node.v[3] = new Node();
                } else if (node.v[3].size != -1)
                {
                    for (i = 0; i < node.v[3].size; i++)
                    {
                        test = Insert_Collision_Test(node.v[3].info[i], ob);
                        test2 = Insert_Collision_Test(ob, node.v[3].info[i]);
                    }

                    if (test == 1 || test2 == 1)
                    {
                        node.v[3].info[node.v[3].size] = ob;

                        node.v[3].size++;
                    }
                }

                if (test == 0 && test2 == 0)
                {
                    Insert(node.v[3], ob, (x_min + x_max) / 2, y_min, x_max, (y_min + y_max) / 2, 0);
                }

            }

            if (flag == 1 && node.info[node.size - 1].get_ID() == ob.get_ID())
            {
                node.size = -1;

                return;
            }

            for (i = 0; i < node.size; i++)
            {
                if (ob.get_ID() == node.info[i].get_ID())
                {
                    return;
                }
            }

            if (node.size != 0 && node.size != -1 && node.size != -2)
            {
                for (i = 0; i < node.size; i++)
                {
                    Insert(node, node.info[i], x_min, y_min, x_max, y_max, 1);
                }
            }
        }
    }

    public void Delete(Node node, double ID)
    {
        int i, j, count = 0, position[] = new int[100000];

        if (node == null || node.info == null)
        {
            return;
        }

        Delete(node.v[0], ID);
        Delete(node.v[1], ID);
        Delete(node.v[2], ID);
        Delete(node.v[3], ID);

        if (node.size != -1 && node.size != -2)
        {
            for (i = 0; i < node.size; i++)
            {
                if (node.info[i].get_ID() == ID)
                {
                    position[count] = i;

                    count++;
                }
            }
        }

        if (count == node.size && node.info != null && node.size != 0)
        {
            node.info = null;
            //node = null;
        } else
        {
            for (i = 0; i < count; i++)
            {
                for (j = position[i]; j < node.size - 1; j++)
                {
                    node.info[j] = node.info[j++];
                }
            }
        }
    }

    public String Point_Collision_Test(Node node, String s, double x, double y)
    {
        int i;

        if (node == null)
        {
            return null;
        }

        if (node.v[0] != null)
        {
            s = Point_Collision_Test(node.v[0], s, x, y);
        }

        if (node.v[1] != null)
        {
            s = Point_Collision_Test(node.v[1], s, x, y);
        }

        if (node.v[2] != null)
        {
            s = Point_Collision_Test(node.v[2], s, x, y);
        }

        if (node.v[3] != null)
        {
            s = Point_Collision_Test(node.v[3], s, x, y);
        }

        for (i = 0; i < node.size; i++)
        {
            if (node.info != null && node.size != -1 &&  node.size != -2)
            {
                if (node.info[i].Point_Collision_Test_2(x, y) == 1)
                {
                    int aux = (int) node.info[i].get_ID();

                    if (!s.contains(Integer.toString(aux)))
                    {
                        s += String.valueOf((int) (node.info[i].get_ID()));
                        s += " ";
                    }
                }
            }
        }

        return s;
    }

    public String Collision_Test(Node n1, Node n2, String s)
    {
        int i;

        if (n1 == null)
        {
            return null;
        }

        if (n1.v[0] != null)
        {
            s = Collision_Test(n1.v[0], n2, s);
        }

        if (n1.v[1] != null)
        {
            s = Collision_Test(n1.v[1], n2, s);
        }

        if (n1.v[2] != null)
        {
            s = Collision_Test(n1.v[2], n2, s);
        }

        if (n1.v[3] != null)
        {
            s = Collision_Test(n1.v[3], n2, s);
        }

        for (i = 0; i < n1.size; i++)
        {
            if (n1.info != null && n1.size != -1 && n1.size != -2)
            {
                int aux = (int) n1.info[i].get_ID();

                if(n1.info[i].getLowerLeftPoint().x < n2.getLowerLeftPoint().x && n1.info[i].getUpperRightPoint().x > n2.getUpperRightPoint().y && n1.info[i].getLowerLeftPoint().y == n2.getLowerLeftPoint().y && n1.info[i].getUpperRightPoint().y >= n2.getUpperRightPoint().y)
                {
                    continue;////////////
                }
                
                if (n1.info[i].getLowerLeftPoint().x < n2.getLowerRightPoint().x && n1.info[i].getLowerLeftPoint().x > n2.getLowerLeftPoint().x && n1.info[i].getLowerLeftPoint().y > n2.getLowerLeftPoint().y && n1.info[i].getLowerLeftPoint().y < n2.getUpperLeftPoint().y)
                {
                    if (!s.contains(Integer.toString(aux)))
                    {
                        s += String.valueOf((int) n1.info[i].get_ID());
                        s += " ";
                    }

                    continue;
                }

                if (n2.getLowerLeftPoint().x < n1.info[i].getLowerRightPoint().x && n2.getLowerLeftPoint().x > n1.info[i].getLowerLeftPoint().x && n2.getLowerLeftPoint().y > n1.info[i].getLowerLeftPoint().y && n2.getLowerLeftPoint().y < n1.info[i].getUpperLeftPoint().y)
                {
                    if (!s.contains(Integer.toString(aux)))
                    {
                        s += String.valueOf((int) n1.info[i].get_ID());
                        s += " ";
                    }

                    continue;
                }

                if (n1.info[i].getUpperLeftPoint().x < n2.getLowerRightPoint().x && n1.info[i].getUpperLeftPoint().x > n2.getLowerLeftPoint().x && n1.info[i].getUpperLeftPoint().y > n2.getLowerLeftPoint().y && n1.info[i].getUpperLeftPoint().y < n2.getUpperLeftPoint().y)
                {
                    if (!s.contains(Integer.toString(aux)))
                    {
                        s += String.valueOf((int) n1.info[i].get_ID());
                        s += " ";
                    }

                    continue;
                }

                if (n2.getUpperLeftPoint().x < n1.info[i].getLowerRightPoint().x && n2.getUpperLeftPoint().x > n1.info[i].getLowerLeftPoint().x && n2.getUpperLeftPoint().y > n1.info[i].getLowerLeftPoint().y && n2.getUpperLeftPoint().y < n1.info[i].getUpperLeftPoint().y)
                {
                    if (!s.contains(Integer.toString(aux)))
                    {
                        s += String.valueOf((int) n1.info[i].get_ID());
                        s += " ";
                    }

                    continue;
                }

                if (n1.info[i].getLowerRightPoint().x < n2.getLowerRightPoint().x && n1.info[i].getLowerRightPoint().x > n2.getLowerLeftPoint().x && n1.info[i].getLowerRightPoint().y > n2.getLowerLeftPoint().y && n1.info[i].getLowerRightPoint().y < n2.getUpperLeftPoint().y)
                {
                    if (!s.contains(Integer.toString(aux)))
                    {
                        s += String.valueOf((int) n1.info[i].get_ID());
                        s += " ";
                    }

                    continue;
                }

                if (n2.getLowerRightPoint().x < n1.info[i].getLowerRightPoint().x && n2.getLowerRightPoint().x > n1.info[i].getLowerLeftPoint().x && n2.getLowerRightPoint().y > n1.info[i].getLowerLeftPoint().y && n2.getLowerRightPoint().y < n1.info[i].getUpperLeftPoint().y)
                {
                    if (!s.contains(Integer.toString(aux)))
                    {
                        s += String.valueOf((int) n1.info[i].get_ID());
                        s += " ";
                    }

                    continue;
                }

                if (n1.info[i].getUpperRightPoint().x < n2.getLowerRightPoint().x && n1.info[i].getUpperRightPoint().x > n2.getLowerLeftPoint().x && n1.info[i].getUpperRightPoint().y > n2.getLowerLeftPoint().y && n1.info[i].getUpperRightPoint().y < n2.getUpperLeftPoint().y)
                {
                    if (!s.contains(Integer.toString(aux)))
                    {
                        s += String.valueOf((int) n1.info[i].get_ID());
                        s += " ";
                    }

                    continue;
                }
////////////////////////////////////////////////////////////
                if (n2.getUpperRightPoint().x < n1.info[i].getLowerRightPoint().x && n2.getUpperRightPoint().x > n1.info[i].getLowerLeftPoint().x && n2.getUpperRightPoint().y > n1.info[i].getLowerLeftPoint().y && n2.getUpperRightPoint().y < n1.info[i].getUpperLeftPoint().y)
                {
                    if (!s.contains(Integer.toString(aux)))
                    {
                        s += String.valueOf((int) n1.info[i].get_ID());
                        s += " ";
                    }

                    continue;
                }

                if (n1.info[i].getLowerLeftPoint().x < n2.getLowerLeftPoint().x && n1.info[i].getLowerLeftPoint().y > n2.getLowerLeftPoint().y && n1.info[i].getUpperRightPoint().x > n2.getUpperRightPoint().x && n1.info[i].getUpperRightPoint().y < n2.getUpperRightPoint().y)
                {
                    if (!s.contains(Integer.toString(aux)))
                    {
                        s += String.valueOf((int) n1.info[i].get_ID());
                        s += " ";
                    }

                    continue;
                }
///////////////////////////////////////////////////////////////////////
                if (n2.getLowerLeftPoint().x < n1.info[i].getLowerLeftPoint().x && n2.getLowerLeftPoint().y > n1.info[i].getLowerLeftPoint().y && n2.getUpperRightPoint().x > n1.info[i].getUpperRightPoint().x && n2.getUpperRightPoint().y < n1.info[i].getUpperRightPoint().y)
                {
                    if (!s.contains(Integer.toString(aux)))
                    {
                        s += String.valueOf((int) n1.info[i].get_ID());
                        s += " ";
                    }

                    continue;
                }

                if (n1.info[i].getLowerLeftPoint().x > n2.getLowerLeftPoint().x && n1.info[i].getLowerLeftPoint().y < n2.getLowerLeftPoint().y && n1.info[i].getUpperRightPoint().x < n2.getUpperRightPoint().x && n1.info[i].getUpperRightPoint().y > n2.getUpperRightPoint().y)
                {
                    if (!s.contains(Integer.toString(aux)))
                    {
                        s += String.valueOf((int) n1.info[i].get_ID());
                        s += " ";
                    }

                    continue;
                }

                if (n2.getLowerLeftPoint().x > n1.info[i].getLowerLeftPoint().x && n2.getLowerLeftPoint().y < n1.info[i].getLowerLeftPoint().y && n2.getUpperRightPoint().x < n1.info[i].getUpperRightPoint().x && n2.getUpperRightPoint().y > n1.info[i].getUpperRightPoint().y)
                {
                    if (!s.contains(Integer.toString(aux)))
                    {
                        s += String.valueOf((int) n1.info[i].get_ID());
                        s += " ";
                    }

                    continue;
                }

                if (n1.info[i].getLowerLeftPoint().x == n2.getLowerLeftPoint().x && n1.info[i].getLowerLeftPoint().y == n2.getLowerLeftPoint().y && n1.info[i].getUpperRightPoint().x == n2.getUpperRightPoint().x && n1.info[i].getUpperRightPoint().y == n2.getUpperRightPoint().y)
                {
                    if (!s.contains(Integer.toString(aux)))
                    {
                        s += String.valueOf((int) n1.info[i].get_ID());
                        s += " ";
                    }
                    
                    continue;
                }

                if (n1.info[i].getLowerLeftPoint().x < n2.getLowerLeftPoint().x && n1.info[i].getLowerLeftPoint().y < n2.getLowerLeftPoint().y && n1.info[i].getUpperRightPoint().x > n2.getUpperRightPoint().x && n1.info[i].getUpperRightPoint().y > n2.getUpperRightPoint().y)
                {
                    if (!s.contains(Integer.toString(aux)))
                    {
                        s += String.valueOf((int) n1.info[i].get_ID());
                        s += " ";
                    }
                    
                    continue;
                }

                if (n2.getLowerLeftPoint().x < n1.info[i].getLowerLeftPoint().x && n2.getLowerLeftPoint().y < n1.info[i].getLowerLeftPoint().y && n2.getUpperRightPoint().x > n1.info[i].getUpperRightPoint().x && n2.getUpperRightPoint().y > n1.info[i].getUpperRightPoint().y)
                {
                    if (!s.contains(Integer.toString(aux)))
                    {
                        s += String.valueOf((int) n1.info[i].get_ID());
                        s += " ";
                    }
                }
            }
        }

        return s;
    }

    public void Display(Node node)
    {
        int i;
        if (node == null)
        {
            return;
        }

        Display(node.v[0]);
        Display(node.v[1]);
        Display(node.v[2]);
        Display(node.v[3]);

        if (node.size != 0 && node.size != -1 && node.size != -2)
        {
            for (i = 0; i < node.size; i++)
            {
                if (node.size != -1)
                {
                    System.out.println(node.info[i].get_ID());
                }
            }
        }
    }
}
