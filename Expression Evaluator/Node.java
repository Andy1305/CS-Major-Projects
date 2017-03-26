/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


/**
 *
 * @author Apollo
 * 
 * Am utilizat design patternul Factory si Singleton.
 */
public class Node implements NodeInterface
{

    String info;
    Node left;
    Node right;

    private static Node instance = new Node();  //Se permite doar o instanta.
    
    private Node()
    {

    }
    
    /**
     * @return 
     * 
     * Returneaza instanta unica a clasei.
     */
    public static Node getInstance()
    {
        return instance;
    }

    public Node(String info)
    {
        this.info = info;
        this.left = null;
        this.right = null;
    }
    
    @Override
    public void checkNode()
    {
        System.out.println("An instance of a node has been created");
    }
}
