/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


import java.util.Iterator;
import java.util.LinkedList;

/**
 * @author Andy
 *
 * Clasa este echivalentul primei iteratii, ce foloseste o lista simplu inlantuita pentru a retine nodurile adiacente.
 */
public class List implements IterationsInterface
{

    LinkedList<Node> list = new LinkedList<>();

    /**
     * @param node
     *
     * Adauga un "vecin" in lista de adiacenta.
     */
    @Override
    public void add(Node node)
    {
        list.add(node);
    }

    /**
     * @param name
     *
     * Sterge un "vecin" din lista de adiacenta.
     */
    @Override
    public void delete(String name)
    {
        Node node;

        Iterator<Node> it = list.iterator();

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
