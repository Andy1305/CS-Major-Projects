/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


import java.util.HashSet;
import java.util.Iterator;

/**
 * @author Andy
 *
 * Clasa este echivalentul iteratiei 3, ce foloseste un set pentru a retine nodurile adiacente.
 */
public class Set implements IterationsInterface
{

    HashSet<Node> set = new HashSet<>();

    /**
     * @param node
     *
     * Adauga un "vecin" in setul de adiacenta.
     */
    @Override
    public void add(Node node)
    {
        set.add(node);
    }

    /**
     * @param name
     *
     * Sterge un "vecin" din setul de adiacenta.
     */
    @Override
    public void delete(String name)
    {
        Node node;

        Iterator<Node> it = set.iterator();

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
