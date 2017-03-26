/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


/**
 *
 * @author Apollo
 */
public class NodeFactory
{
    /**
     * @param info
     * @return 
     * 
     * Metoda apeleaza constructorul cu parametrii ai clasei Node, respectand design pattern-ul Factory.
     */
    public Node returnInstance(String info)
    {
        return new Node(info);
    }
}
