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

/**
 *
 * @author Andy
 */
public class Serialization
{

    /**
     * @param args the command line arguments
     * @throws java.io.FileNotFoundException
     *
     * In functia main se citeste din fisier si se apleaza functiile corespunzatoare, in functie de operatia citita.
     */
    public static void main(String[] args) throws FileNotFoundException, IOException
    {
        int i, j, typeA = 0, typeB = 0, typeC = 0, ID = 0;
        String line, words[];

        FileInputStream is = new FileInputStream(args[0]);

        try (BufferedReader reader = new BufferedReader(new InputStreamReader(is)))
        {
            Graph graph = new Graph();
            
            while ((line = reader.readLine()) != null)
            {
                words = line.trim().split(" ");
                
                if (words[0].equals("Settings"))
                {
                    typeA = Integer.parseInt(words[1]);
                    typeB = Integer.parseInt(words[2]);
                    typeC = Integer.parseInt(words[3]);
                    
                    continue;
                }
                
                if (words[0].equals("Add"))
                {
                    if (words[1].equals("NodA"))
                    {
                        if (typeA == 1)
                        {
                            NodeA node = new NodeA(words[2], ID, 1);
                            
                            ID++;
                            
                            if (words.length >= 4)  //Se verifica da sunt date si nodurile adiacente.
                            {
                                for (i = 3; i < words.length; i++)
                                {
                                    for (j = 0; j < graph.nodes.size(); j++)
                                    {
                                        if (graph.nodes.get(j).getName().equals(words[i]))
                                        {
                                            graph.InsertM(node, graph.nodes.get(j));
                                        }
                                    }
                                }
                            }
                            
                            graph.Insert(node);
                            
                            continue;
                        }
                        
                        if (typeA == 2)
                        {
                            NodeA node = new NodeA(words[2], ID, 2);
                            
                            ID++;
                            
                            if (words.length >= 4)  //Se verifica da sunt date si nodurile adiacente.
                            {
                                for (i = 3; i < words.length; i++)
                                {
                                    for (j = 0; j < graph.nodes.size(); j++)
                                    {
                                        if (graph.nodes.get(j).getName().equals(words[i]))  //Se conecteaza nodurile adiacente.
                                        {
                                            graph.InsertM(node, graph.nodes.get(j));
                                        }
                                    }
                                }
                            }
                            
                            graph.Insert(node);
                            
                            continue;
                        }
                        
                        if (typeA == 3)
                        {
                            NodeA node = new NodeA(words[2], ID, 3);
                            
                            ID++;
                            
                            if (words.length >= 4)  //Se verifica da sunt date si nodurile adiacente.
                            {
                                for (i = 3; i < words.length; i++)
                                {
                                    for (j = 0; j < graph.nodes.size(); j++)
                                    {
                                        if (graph.nodes.get(j).getName().equals(words[i]))
                                        {
                                            graph.InsertM(node, graph.nodes.get(j));
                                        }
                                    }
                                }
                            }
                            
                            graph.Insert(node);
                            
                            continue;
                        }
                    }
                    
                    if (words[1].equals("NodB"))
                    {
                        if (typeB == 1)
                        {
                            NodeB node = new NodeB(words[2], ID, 1);
                            
                            ID++;
                            
                            if (words.length >= 4)  //Se verifica da sunt date si nodurile adiacente.
                            {
                                for (i = 3; i < words.length; i++)
                                {
                                    for (j = 0; j < graph.nodes.size(); j++)
                                    {
                                        if (graph.nodes.get(j).getName().equals(words[i]))
                                        {
                                            graph.InsertM(node, graph.nodes.get(j));
                                        }
                                    }
                                }
                            }
                            
                            graph.Insert(node);
                            
                            continue;
                        }
                        
                        if (typeB == 2)
                        {
                            NodeB node = new NodeB(words[2], ID, 2);
                            
                            ID++;
                            
                            if (words.length >= 4)  //Se verifica da sunt date si nodurile adiacente.
                            {
                                for (i = 3; i < words.length; i++)
                                {
                                    for (j = 0; j < graph.nodes.size(); j++)
                                    {
                                        if (graph.nodes.get(j).getName().equals(words[i]))
                                        {
                                            graph.InsertM(node, graph.nodes.get(j));
                                        }
                                    }
                                }
                            }
                            
                            graph.Insert(node);
                            
                            continue;
                        }
                        
                        if (typeB == 3)
                        {
                            NodeB node = new NodeB(words[2], ID, 3);
                            
                            ID++;
                            
                            if (words.length >= 4)  //Se verifica da sunt date si nodurile adiacente.
                            {
                                for (i = 3; i < words.length; i++)
                                {
                                    for (j = 0; j < graph.nodes.size(); j++)
                                    {
                                        if (graph.nodes.get(j).getName().equals(words[i]))
                                        {
                                            graph.InsertM(node, graph.nodes.get(j));
                                        }
                                    }
                                }
                            }
                            
                            graph.Insert(node);
                            
                            continue;
                        }
                    }
                    
                    if (words[1].equals("NodC"))
                    {
                        if (typeC == 1)
                        {
                            NodeC node = new NodeC(words[2], ID, 1);
                            
                            ID++;
                            
                            if (words.length >= 4)  //Se verifica da sunt date si nodurile adiacente.
                            {
                                for (i = 3; i < words.length; i++)
                                {
                                    for (j = 0; j < graph.nodes.size(); j++)
                                    {
                                        if (graph.nodes.get(j).getName().equals(words[i]))
                                        {
                                            graph.InsertM(node, graph.nodes.get(j));
                                        }
                                    }
                                }
                            }
                            
                            graph.Insert(node);
                            
                            continue;
                        }
                        
                        if (typeC == 2)
                        {
                            NodeC node = new NodeC(words[2], ID, 2);
                            
                            ID++;
                            
                            if (words.length >= 4)  //Se verifica da sunt date si nodurile adiacente.
                            {
                                for (i = 3; i < words.length; i++)
                                {
                                    for (j = 0; j < graph.nodes.size(); j++)
                                    {
                                        if (graph.nodes.get(j).getName().equals(words[i]))
                                        {
                                            graph.InsertM(node, graph.nodes.get(j));
                                        }
                                    }
                                }
                            }
                            
                            graph.Insert(node);
                            
                            continue;
                        }
                        
                        if (typeC == 3)
                        {
                            NodeC node = new NodeC(words[2], ID, 3);
                            
                            ID++;
                            
                            if (words.length >= 4)  //Se verifica da sunt date si nodurile adiacente.
                            {
                                for (i = 3; i < words.length; i++)
                                {
                                    for (j = 0; j < graph.nodes.size(); j++)
                                    {
                                        if (graph.nodes.get(j).getName().equals(words[i]))
                                        {
                                            graph.InsertM(node, graph.nodes.get(j));
                                        }
                                    }
                                }
                            }
                            
                            graph.Insert(node);
                        }
                    }
                }
                
                if (words[0].equals("Del"))
                {
                    graph.Delete(words[1], words[2]);
                }
                
                if (words[0].equals("AddM"))
                {
                    Node aux = new Node();
                    Node aux2 = new Node();
                    
                    for (Node node : graph.nodes)   //Se cauta nodurile in graf.
                    {
                        if (node.getName().equals(words[1]))
                        {
                            aux = node;
                        }
                        
                        if (node.getName().equals(words[2]))
                        {
                            aux2 = node;
                        }
                    }
                    
                    graph.InsertM(aux, aux2);
                }
                
                if (words[0].equals("DelM"))
                {
                    graph.DeleteM(words[1], words[2]);
                }
                
                if (words[0].equals("Serialize"))
                {
                    try (PrintWriter writer = new PrintWriter(words[2]))
                    {
                        String buffer = "";
                        
                        buffer += graph.Serialize(graph.findInfo(words[1]), buffer, 0);
                        
                        writer.println(buffer);
                        
                        writer.close();
                    }
                }
                
                if (words[0].equals("Deserialize"))
                {
                    graph = graph.Deserialize(words[1], typeA, typeB, typeC);
                    
                    //graph.Display();
                }
            }
        }
    }
}
