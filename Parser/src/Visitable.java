/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


/**
 *
 * @author Andy
 * 
 * Interfata pentru Visitable, ce accepta Visitorul.
 */
public interface Visitable
{
    public void accept(Visitor visitor);
}