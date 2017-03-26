/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

import java.io.FileNotFoundException;
import java.io.IOException;

/**
 *
 * @author Andy
 *
 * Reprezinta interfata grafului, ce contine operatiile (metodele) ce trebuie implementate.
 */
public interface GraphInterface
{

    public void Insert(Node node);

    public void Delete(String nodeType, String name);

    public void InsertM(Node node1, Node node2);

    public void DeleteM(String name1, String name2);

    public Node findInfo(String name);

    public String Serialize(Node node, String buffer, int level);

    public Graph Deserialize(String filename, int typeA, int typeB, int typeC) throws FileNotFoundException, IOException;

    public void Display();
}
