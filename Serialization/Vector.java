/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


import java.util.ArrayList;
import java.util.Iterator;

/**
 * @author Andy
 *
 * Clasa este echivalentul iteratiei 2, ce foloseste un vector pentru a retine nodurile adiacente.
 */
public class Vector implements IterationsInterface
{

    ArrayList<Node> array = new ArrayList<>();

    /**
     * @param node
     *
     * Adauga un "vecin" in vectorul de adiacenta.
     */
    @Override
    public void add(Node node)
    {
        array.add(node);
    }

    /**
     * @param name
     *
     * Sterge un "vecin" din vectorul de adiacenta.
     */
    @Override
    public void delete(String name)
    {
        Node node;

        Iterator<Node> it = array.iterator();

        while (it.hasNext())
        {
            node = it.next();

            if (node.getName().equals(name))
            {
                it.remove();
            }
        }
    }
}
