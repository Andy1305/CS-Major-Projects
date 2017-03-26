/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


import java.util.HashMap;

/**
 *
 * @author Apollo
 * 
 * Interfata pentru design pattern-ul Visitor.
 */
public interface Visitor
{
    /**
     * 
     * @param n
     * @param ints
     * @param doubles
     * @param strings
     * @return 
     * 
     * Metoda pentru design pattern-ul Visitor, ce apeleaza metoda evaluate.
     */
    public String visit(Node n, HashMap ints, HashMap doubles, HashMap strings);
}
