/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Iterator;

/**
 *
 * @author Andy
 *
 * Clasa graf implementeaza operatiile interfetei.
 */
public class Graph implements GraphInterface
{

    int flag2 = 0, j = 0;
    ArrayList<Node> nodes = new ArrayList<>();

    /**
     * @param node
     *
     * Insereaza un nod in graf, in cazul in care acesta nu exista.
     */
    @Override
    public void Insert(Node node)
    {
        for (Node traverse : nodes)
        {
            if (traverse.getName().equals(node.getName()))  //Verific cazul in care nodul exista deja.
            {
                return;
            }
        }

        nodes.add(node);
    }

    /**
     * @param nodeType
     * @param name
     *
     * Sterge un nod din graf si legaturile cu celelalte noduri.
     */
    @Override
    public void Delete(String nodeType, String name)
    {
        Iterator<Node> it = nodes.iterator();

        while (it.hasNext())
        {
            Node node = it.next();

            if (node.getName().equals(name))
            {
                it.remove();
            } else
            {
                node.deleteNeighbors(node.getName());   //Sterg legaturile nodului cu toate celelalte noduri.
            }
        }
    }

    /**
     * @param node1
     * @param node2
     *
     * Insereaza o muchie, in caz ca aceasta nu exista.
     */
    @Override
    public void InsertM(Node node1, Node node2)
    {
        node1.addNeighbors(node2);
        node2.addNeighbors(node1);
    }

    /**
     * @param name1
     * @param name2
     *
     * Sterge legatura dintre doua noduri.
     */
    @Override
    public void DeleteM(String name1, String name2)
    {
        for (Node node : nodes)
        {
            if (node.getName().equals(name1))
            {
                node.deleteNeighbors(name2);
            }

            if (node.getName().equals(name2))
            {
                node.deleteNeighbors(name1);
            }
        }
    }

    /**
     * @param name
     * @return
     *
     * Gaseste o anumita informatie din graf si returneaza nodul respectiv.
     */
    @Override
    public Node findInfo(String name)
    {
        for (Node node : nodes)
        {
            if (node.getName().equals(name))
            {
                return node;
            }
        }

        return null;
    }

    /**
     *
     * @param node
     * @param buffer
     * @param level
     * @return
     *
     * Operatia de serializare, exact ca in exemplul din enunt. Returneaza stringul cu serializarea, ce va fi scris in fisier.
     */
    @Override
    public String Serialize(Node node, String buffer, int level)
    {
        int i, flag = 0;
        String buffer2 = "";

        node.flag = 1;

        for (i = 0; i < level; i++)
        {
            buffer2 += "\t\t";
        }

        if (flag2 == 1)
        {
            buffer2 = buffer2.substring(2, buffer2.length());
        }

        if (level == 0)
        {
            buffer = "<Object class=\"" + node.getClass().getSimpleName() + "\" Version=\"" + node.getIteration() + "\" id=\"" + node.getID() + "\">\n";

            buffer += "\t" + "<Nume>" + node.getName() + "</Nume>\n";
        } else
        {
            buffer = "<Object class=\"" + node.getClass().getSimpleName() + "\" Version=\"" + node.getIteration() + "\" id=\"" + node.getID() + "\">\n";

            buffer += buffer2 + "\t<Nume>" + node.getName() + "</Nume>\n";
        }

        buffer = buffer2 + buffer;

        if (node.getIteration() == 1)
        {
            if (level == 0)
            {
                buffer += buffer2 + "\t<LIST>\n";
            } else
            {
                buffer += buffer2 + "\t<LIST>\n";
            }

            List list = node.getNeighborsList();

            if (list == null)
            {
                return "";
            }

            Iterator<Node> it = list.list.iterator();

            while (it.hasNext())
            {
                Node aux = it.next();

                if (aux.flag == 0)
                {
                    buffer += Serialize(aux, buffer, ++level);

                    if (!aux.getName().equals(list.list.get(0).getName()))
                    {
                        flag2 = 1;
                    }

                    flag = 1;
                } else if (flag == 0)
                {
                    buffer += buffer2 + "\t\t<Reference class=\"" + aux.getClass().getSimpleName() + "\" Version=\"" + aux.getIteration() + "\" id=\"" + aux.getID() + "\">\n";

                    if (!aux.getName().equals(list.list.get(0).getName()))
                    {
                        flag2 = 1;
                    }
                }
            }

            buffer += buffer2 + "\t</LIST>\n" + buffer2 + "</Object>\n";
        }

        if (node.getIteration() == 2)
        {
            if (level == 0)
            {
                buffer += buffer2 + "\t<VECTOR>\n";
            } else
            {
                buffer += buffer2 + "\t<VECTOR>\n";
            }

            Vector vector = node.getNeighborsVector();

            if (vector == null)
            {
                return "";
            }

            Iterator<Node> it = vector.array.iterator();

            while (it.hasNext())
            {
                Node aux = it.next();

                if (aux.flag == 0)
                {

                    buffer += Serialize(aux, buffer, ++level);
                    if (!aux.getName().equals(vector.array.get(0).getName()))
                    {

                        flag2 = 1;
                    }

                    flag = 1;
                } else if (flag == 0)
                {
                    buffer += buffer2 + "\t\t<Reference class=\"" + aux.getClass().getSimpleName() + "\" Version=\"" + aux.getIteration() + "\" id=\"" + aux.getID() + "\">\n";

                    if (!aux.getName().equals(vector.array.get(0).getName()))
                    {

                        flag2 = 1;
                    }
                }
            }

            buffer += buffer2 + "\t</VECTOR>\n" + buffer2 + "</Object>\n";
        }

        if (node.getIteration() == 3)
        {
            if (level == 0)
            {
                buffer += buffer2 + "\t\t<SET>\n";
            } else
            {
                buffer += buffer2 + "\t<SET>\n";
            }

            Set set = node.getNeighborsSet();

            if (set == null)
            {
                return "";
            }

            Iterator<Node> it = set.set.iterator();
            Iterator<Node> it2 = set.set.iterator();

            while (it.hasNext())
            {
                Node aux = it.next();

                if (aux.flag == 0)
                {
                    buffer += Serialize(aux, buffer, ++level);

                    if (!aux.getName().equals(it2.next().getName()))
                    {
                        flag2 = 1;
                    }

                    flag = 1;
                } else if (flag == 0)
                {
                    buffer += buffer2 + "\t\t<Reference class=\"" + aux.getClass().getSimpleName() + "\" Version=\"" + aux.getIteration() + "\" id=\"" + aux.getID() + "\">\n";

                    if (!aux.getName().equals(it2.next().getName()))
                    {
                        flag2 = 1;
                    }
                }
            }

            buffer += buffer2 + "\t</SET>\n" + buffer2 + "</Object>\n";
        }

        return buffer;
    }

    /**
     * @param filename
     * @param typeA
     * @param typeB
     * @param typeC
     * @return
     * @throws FileNotFoundException
     * @throws IOException
     *
     * Operatia ce deserializeaza fisierul, refacand graful, conform noilor setari. Scrie in fisier daca operatia de cast a fost realizata cu succes sau nu. Returneaza noul graf.
     */
    @Override
    public Graph Deserialize(String filename, int typeA, int typeB, int typeC) throws FileNotFoundException, IOException
    {
        String line, words[], nodeType[] = null, version[] = null, id[] = null;

        FileInputStream is = new FileInputStream(filename);

        PrintWriter writer;

        Graph graph;

        try (BufferedReader reader = new BufferedReader(new InputStreamReader(is)))
        {
            writer = new PrintWriter("Deserialize_" + filename + "_CAST.log");

            graph = new Graph();

            while ((line = reader.readLine()) != null)
            {
                line = line.replace("\t", " ");

                words = line.trim().split(" ");

                if (words[0].equals("<Object"))
                {
                    nodeType = words[1].trim().split("\"");

                    version = words[2].trim().split("\"");

                    id = words[3].trim().split("\"");

                    continue;
                }

                words = line.trim().split(">");

                if (words.length > 1)
                {
                    words[1] = words[1].trim().split("<")[0];
                }

                if (words[0].equals("<Nume"))
                {
                    if (nodeType[1].equals("NodeA"))
                    {
                        NodeA node;

                        if (Integer.parseInt(version[1]) <= typeA)
                        {
                            node = new NodeA(words[1], Integer.parseInt(id[1]), typeA);

                            writer.println("OK cast NodA " + words[1] + " from Version=\"" + version[1] + "\" to Version=\"" + typeA + "\"");
                        } else
                        {
                            node = new NodeA(words[1], Integer.parseInt(id[1]), Integer.parseInt(version[1]));

                            writer.println("Fail cast NodA " + words[1] + " from Version=\"" + version[1] + "\" to Version=\"" + typeA + "\"");
                        }

                        graph.Insert(node);

                        continue;
                    }

                    if (nodeType[1].equals("NodeB"))
                    {
                        NodeB node;

                        if (Integer.parseInt(version[1]) <= typeB)
                        {
                            node = new NodeB(words[1], Integer.parseInt(id[1]), typeB);

                            writer.println("OK cast NodB " + words[1] + " from Version=\"" + version[1] + "\" to Version=\"" + typeA + "\"");
                        } else
                        {
                            node = new NodeB(words[1], Integer.parseInt(id[1]), Integer.parseInt(version[1]));

                            writer.println("Fail cast NodB " + words[1] + " from Version=\"" + version[1] + "\" to Version=\"" + typeA + "\"");
                        }

                        graph.Insert(node);

                        continue;
                    }

                    if (nodeType[1].equals("NodeC"))
                    {
                        NodeC node;

                        if (Integer.parseInt(version[1]) <= typeC)
                        {
                            node = new NodeC(words[1], Integer.parseInt(id[1]), typeC);

                            writer.println("OK cast NodC " + words[1] + " from Version=\"" + version[1] + "\" to Version=\"" + typeA + "\"");
                        } else
                        {
                            node = new NodeC(words[1], Integer.parseInt(id[1]), Integer.parseInt(version[1]));

                            writer.println("Fail cast NodC " + words[1] + " from Version=\"" + version[1] + "\" to Version=\"" + typeA + "\"");
                        }

                        graph.Insert(node);

                        continue;
                    }
                }

                line = line.replace("\t", " ");

                words = line.trim().split(" ");

                if (words[0].equals("<Reference"))
                {
                    nodeType = words[1].trim().split("\"");

                    version = words[2].trim().split("\"");

                    id = words[3].trim().split("\"");

                    for (Node traverse : graph.nodes)
                    {
                        if (traverse.getID() == Integer.parseInt(id[1]))
                        {
                            traverse.addNeighbors(graph.nodes.get(graph.nodes.size() - 1));
                            graph.nodes.get(graph.nodes.size() - 1).addNeighbors(traverse);
                        }
                    }
                }
            }
        }

        writer.close();

        return graph;
    }

    /**
     * Metoda optionala ce afiseaza informatiile din graf.
     */
    @Override
    public void Display()
    {
        Iterator<Node> it = nodes.iterator();

        while (it.hasNext())
        {
            Node aux = it.next();

            System.out.println(aux.getName());

            if (aux.getIteration() == 1)
            {
                if (aux.getNeighborsList() != null)
                {
                    List list = aux.getNeighborsList();

                    Iterator<Node> it1 = list.list.iterator();

                    while (it1.hasNext())
                    {
                        System.out.println("\t" + it1.next().getName());
                    }
                }
            }

            if (aux.getIteration() == 2)
            {
                Vector vector = aux.getNeighborsVector();

                Iterator<Node> it1 = vector.array.iterator();

                while (it1.hasNext())
                {
                    System.out.println("\t" + it1.next().getName());
                }
            }

            if (aux.getIteration() == 3)
            {
                Set set = aux.getNeighborsSet();

                Iterator<Node> it1 = set.set.iterator();

                while (it1.hasNext())
                {
                    System.out.println("\t" + it1.next().getName());
                }
            }
        }
    }
}
