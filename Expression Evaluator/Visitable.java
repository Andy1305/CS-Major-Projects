/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


/**
 *
 * @author Apollo
 * 
 * Interfata pentru design pattern-ul Visitor.
 */
public interface Visitable
{
    /**
     * 
     * @param visitor
     * @return 
     * 
     * Metoda pentru design pattern-ul Visitor.
     */
    public String accept(Visitor visitor);
}
