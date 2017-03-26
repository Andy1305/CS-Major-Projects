/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


/**
 *
 * @author Andy
 * 
 * Clasa Node reprezinta nodul generic ce contine metodele corespunzatoare fiecarei clase, A, B, sau C.
 */
public class Node
{
    int flag = 0, flag2 = 0;
    private String name;

    public Node()
    {

    }

    public Node(String name)
    {
        this.name = name;
    }

    public String getName()
    {
        return this.name;
    }

    public String getClassType()
    {
        return null;
    }

    public int getIteration()
    {
        return 0;
    }

    public int getID()
    {
        return 0;
    }

    public List getNeighborsList()
    {
        return null;
    }

    public Vector getNeighborsVector()
    {
        return null;
    }

    public Set getNeighborsSet()
    {
        return null;
    }

    public void addNeighbors(Node node)
    {

    }

    public void deleteNeighbors(String name)
    {

    }
}
